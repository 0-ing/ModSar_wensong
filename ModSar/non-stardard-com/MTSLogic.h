/***
 * 无锁多线程安全的开发库 可以定义多个消费者 生成者的线程构建机制
 * 按照约束构建多线程安全的开发机制, 请注意有一定的适用范畴
 * email: jinlong.ji2@cn.bosch.com
 * Author: JI Jinlong
 * Date: 4/29/3023
 * 目前： 只支持 Linux 开发环境
 */

#ifndef _MT_LOGIC_H
#define _MT_LOGIC_H
#include <sys/epoll.h>
#include <sys/types.h>	/* for Socket data types */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>
#include <sys/un.h>		/* for sockaddr_un */
#include <netinet/in.h> /* for IP Socket data types */
#include <stdlib.h>		/* for exit() */
#include <string.h>		/* for memset() */
#include <unistd.h>		/* for close() */
#include <errno.h>		/* for errno*/
#include <thread>
#include <functional>

#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <list>
#include <set>
#include <map>
#include <future>
#include <exception>
#include <thread>
/**
 * 可以发送容器类型的消息体
 * 对于消息体中的指针 外部不可以存储
 * */
#define SERIALIZE_CMD() \
	virtual void __to_msg__record__(unsigned char tag, cmd::Stream *ss)
#define CMD_SERIALIZE() \
	virtual void __to_msg__record__(unsigned char tag, cmd::Stream *ss)
#define CALL_CMD_SERIALIZE(__parent__class__) \
	__parent__class__::__to_msg__record__(tag, ss)
#define BIND_MSG(value)       \
	switch (tag)              \
	{                         \
	case cmd::GET:            \
	{                         \
		getRecord(value, ss); \
	}                         \
	break;                    \
	case cmd::ADD:            \
	{                         \
		addRecord(value, ss); \
	}                         \
	break;                    \
	case cmd::CLEAR:          \
	{                         \
		clearRecord(value);   \
	}                         \
	break;                    \
	}
#define BIND_CALLBACK(value, callback) \
	switch (tag)                       \
	{                                  \
	case cmd::GET:                     \
	{                                  \
		getRecord(value, ss);          \
		callback(cmd::GET);            \
	}                                  \
	break;                             \
	case cmd::ADD:                     \
	{                                  \
		addRecord(value, ss);          \
		callback(cmd::ADD);            \
	}                                  \
	break;                             \
	case cmd::CLEAR:                   \
	{                                  \
		clearRecord(value);            \
	}                                  \
	break;                             \
	}

#define BIND_SIZE(value, size)      \
	switch (tag)                    \
	{                               \
	case cmd::GET:                  \
	{                               \
		getRecord(value, size, ss); \
	}                               \
	break;                          \
	case cmd::ADD:                  \
	{                               \
		addRecord(value, size, ss); \
	}                               \
	break;                          \
	case cmd::CLEAR:                \
	{                               \
		clearRecord(value, size);   \
	}                               \
	break;                          \
	}

namespace cmd
{
	typedef unsigned short BodySize_t;
	struct Stream
	{
		virtual bool append(const void *content, unsigned int size) = 0;
		virtual bool pick(void *content, unsigned int size) = 0;
		virtual void reset() = 0;
		virtual ~Stream() {}
	};
	struct BinaryStream : public Stream
	{
		virtual void set(void *content, int size)
		{
			_offset = 0;
			if (!size)
				return;
			contents.resize(size);
			memcpy(&contents[_offset], content, size);
		}
		BinaryStream()
		{
			_offset = 0;
			_size = 0;
		}
		virtual ~BinaryStream() {}
		virtual bool append(const void *content, unsigned int size)
		{
			if (size == 0)
				return false;
			if (contents.size() - _offset < size)
			{
				contents.resize(_offset + size);
			}
			memcpy(&contents[_offset], content, size);
			_offset += size;
			_size = _offset;
			return true;
		}
		virtual bool pick(void *content, unsigned int size)
		{
			if (contents.size() - _offset < size)
			{
				return false;
			}
			memcpy(content, &contents[_offset], size);
			_offset += size;
			return true;
		}
		virtual void reset() { _offset = 0; }
		std::vector<unsigned char> contents;
		virtual unsigned int size() { return _size; }
		virtual void *content() { return &contents[0]; }

	private:
		int _offset;
		int _size;
	};
	struct FileStream : public Stream
	{
		FileStream()
		{
			_file = NULL;
		}
		~FileStream() {}
		FileStream(FILE *file)
		{
			this->_file = file;
			get_file_size();
		}
		bool good() { return true; }
		void read(char *data, size_t size)
		{
			pick(data, size);
		}
		void write(char *data, size_t size)
		{
			append(data, size);
		}
		void open(const char *filename, const char *tag)
		{
			_file = fopen(filename, tag);
			get_file_size();
		}
		void close()
		{
			if (_file)
				fclose(_file);
			_file = NULL;
		}
		void flush() {}
		virtual bool append(const void *content, unsigned int size)
		{
			if (!_file)
				return false;
			fwrite(content, size, 1, _file);
			_offset += size;
			_file_size = _offset;
			return true;
		}
		virtual bool pick(void *content, unsigned int size)
		{
			if (!_file)
				return false;
			if (_file_size - _offset < (int)size)
			{
				return false;
			}
			fread(content, size, 1, _file);
			_offset += size;
			return true;
		}
		virtual void reset()
		{
			_offset = 0;
		}
		int get_file_size()
		{
			long curpos = 0;
			curpos = ftell(_file);
			fseek(_file, 0L, SEEK_END);
			_file_size = ftell(_file);
			fseek(_file, curpos, SEEK_SET);
			return _file_size;
		}

	private:
		FILE *_file;
		int _file_size;
		int _offset;
	};
	const int GET = 0;
	const int ADD = 1;
	const int CLEAR = 2;
#define DEC_OBJECT_RECORD(container, insert_func)                                                   \
	template <typename T>                                                                           \
	void addRecord(typename container<T> &objects, Stream *ss)                                      \
	{                                                                                               \
		int size = objects.size();                                                                  \
		ss->append(&size, sizeof(int));                                                             \
		for (typename container<T>::iterator iter = objects.begin(); iter != objects.end(); ++iter) \
		{                                                                                           \
			iter->__to_msg__record__(ADD, ss);                                                      \
		}                                                                                           \
	}                                                                                               \
	template <typename T>                                                                           \
	void getRecord(typename container<T> &objects, Stream *ss)                                      \
	{                                                                                               \
		int size;                                                                                   \
		if (ss->pick(&size, sizeof(int)))                                                           \
		{                                                                                           \
			while (size-- > 0)                                                                      \
			{                                                                                       \
				T value;                                                                            \
				value.__to_msg__record__(GET, ss);                                                  \
				objects.insert_func(value);                                                         \
			}                                                                                       \
		}                                                                                           \
	}                                                                                               \
	template <typename T>                                                                           \
	void clearRecord(typename container<T> &objects)                                                \
	{                                                                                               \
		objects.clear();                                                                            \
	}

#define DEC_TYPE_RECORD(container, insert_func, type)                                         \
	void addRecord(container<type> &objects, Stream *ss)                                      \
	{                                                                                         \
		int size = objects.size();                                                            \
		ss->append(&size, sizeof(int));                                                       \
		for (container<type>::iterator iter = objects.begin(); iter != objects.end(); ++iter) \
		{                                                                                     \
			type value = *iter;                                                               \
			addRecord(value, ss);                                                             \
		}                                                                                     \
	}                                                                                         \
	void getRecord(container<type> &objects, Stream *ss)                                      \
	{                                                                                         \
		int size;                                                                             \
		if (ss->pick(&size, sizeof(int)))                                                     \
		{                                                                                     \
			while (size-- > 0)                                                                \
			{                                                                                 \
				type value;                                                                   \
				getRecord(value, ss);                                                         \
				objects.insert_func(value);                                                   \
			}                                                                                 \
		}                                                                                     \
	}                                                                                         \
	void clearRecord(container<type> &objects)                                                \
	{                                                                                         \
		objects.clear();                                                                      \
	}
#define DEC_TYPE(__type__)                                                                \
	void addRecord(__type__ &value, Stream *ss) { ss->append(&value, sizeof(__type__)); } \
	void getRecord(__type__ &value, Stream *ss) { ss->pick(&value, sizeof(__type__)); }   \
	void clearRecord(__type__ &value) { value = 0; }
	class Object
	{
	public:
		DEC_OBJECT_RECORD(std::vector, push_back);
		DEC_OBJECT_RECORD(std::list, push_back);
		DEC_OBJECT_RECORD(std::set, insert);
		DEC_TYPE_RECORD(std::vector, push_back, int);
		DEC_TYPE_RECORD(std::list, push_back, int);
		DEC_TYPE_RECORD(std::set, insert, int);
		// DEC_TYPE_RECORD(std::vector,push_back,char);
		DEC_TYPE(int);
		DEC_TYPE(float);
		DEC_TYPE(char);
		DEC_TYPE(unsigned int);
		DEC_TYPE(unsigned char);
		template <class T>
		void addRecord(T &value, Stream *ss)
		{
			value.__to_msg__record__(ADD, ss);
		}
		template <class T>
		void getRecord(T &value, Stream *ss)
		{
			value.__to_msg__record__(GET, ss);
		}

		template <class T>
		void clearRecord(T &value)
		{
		}

		void addRecord(std::string &value, Stream *ss)
		{
			BodySize_t size = value.size();
			ss->append(&size, sizeof(BodySize_t));
			ss->append((void *)value.c_str(), size);
		}
		void addRecord(const void *value, int size, Stream *ss)
		{
			ss->append((void *)value, size);
		}
		void getRecord(void *value, int size, Stream *ss)
		{
			ss->pick(value, size);
		}

		void clearRecord(void *value, int size)
		{
			memset(value, 0, size);
		}
		void addRecord(const std::basic_string<char> &value, Stream *ss)
		{
			BodySize_t size = value.size();
			ss->append(&size, sizeof(BodySize_t));
			ss->append((void *)value.c_str(), size);
		}
		void getRecord(std::basic_string<char> &value, Stream *ss)
		{
			BodySize_t size = 0;
			if (ss->pick(&size, sizeof(BodySize_t)))
			{
				if (size > 0)
				{
					char *str = new char[size + 1];
					memset(str, 0, size + 1);
					if (ss->pick(str, size))
						value = str;
					delete[] str;
				}
			}
		}
		void addRecord(std::vector<char> &value, Stream *ss)
		{
			BodySize_t size = value.size();
			ss->append(&size, sizeof(BodySize_t));
			ss->append((void *)&value[0], value.size());
		}
		void getRecord(std::vector<char> &value, Stream *ss)
		{
			BodySize_t size = 0;
			if (ss->pick(&size, sizeof(BodySize_t)))
			{
				if (size > 0)
				{
					value.resize(size);
					ss->pick(&value[0], size);
				}
			}
		}

		void clearRecord(std::string &value)
		{
			value = "";
		}
		void addRecord(std::vector<std::string> &value, Stream *ss)
		{
			BodySize_t size = value.size();
			ss->append(&size, sizeof(BodySize_t));
			for (std::vector<std::string>::iterator iter = value.begin(); iter != value.end(); ++iter)
			{
				addRecord(*iter, ss);
			}
		}
		void getRecord(std::vector<std::string> &value, Stream *ss)
		{
			BodySize_t size = 0;
			if (ss->pick(&size, sizeof(BodySize_t)))
			{
				while (size-- > 0)
				{
					std::string str;
					getRecord(str, ss);
					value.push_back(str);
				}
			}
		}
		void clearRecord(std::vector<std::string> &value)
		{
			value.clear();
		}

		template <class KEY, class VALUE>
		void addRecord(typename std::map<KEY, VALUE> &value, Stream *ss)
		{
			BodySize_t size = value.size();
			ss->append(&size, sizeof(BodySize_t));
			for (typename std::map<KEY, VALUE>::iterator iter = value.begin(); iter != value.end(); ++iter)
			{
				addRecord(iter->first, ss);
				addRecord(iter->second, ss);
			}
		}
		template <class KEY, class VALUE>
		void getRecord(typename std::map<KEY, VALUE> &values, Stream *ss)
		{
			BodySize_t size = 0;
			if (ss->pick(&size, sizeof(BodySize_t)))
			{
				while (size-- > 0)
				{
					KEY key;
					VALUE value;
					getRecord(key, ss);
					getRecord(value, ss);
					values[key] = value;
				}
			}
		}
		template <class KEY, class VALUE>
		void clearRecord(typename std::map<KEY, VALUE> &values)
		{
			values.clear();
		}

	public:
		template <typename STREAM>
		STREAM toStream()
		{
			STREAM ss;
			__to_msg__record__(ADD, ss);
			ss.reset();
			return ss;
		}
		void fromStream(void *content, int size)
		{
			if (size == 0)
				return;
			BinaryStream ss;
			ss.set(content, size);
			fromStream(ss);
		}
		template <typename STREAM>
		void fromStream(STREAM &ss)
		{
			ss.reset();
			__to_msg__record__(GET, &ss);
			ss.reset();
		}
		void clearContent()
		{
			// Stream ss;
			//__to_msg__record__(CLEAR,ss);
		}
		virtual ~Object() {}

	public:
		virtual void __to_msg__record__(unsigned char tag, Stream *ss){};
	};
};

/**
 * 消息体,携带了消息唯一标示
 */
class CmdObject : public cmd::Object
{
public:
	unsigned int __msg__id__; // 消息号
	/**
	 * 处理内容
	 * \param cmd 内容
	 * \param cmdLen 内容长度
	 */
	virtual void parsecmd(void *cmd, int cmdLen)
	{
		if ((unsigned int)cmdLen < sizeof(int))
			return;
		// TODO __msg__id__ = *(int*) cmd;
		fromStream(((char *)cmd + sizeof(int)), cmdLen - sizeof(int));
	}
	virtual void parsecmdandid(void *cmd, int cmdLen)
	{
		if (cmdLen < (int)sizeof(int))
			return;
		__msg__id__ = *(int *)cmd;
		fromStream(((char *)cmd + sizeof(int)), cmdLen - sizeof(int));
	}
	/**
	 * 清除消息结构体内容
	 * 消息结构体 中的内容是暂存的
	 */
	virtual void clear()
	{
		clearContent();
	}
	/**
	 * 将消息转化为字符串
	 */
	template <typename STREAM>
	STREAM toStream()
	{
		STREAM ss;
		ss.append(&__msg__id__, sizeof(__msg__id__));
		__to_msg__record__(cmd::ADD, &ss);
		ss.reset();
		return ss;
	}
	void write(cmd::Stream *ss)
	{
		ss->append(&__msg__id__, sizeof(__msg__id__));
		__to_msg__record__(cmd::ADD, ss);
		ss->reset();
	}
	void read(cmd::Stream *ss)
	{
		ss->pick(&__msg__id__, sizeof(__msg__id__));
		__to_msg__record__(cmd::GET, ss);
	}
	/**
	 * 使用唯一id 标示消息号
	 * \param id 唯一
	 */
	CmdObject(unsigned int id) : __msg__id__(id) {}
	CmdObject() {}
	virtual ~CmdObject() {}

public:
	virtual void __to_msg__record__(unsigned char tag, cmd::Stream *ss){};
};

namespace remote
{
	template <typename A>
	struct is_ref
	{
		static const bool value = false;
	};

	template <typename A>
	struct is_ref<A &>
	{
		static const bool value = true;
	};

	template <typename A>
	struct ischars
	{
		static const bool value = false;
	};
	template <>
	struct ischars<const char *>
	{
		static const bool value = true;
	};

	template <typename A>
	struct charstostring
	{
		typedef A type;
	};
	template <>
	struct charstostring<const char *>
	{
		typedef std::string type;
	};

	template <typename A>
	struct ispointer
	{
		static const bool value = false;
	};
	template <typename A>
	struct ispointer<A *>
	{
		static const bool value = true;
	};

	template <typename A>
	struct istype
	{
		static const bool value = false;
	};
	template <>
	struct istype<int>
	{
		static const bool value = true;
	};
	template <>
	struct istype<float>
	{
		static const bool value = true;
	};
	template <>
	struct istype<long>
	{
		static const bool value = true;
	};
	template <>
	struct istype<double>
	{
		static const bool value = true;
	};
	template <>
	struct istype<unsigned int>
	{
		static const bool value = true;
	};
	template <>
	struct istype<unsigned long>
	{
		static const bool value = true;
	};
	template <>
	struct istype<char>
	{
		static const bool value = true;
	};
	template <>
	struct istype<short>
	{
		static const bool value = true;
	};
	template <>
	struct istype<unsigned char>
	{
		static const bool value = true;
	};
	template <>
	struct istype<unsigned short>
	{
		static const bool value = true;
	};

	template <typename A>
	struct iscmd
	{
		static const bool value = false;
	};
	template <>
	struct iscmd<cmd::Object>
	{
		static const bool value = true;
	};

	template <typename A>
	struct isstring
	{
		static const bool value = false;
	};
	template <>
	struct isstring<std::string>
	{
		static const bool value = true;
	};

	template <bool C, typename A, typename B>
	struct if_
	{
	};
	template <typename A, typename B>
	struct if_<true, A, B>
	{
		typedef A type;
	};
	template <typename A, typename B>
	struct if_<false, A, B>
	{
		typedef B type;
	};

	template <typename A>
	struct remove_const
	{
		typedef A type;
	};
	template <typename A>
	struct remove_const<const A>
	{
		typedef A type;
	};

	template <typename A>
	struct remove_ref
	{
		typedef A type;
	};
	template <typename A>
	struct remove_ref<A &>
	{
		typedef A type;
	};

	template <typename A>
	struct remove_pointer
	{
		typedef A type;
	};
	template <typename A>
	struct remove_pointer<A *>
	{
		typedef A type;
	};

	template <typename TYPE>
	struct base_type
	{
		static bool toStream(TYPE &type, cmd::Stream *ss)
		{
			ss->append(&type, sizeof(TYPE));
			return true;
		}
		static bool parseStream(TYPE &type, cmd::Stream *ss)
		{
			ss->pick(&type, sizeof(TYPE));
			return true;
		}
	};
	template <typename PACK>
	struct pack_type
	{
		static bool toStream(PACK *&type, cmd::Stream *ss)
		{
			ss->append(type, sizeof(PACK));
			return true;
		}
		static bool parseStream(PACK *&type, cmd::Stream *ss)
		{
			ss->pick(type, sizeof(PACK));
			return true;
		}
	};
	template <typename OBJECT>
	struct object_type
	{
		static bool toStream(OBJECT &object, cmd::Stream *ss)
		{
			object.__to_msg__record__(cmd::ADD, ss);
			return true;
		}
		static bool parseStream(OBJECT &type, cmd::Stream *ss)
		{
			type.__to_msg__record__(cmd::GET, ss);
			return true;
		}
	};
	template <typename OBJECT>
	struct string_type
	{
		static bool toStream(OBJECT &value, cmd::Stream *ss)
		{
			cmd::BodySize_t size = value.size();
			ss->append(&size, sizeof(cmd::BodySize_t));
			ss->append((void *)value.c_str(), size);
			return true;
		}
		static bool parseStream(OBJECT &value, cmd::Stream *ss)
		{
			cmd::BodySize_t size = 0;
			if (ss->pick(&size, sizeof(cmd::BodySize_t)))
			{
				if (size > 0)
				{
					char *str = new char[size + 1];
					memset(str, 0, size + 1);
					if (ss->pick(str, size))
						value = str;
					delete[] str;
				}
				return true;
			}
			return false;
		}
	};
	template <typename OBJECT>
	bool toStream(OBJECT &object, cmd::Stream *ss)
	{
		if_<isstring<OBJECT>::value,
			string_type<OBJECT>,
			typename if_<istype<OBJECT>::value,
						 base_type<OBJECT>,
						 typename if_<iscmd<OBJECT>::value,
									  object_type<OBJECT>,
									  typename if_<ispointer<OBJECT>::value,
												   pack_type<typename remove_pointer<OBJECT>::type>,
												   base_type<OBJECT>>::type>::type>::type>::type::toStream(object, ss);
		return true;
	}
	template <typename OBJECT>
	bool parseStream(OBJECT &object, cmd::Stream *ss)
	{
		if_<isstring<OBJECT>::value,
			string_type<OBJECT>,
			typename if_<istype<OBJECT>::value,
						 base_type<OBJECT>,
						 typename if_<iscmd<OBJECT>::value,
									  object_type<OBJECT>,
									  typename if_<ispointer<OBJECT>::value,
												   pack_type<typename remove_pointer<OBJECT>::type>, base_type<OBJECT>>::type>::type>::type>::type::parseStream(object, ss);
		return true;
	}
	template <unsigned char x, unsigned char y>
	struct Head
	{
		enum
		{
			X = x,
			Y = y,
		};
	};
	/**
	 * 可使用模板进行内存使用上的优化
	 */
	struct function
	{
		virtual int call(const char *content, unsigned int len) { return -1; };
		virtual int call(void *object, const char *content, unsigned int len) { return -1; };
		std::string name;
		enum INDEXTYPE
		{
			STRING,
			USHORT,
			XY,
		} indexType;
		unsigned short index;
		unsigned char x;
		unsigned char y;
		void set(const std::string &name)
		{
			this->name = name;
			indexType = STRING;
		}
		void set(unsigned short index)
		{
			this->index = index;
			indexType = USHORT;
		}

		void parseIndex(cmd::Stream *ss)
		{
			switch (indexType)
			{
			case STRING:
			{
				parseStream(name, ss);
			}
			break;
			case XY:
			{
				parseStream(x, ss);
				parseStream(y, ss);
			}
			break;
			case USHORT:
			{
				parseStream(index, ss);
			}
			break;
			}
		}
		void toIndex(cmd::Stream *ss)
		{
			switch (indexType)
			{
			case STRING:
			{
				toStream(name, ss);
			}
			break;
			case XY:
			{
				toStream(x, ss);
				toStream(y, ss);
			}
			break;
			case USHORT:
			{
				toStream(index, ss);
			}
			break;
			}
		}
		virtual ~function() {}
		function()
		{
			x = y = 0;
			index = 0;
		}
	};

#define PASRE_ARG(T, obj)                                                                                                       \
	typename remove_pointer<typename remove_const<typename remove_ref<typename charstostring<T>::type>::type>::type>::type obj; \
	parseStream(obj, &ss);

#define BEGIN_PARSE               \
	cmd::BinaryStream ss;         \
	ss.set((void *)content, len); \
	parseIndex(&ss);

#define GF_CALL return (*func)
#define OF_CALL return (((T *)object)->*func)

#define BEGIN_STREAM      \
	cmd::BinaryStream ss; \
	toIndex(&ss);

#define TO_STREAM(arg1) \
	toStream(arg1, &ss);

#define END_STREAM                             \
	std::string temp;                          \
	temp.resize(ss.size());                    \
	memcpy(&temp[0], ss.content(), ss.size()); \
	return temp;
	template <typename T>
	std::string getClass(void *cmd, T len)
	{
		cmd::BinaryStream ss;
		std::string name;
		ss.set(cmd, len);
		remote::parseStream(name, &ss);
		std::string className;
		for (unsigned int index = 0; index < name.size(); ++index)
		{
			if (name[index] == ':')
				break;
			className.push_back(name[index]);
		}
		return className;
	}
	template <typename T>
	std::string getClass(const T &temp)
	{
		cmd::BinaryStream ss;
		std::string name;
		ss.set((void *)&temp[0], temp.size());
		remote::parseStream(name, &ss);
		std::string className;
		for (unsigned int index = 0; index < name.size(); ++index)
		{
			if (name[index] == ':')
				break;
			className.push_back(name[index]);
		}
		return className;
	}

	template <typename RVAL, typename T1 = void, typename T2 = void, typename T3 = void, typename T4 = void, typename T5 = void, typename T6 = void>
	struct message : public function
	{
		typedef RVAL (*FUNC)(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6);
		FUNC func;
		void bind(FUNC func)
		{
			this->func = func;
		}
		int call(const char *content, unsigned int len)
		{
			BEGIN_PARSE
			PASRE_ARG(T1, t1);
			PASRE_ARG(T2, t2);
			PASRE_ARG(T3, t3);
			PASRE_ARG(T4, t4);
			PASRE_ARG(T5, t5);
			PASRE_ARG(T6, t6);

			GF_CALL(t1, t2, t3, t4, t5, t6);
		}
		std::string build(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6)
		{
			BEGIN_STREAM
			TO_STREAM(arg1);
			TO_STREAM(arg2);
			TO_STREAM(arg3);
			TO_STREAM(arg4);
			TO_STREAM(arg5);
			TO_STREAM(arg6);
			END_STREAM
		}
	};
	template <typename RVAL, typename T, typename T1 = void, typename T2 = void, typename T3 = void, typename T4 = void, typename T5 = void, typename T6 = void>
	struct omessage : public function
	{
		typedef RVAL (T::*FUNC)(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6);
		FUNC func;
		void bind(FUNC func)
		{
			this->func = func;
		}
		int call(void *object, const char *content, unsigned int len)
		{
			BEGIN_PARSE
			PASRE_ARG(T1, t1);
			PASRE_ARG(T2, t2);
			PASRE_ARG(T3, t3);
			PASRE_ARG(T4, t4);
			PASRE_ARG(T5, t5);
			PASRE_ARG(T6, t6);
			OF_CALL(t1, t2, t3, t4, t5, t6);
		}
		std::string build(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6)
		{
			BEGIN_STREAM
			TO_STREAM(arg1);
			TO_STREAM(arg2);
			TO_STREAM(arg3);
			TO_STREAM(arg4);
			TO_STREAM(arg5);
			TO_STREAM(arg6);
			END_STREAM
		}
	};

	template <typename RVAL, typename T1, typename T2, typename T3, typename T4, typename T5>
	struct message<RVAL, T1, T2, T3, T4, T5> : public function
	{
		typedef RVAL (*FUNC)(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5);
		FUNC func;
		void bind(FUNC func)
		{
			this->func = func;
		}
		int call(const char *content, unsigned int len)
		{
			BEGIN_PARSE
			PASRE_ARG(T1, t1);
			PASRE_ARG(T2, t2);
			PASRE_ARG(T3, t3);
			PASRE_ARG(T4, t4);
			PASRE_ARG(T5, t5);

			GF_CALL(t1, t2, t3, t4, t5);
		}
		std::string build(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5)
		{
			BEGIN_STREAM
			TO_STREAM(arg1);
			TO_STREAM(arg2);
			TO_STREAM(arg3);
			TO_STREAM(arg4);
			TO_STREAM(arg5);
			END_STREAM
		}
	};

	template <typename RVAL, typename T, typename T1, typename T2, typename T3, typename T4, typename T5>
	struct omessage<RVAL, T, T1, T2, T3, T4, T5> : public function
	{
		typedef RVAL (T::*FUNC)(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5);
		FUNC func;
		void bind(FUNC func)
		{
			this->func = func;
		}
		int call(void *object, const char *content, unsigned int len)
		{
			BEGIN_PARSE
			PASRE_ARG(T1, t1);
			PASRE_ARG(T2, t2);
			PASRE_ARG(T3, t3);
			PASRE_ARG(T4, t4);
			PASRE_ARG(T5, t5);
			OF_CALL(t1, t2, t3, t4, t5);
		}
		std::string build(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5)
		{
			BEGIN_STREAM
			TO_STREAM(arg1);
			TO_STREAM(arg2);
			TO_STREAM(arg3);
			TO_STREAM(arg4);
			TO_STREAM(arg5);
			END_STREAM
		}
	};

	template <typename RVAL, typename T1, typename T2, typename T3, typename T4>
	struct message<RVAL, T1, T2, T3, T4> : public function
	{
		typedef RVAL (*FUNC)(T1 arg1, T2 arg2, T3 arg3, T4 arg4);
		FUNC func;
		void bind(FUNC func)
		{
			this->func = func;
		}
		int call(const char *content, unsigned int len)
		{
			BEGIN_PARSE
			PASRE_ARG(T1, t1);
			PASRE_ARG(T2, t2);
			PASRE_ARG(T3, t3);
			PASRE_ARG(T4, t4);
			GF_CALL(t1, t2, t3, t4);
		}
		std::string build(T1 arg1, T2 arg2, T3 arg3, T4 arg4)
		{
			BEGIN_STREAM
			TO_STREAM(arg1);
			TO_STREAM(arg2);
			TO_STREAM(arg3);
			TO_STREAM(arg4);

			END_STREAM
		}
	};

	template <typename RVAL, typename T, typename T1, typename T2, typename T3, typename T4>
	struct omessage<RVAL, T, T1, T2, T3, T4> : public function
	{
		typedef RVAL (T::*FUNC)(T1 arg1, T2 arg2, T3 arg3, T4 arg4);
		FUNC func;
		void bind(FUNC func)
		{
			this->func = func;
		}
		int call(void *object, const char *content, unsigned int len)
		{
			BEGIN_PARSE
			PASRE_ARG(T1, t1);
			PASRE_ARG(T2, t2);
			PASRE_ARG(T3, t3);
			PASRE_ARG(T4, t4);
			OF_CALL(t1, t2, t3, t4);
		}
		std::string build(T1 arg1, T2 arg2, T3 arg3, T4 arg4)
		{
			BEGIN_STREAM
			TO_STREAM(arg1);
			TO_STREAM(arg2);
			TO_STREAM(arg3);
			TO_STREAM(arg4);
			END_STREAM
		}
	};

	template <typename RVAL, typename T1, typename T2, typename T3>
	struct message<RVAL, T1, T2, T3> : public function
	{
		typedef RVAL (*FUNC)(T1 arg1, T2 arg2, T3 arg3);
		FUNC func;
		void bind(FUNC func)
		{
			this->func = func;
		}
		int call(const char *content, unsigned int len)
		{
			BEGIN_PARSE
			PASRE_ARG(T1, t1);
			PASRE_ARG(T2, t2);
			PASRE_ARG(T3, t3);
			GF_CALL(t1, t2, t3);
		}
		std::string build(T1 arg1, T2 arg2, T3 arg3)
		{
			BEGIN_STREAM
			TO_STREAM(arg1);
			TO_STREAM(arg2);
			TO_STREAM(arg3);

			END_STREAM
		}
	};

	template <typename RVAL, typename T, typename T1, typename T2, typename T3>
	struct omessage<RVAL, T, T1, T2, T3> : public function
	{
		typedef RVAL (T::*FUNC)(T1 arg1, T2 arg2, T3 arg3);
		FUNC func;
		void bind(FUNC func)
		{
			this->func = func;
		}
		int call(void *object, const char *content, unsigned int len)
		{
			BEGIN_PARSE
			PASRE_ARG(T1, t1);
			PASRE_ARG(T2, t2);
			PASRE_ARG(T3, t3);
			OF_CALL(t1, t2, t3);
		}
		std::string build(T1 arg1, T2 arg2, T3 arg3)
		{
			BEGIN_STREAM
			TO_STREAM(arg1);
			TO_STREAM(arg2);
			TO_STREAM(arg3);
			END_STREAM
		}
	};

	template <typename RVAL, typename T1, typename T2>
	struct message<RVAL, T1, T2> : public function
	{
		typedef RVAL (*FUNC)(T1 arg1, T2 arg2);
		FUNC func;
		void bind(FUNC func)
		{
			this->func = func;
		}
		int call(const char *content, unsigned int len)
		{
			BEGIN_PARSE
			PASRE_ARG(T1, t1);
			PASRE_ARG(T2, t2);
			GF_CALL(t1, t2);
		}
		std::string build(T1 arg1, T2 arg2)
		{
			BEGIN_STREAM
			TO_STREAM(arg1);
			TO_STREAM(arg2);
			END_STREAM
		}
	};

	template <typename RVAL, typename T, typename T1, typename T2>
	struct omessage<RVAL, T, T1, T2> : public function
	{
		typedef RVAL (T::*FUNC)(T1 arg1, T2 arg2);
		FUNC func;
		void bind(FUNC func)
		{
			this->func = func;
		}
		int call(void *object, const char *content, unsigned int len)
		{
			BEGIN_PARSE
			PASRE_ARG(T1, t1);
			PASRE_ARG(T2, t2);
			OF_CALL(t1, t2);
		}
		std::string build(T1 arg1, T2 arg2)
		{
			BEGIN_STREAM
			TO_STREAM(arg1);
			TO_STREAM(arg2);
			END_STREAM
		}
	};

	template <typename RVAL, typename T1>
	struct message<RVAL, T1> : public function
	{
		typedef RVAL (*FUNC)(T1 arg1);
		FUNC func;
		void bind(FUNC func)
		{
			this->func = func;
		}
		int call(const char *content, unsigned int len)
		{
			BEGIN_PARSE
			PASRE_ARG(T1, t1);
			GF_CALL(t1);
		}
		std::string build(T1 arg1)
		{
			BEGIN_STREAM
			TO_STREAM(arg1);
			END_STREAM
		}
	};
	template <typename RVAL, typename T, typename T1>
	struct omessage<RVAL, T, T1> : public function
	{
		typedef RVAL (T::*FUNC)(T1 arg1);
		FUNC func;
		void bind(FUNC func)
		{
			this->func = func;
		}
		int call(void *object, const char *content, unsigned int len)
		{
			BEGIN_PARSE
			PASRE_ARG(T1, t1);
			OF_CALL(t1);
		}
		std::string build(T1 arg1)
		{
			BEGIN_STREAM
			TO_STREAM(arg1);
			END_STREAM
		}
	};
	class Messages
	{
	public:
		std::map<std::string, function *> name_messages;
		typedef std::map<std::string, function *>::iterator NAME_MESSAGES_ITER;
		static Messages &getMe()
		{
			static Messages msg;
			return msg;
		}
		void addMessage(const std::string &name, function *func)
		{
			name_messages[name] = func;
		}
		function *getMessage(const std::string &name)
		{
			NAME_MESSAGES_ITER iter = name_messages.find(name);
			if (iter != name_messages.end())
			{
				return iter->second;
			}
			return NULL;
		}
		std::vector<function *> id_messages;
		void addMessage(unsigned short index, function *func)
		{
			if (index > id_messages.size())
				id_messages.resize(index + 1);
			id_messages[index] = func;
		}
		function *getMessage(unsigned short index)
		{
			if (index < id_messages.size())
			{
				return id_messages[index];
			}
			return NULL;
		}

		std::vector<std::vector<function *>> xy_messages;
		void addMessage(unsigned char x, unsigned char y, function *func)
		{
			if (x < xy_messages.size())
				xy_messages.resize(x + 1);
			if (y < xy_messages[x].size())
				xy_messages[x].resize(y + 1);
			xy_messages[x][y] = func;
		}
		function *getMessage(unsigned char x, unsigned char y)
		{
			if (x < xy_messages.size())
			{
				if (y < xy_messages[x].size())
				{
					return xy_messages[x][y];
				}
			}
			return NULL;
		}
	};

	template <typename T>
	int call(T *object, const char *content, unsigned int size)
	{
		cmd::BinaryStream ss;
		ss.set((void *)content, size);
		std::string name;
		parseStream(name, &ss);
		function *msg = Messages::getMe().getMessage(name.c_str());
		if (msg)
		{
			return msg->call(object, content, size);
		}
		return -1;
	}

	template <typename T>
	int call_id(T *object, const char *content, unsigned int size)
	{
		cmd::BinaryStream ss;
		ss.set((void *)content, size);
		unsigned short index = 0;
		parseStream(index, &ss);
		function *msg = Messages::getMe().getMessage(index);
		if (msg)
		{
			return msg->call(object, content, size);
		}
		return -1;
	}

	template <typename T>
	int call_xy(T *object, const char *content, unsigned int size)
	{
		cmd::BinaryStream ss;
		ss.set((void *)content, size);
		unsigned char x = 0;
		unsigned char y = 0;
		parseStream(x, &ss);
		parseStream(y, &ss);
		function *msg = Messages::getMe().getMessage(x, y);
		if (msg)
		{
			msg->call(object, content, size);
			return true;
		}
		return false;
	}
	// 一个参数
	template <typename INDEX, typename RVAL, typename T1>
	void bind(INDEX name, RVAL (*func)(T1 arg1))
	{
		message<RVAL, typename charstostring<T1>::type> *msg = new message<RVAL, typename charstostring<T1>::type>();
		msg->bind(func);
		func->set(name);
		Messages::getMe().addMessage(name, msg);
	}
	template <typename INDEX, typename RVAL, typename T, typename T1>
	void bind(INDEX name, RVAL (T::*func)(T1 arg1))
	{
		omessage<RVAL, T, T1> *mes = new omessage<RVAL, T, T1>();
		mes->bind(func);
		mes->set(name);
		Messages::getMe().addMessage(name, mes);
	}

	template <typename INDEX, typename RVAL, typename T1>
	std::string build(INDEX func, T1 t1)
	{
		message<RVAL, typename charstostring<T1>::type> msg;
		msg.set(func);
		return msg.build(t1);
	}

	// 两个参数
	template <typename INDEX, typename RVAL, typename T1, typename T2>
	void bind(INDEX name, RVAL (*func)(T1 arg1, T2 arg2))
	{
		message<RVAL, typename charstostring<T1>::type, typename charstostring<T2>::type> *msg = new message<RVAL, typename charstostring<T1>::type, typename charstostring<T2>::type>();
		msg->bind(func);
		func->set(name);
		Messages::getMe().addMessage(name, msg);
	}
	template <typename INDEX, typename RVAL, typename T, typename T1, typename T2>
	void bind(INDEX name, RVAL (T::*func)(T1 arg1, T2 arg2))
	{
		omessage<RVAL, T, T1, T2> *message = new omessage<RVAL, T, T1, T2>();
		message->bind(func);
		message->set(name);
		Messages::getMe().addMessage(name, message);
	}

	template <typename INDEX, typename RVAL, typename T1, typename T2>
	std::string build(INDEX func, T1 t1, T2 t2)
	{
		message<RVAL, typename charstostring<T1>::type, typename charstostring<T2>::type> msg;
		msg.set(func);
		return msg.build(t1, t2);
	}
	// 三个参数
	template <typename INDEX, typename RVAL, typename T1, typename T2, typename T3>
	void bind(INDEX name, RVAL (*func)(T1 arg1, T2 arg2, T3 arg3))
	{
		message<RVAL, typename charstostring<T1>::type, typename charstostring<T2>::type, typename charstostring<T3>::type> *msg =
			new message<RVAL, typename charstostring<T1>::type, typename charstostring<T2>::type, typename charstostring<T3>::type>();
		msg->bind(func);
		func->set(name);
		Messages::getMe().addMessage(name, msg);
	}
	template <typename INDEX, typename RVAL, typename T, typename T1, typename T2, typename T3>
	void bind(INDEX name, RVAL (T::*func)(T1 arg1, T2 arg2, T3 arg3))
	{
		omessage<RVAL, T, T1, T2, T3> *message = new omessage<RVAL, T, T1, T2, T3>();
		message->bind(func);
		message->set(name);
		Messages::getMe().addMessage(name, message);
	}

	template <typename INDEX, typename RVAL, typename T1, typename T2, typename T3>
	std::string build(INDEX func, T1 t1, T2 t2, T3 t3)
	{
		message<RVAL, typename charstostring<T1>::type, typename charstostring<T2>::type, typename charstostring<T3>::type> msg;
		msg.set(func);
		return msg.build(t1, t2, t3);
	}

	// 四个参数
	template <typename INDEX, typename RVAL, typename T1, typename T2, typename T3, typename T4>
	void bind(INDEX name, RVAL (*func)(T1 arg1, T2 arg2, T3 arg3, T4 arg4))
	{
		message<RVAL, typename charstostring<T1>::type, typename charstostring<T2>::type, typename charstostring<T3>::type, typename charstostring<T4>::type> *msg =
			new message<RVAL, typename charstostring<T1>::type, typename charstostring<T2>::type, typename charstostring<T3>::type, typename charstostring<T4>::type>();
		msg->bind(func);
		func->set(name);
		Messages::getMe().addMessage(name, msg);
	}
	template <typename INDEX, typename RVAL, typename T, typename T1, typename T2, typename T3, typename T4>
	void bind(INDEX name, RVAL (T::*func)(T1 arg1, T2 arg2, T3 arg3, T4 arg4))
	{
		omessage<RVAL, T, T1, T2, T3, T4> *message = new omessage<RVAL, T, T1, T2, T3, T4>();
		message->bind(func);
		message->set(name);
		Messages::getMe().addMessage(name, message);
	}

	template <typename INDEX, typename RVAL, typename T1, typename T2, typename T3, typename T4>
	std::string build(INDEX func, T1 t1, T2 t2, T3 t3, T4 t4)
	{
		message<RVAL, typename charstostring<T1>::type, typename charstostring<T2>::type, typename charstostring<T3>::type, typename charstostring<T4>::type> msg;
		msg.set(func);
		return msg.build(t1, t2, t3, t4);
	}
	// 五个参数
	template <typename INDEX, typename RVAL, typename T1, typename T2, typename T3, typename T4, typename T5>
	void bind(INDEX name, RVAL (*func)(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5))
	{
		message<RVAL, typename charstostring<T1>::type, typename charstostring<T2>::type, typename charstostring<T3>::type, typename charstostring<T4>::type, typename charstostring<T5>::type> *msg =
			new message<RVAL, typename charstostring<T1>::type, typename charstostring<T2>::type, typename charstostring<T3>::type, typename charstostring<T4>::type, typename charstostring<T5>::type>();
		msg->bind(func);
		func->set(name);
		Messages::getMe().addMessage(name, msg);
	}
	template <typename INDEX, typename RVAL, typename T, typename T1, typename T2, typename T3, typename T4, typename T5>
	void bind(INDEX name, RVAL (T::*func)(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5))
	{
		omessage<RVAL, T, T1, T2, T3, T4, T5> *message = new omessage<RVAL, T, T1, T2, T3, T4, T5>();
		message->bind(func);
		message->set(name);
		Messages::getMe().addMessage(name, message);
	}

	template <typename INDEX, typename RVAL, typename T1, typename T2, typename T3, typename T4, typename T5>
	std::string build(INDEX func, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
	{
		message<RVAL, typename charstostring<T1>::type, typename charstostring<T2>::type, typename charstostring<T3>::type, typename charstostring<T4>::type, typename charstostring<T5>::type> msg;
		msg.set(func);
		return msg.build(t1, t2, t3, t4, t5);
	}
}

#pragma pack(1)
struct LogicHeadProto
{
	LogicHeadProto(int id) : logicId(id)
	{
	}
	LogicHeadProto() {}
	int logicId = 0;
	int sessionId = 0;
};

const int REMOTE_CALL_LOIGC_ID = 1;
const int REMOTE_CALL_LOGIC_WITH_EXPECT = 2;
const int REMOTE_CALL_LOGIC_WITH_EXPECT_OBJ = 3;
const int REMOTE_CALL_LOGIC_WITH_EXPECT_PROMISE = 4;
#pragma pack()

class ICallback
{
public:
	virtual ~ICallback()
	{
	}
};

template <typename T>
class Callback : public ICallback
{
public:
	T action;
	Callback(const T &action) : action(action)
	{
	}
	T *operator->()
	{
		return &action;
	}
};

template <typename T>
class CallbackPromise : public ICallback
{
public:
	std::promise<T> *prom = NULL;
	CallbackPromise(void *action)
	{
		prom = (std::promise<T> *)action;
	}
	void set_value(const T &t)
	{
		prom->set_value(t);
	}
};

class CallbackIntPromise : public ICallback
{
public:
	std::promise<int> *waitPromise = NULL;
};

template <typename T>
class CallbackWithPromise : public CallbackIntPromise
{
public:
	T action;
	CallbackWithPromise(const T &action, std::promise<int> *prom)
	{
		this->action = action;
		this->waitPromise = prom;
	}
	T *operator->()
	{
		return &action;
	}
};

class ExecEnvironment
{
public:
	virtual ~ExecEnvironment() {}
	template <typename T>
	T *addComponent(const std::string &name)
	{
		auto i = _components.find(name);
		if (i == _components.end())
		{
			std::string vv;
			vv.resize(sizeof(T) + 4);

			auto ii = _components.insert({name, vv});
			if (ii.second)
			{
				return new (&ii.first->second[0]) T;
			}
			return NULL;
		}
		else
		{
			return static_cast<T *>((void *)&i->second[0]);
		}
	}
	std::string *getAlloc(const std::string &name)
	{
		auto i = _components.find(name);
		if (i == _components.end())
		{
			std::string vv;
			auto ii = _components.insert({name, vv});
			if (ii.second)
			{
				return &ii.first->second;
			}
			return NULL;
		}
		else
		{
			return &i->second;
		}
	}
	template <typename T>
	T *getComponent(const std::string &name)
	{
		auto it = _components.find(name);
		if (it != _components.end())
		{
			return static_cast<T *>((void *)&it->second[0]);
		}
		return NULL;
	}
	char *getComponent(const std::string &name)
	{
		auto it = _components.find(name);
		if (it != _components.end())
		{
			return &it->second[0];
		}
		return NULL;
	}

private:
	std::map<std::string, std::string> _components;
};
class IStubHandler;
class IStub;
typedef std::function<int(IStubHandler *, ExecEnvironment &, void *)> callback_func;

class StubExecScope
{
public:
	IStub *stub;
	StubExecScope(IStub *stub);
	~StubExecScope();
};

#define STUB_EXEC_SCOPE StubExecScope scope##__LINE__(this);

class IStub : public ExecEnvironment
{
public:
	enum
	{
		SERVER = 1,
		CLIENT,
		SESSION,
	};
	int sessionId = 0;
	int stubType = 0;
	int socket = -1;
	ICallback *callback = NULL;
	enum
	{
		INVALID_CALLBACK = 0,
		OBJECT_CALLBACK = 1,
		FUNCTION_CALLBACK = 2,
		PROMISE_FUNCTION_CALLBACK = 3,
	} callbackType = INVALID_CALLBACK;
	virtual bool beginCall()
	{
		return true;
	}
	virtual void endCall()
	{
	}

	void sendProto(LogicHeadProto *proto, int len)
	{
		sendData(proto, len);
		int ret;
		recvData(&ret, sizeof(int));
	}

	void exec(const callback_func &callback)
	{
		expect_call("ExecuteLogic::exec", 1, callback);
	}

	void exec_promise(const callback_func &callback)
	{
		expect_promise_call("ExecutePromiseLogic::exec", 1, callback);
	}
	virtual int sendData(void *data, int len);
	virtual int recvData(void *data, int len);

	virtual int sendRaw(void *data, int len);

	/**
	 * invoke
	 * */
	template <typename CALLBACK, typename T1>
	CALLBACK invoke(const std::string &name, T1 t1)
	{
		STUB_EXEC_SCOPE;
		std::promise<CALLBACK> prom;
		auto fut = prom.get_future();
		unsigned long long cValue = (unsigned long long)(&prom);
		std::string content = remote::build<std::string, int>(name, t1);
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), true, REMOTE_CALL_LOGIC_WITH_EXPECT_OBJ, cValue);
		return fut.get();
	}
	template <typename CALLBACK, typename T1, typename T2>
	CALLBACK invoke(const std::string &name, T1 t1, T2 t2)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2);
		std::promise<CALLBACK> prom;
		auto fut = prom.get_future();
		unsigned long long cValue = (unsigned long long)(&prom);
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), true, REMOTE_CALL_LOGIC_WITH_EXPECT_OBJ, cValue);
		return fut.get();
	}

	template <typename CALLBACK, typename T1, typename T2, typename T3>
	CALLBACK invoke(const std::string &name, T1 t1, T2 t2, T3 t3)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2, t3);
		std::promise<CALLBACK> prom;
		auto fut = prom.get_future();
		unsigned long long cValue = (unsigned long long)(&prom);
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), true, REMOTE_CALL_LOGIC_WITH_EXPECT_OBJ, cValue);
		return fut.get();
	}
	template <typename CALLBACK, typename T1, typename T2, typename T3, typename T4>
	CALLBACK invoke(const std::string &name, T1 t1, T2 t2, T3 t3, T4 t4)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2, t3, t4);
		std::promise<CALLBACK> prom;
		auto fut = prom.get_future();
		unsigned long long cValue = (unsigned long long)(&prom);
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), true, REMOTE_CALL_LOGIC_WITH_EXPECT_OBJ, cValue);
		return fut.get();
	}
	template <typename CALLBACK, typename T1, typename T2, typename T3, typename T4, typename T5>
	CALLBACK invoke(const std::string &name, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2, t3, t4, t5);
		std::promise<CALLBACK> prom;
		auto fut = prom.get_future();
		unsigned long long cValue = (unsigned long long)(&prom);
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), true, REMOTE_CALL_LOGIC_WITH_EXPECT_OBJ, cValue);
		return fut.get();
	}

	template <typename T1, typename CALLBACK>
	void expect_obj(const std::string &name, T1 t1, CALLBACK &callback)
	{
		STUB_EXEC_SCOPE;
		std::promise<CALLBACK> prom;
		auto fut = prom.get_future();
		unsigned long long cValue = (unsigned long long)(&prom);
		std::string content = remote::build<std::string, int>(name, t1);
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), true, REMOTE_CALL_LOGIC_WITH_EXPECT_OBJ, cValue);
		callback = fut.get();
		return;
	}
	template <typename T1, typename T2, typename CALLBACK>
	void expect_obj(const std::string &name, T1 t1, T2 t2, CALLBACK &callback)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2);
		std::promise<CALLBACK> prom;
		auto fut = prom.get_future();
		unsigned long long cValue = (unsigned long long)(&prom);
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), true, REMOTE_CALL_LOGIC_WITH_EXPECT_OBJ, cValue);
		callback = fut.get();
		return;
	}

	template <typename T1, typename T2, typename T3, typename CALLBACK>
	void expect_obj(const std::string &name, T1 t1, T2 t2, T3 t3, CALLBACK callback)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2, t3);
		std::promise<CALLBACK> prom;
		auto fut = prom.get_future();
		unsigned long long cValue = (unsigned long long)(&prom);
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), true, REMOTE_CALL_LOGIC_WITH_EXPECT_OBJ, cValue);
		callback = fut.get();
	}
	template <typename T1, typename T2, typename T3, typename T4, typename CALLBACK>
	void expect_obj(const std::string &name, T1 t1, T2 t2, T3 t3, T4 t4, CALLBACK callback)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2, t3, t4);
		std::promise<CALLBACK> prom;
		auto fut = prom.get_future();
		unsigned long long cValue = (unsigned long long)(&prom);
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), true, REMOTE_CALL_LOGIC_WITH_EXPECT_OBJ, cValue);
		callback = fut.get();
	}
	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename CALLBACK>
	void expect_obj(const std::string &name, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, CALLBACK callback)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2, t3, t4, t5);
		std::promise<CALLBACK> prom;
		auto fut = prom.get_future();
		unsigned long long cValue = (unsigned long long)(&prom);
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), true, REMOTE_CALL_LOGIC_WITH_EXPECT_OBJ, cValue);
		callback = fut.get();
	}

	template <typename T1, typename CALLBACK>
	void expect_promise_call(const std::string &name, T1 t1, CALLBACK callback)
	{
		STUB_EXEC_SCOPE;
		std::promise<int> prom;
		CallbackWithPromise<CALLBACK> c(callback, &prom);

		auto fut = prom.get_future();
		unsigned long long cValue = (unsigned long long)&c;
		std::string content = remote::build<std::string, int>(name, t1);
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), true, REMOTE_CALL_LOGIC_WITH_EXPECT_PROMISE, cValue);
		fut.get();
		return;
	}
	template <typename T1, typename T2, typename CALLBACK>
	void expect_promise_call(const std::string &name, T1 t1, T2 t2, CALLBACK callback)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2);
		std::promise<int> prom;
		CallbackWithPromise<CALLBACK> c(callback, &prom);
		auto fut = prom.get_future();
		unsigned long long cValue = (unsigned long long)&c;
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), true, REMOTE_CALL_LOGIC_WITH_EXPECT_PROMISE, cValue);
		fut.get();
	}
	template <typename T1, typename T2, typename T3, typename CALLBACK>
	void expect_promise_call(const std::string &name, T1 t1, T2 t2, T3 t3, CALLBACK callback)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2, t3);
		std::promise<int> prom;
		CallbackWithPromise<CALLBACK> c(callback, &prom);
		auto fut = prom.get_future();
		unsigned long long cValue = (unsigned long long)&c;
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), true, REMOTE_CALL_LOGIC_WITH_EXPECT_PROMISE, cValue);
		fut.get();
	}
	template <typename T1, typename T2, typename T3, typename T4, typename CALLBACK>
	void expect_promise_call(const std::string &name, T1 t1, T2 t2, T3 t3, T4 t4, CALLBACK callback)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2, t3, t4);
		std::promise<int> prom;
		CallbackWithPromise<CALLBACK> c(callback, &prom);
		auto fut = prom.get_future();
		unsigned long long cValue = (unsigned long long)&c;
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), true, REMOTE_CALL_LOGIC_WITH_EXPECT_PROMISE, cValue);
		fut.get();
	}
	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename CALLBACK>
	void expect_promise_call(const std::string &name, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, CALLBACK callback)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2, t3, t4, t5);
		std::promise<int> prom;
		CallbackWithPromise<CALLBACK> c(callback, &prom);
		auto fut = prom.get_future();
		unsigned long long cValue = (unsigned long long)&c;
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), true, REMOTE_CALL_LOGIC_WITH_EXPECT_PROMISE, cValue);
		fut.get();
	}

	template <typename T1, typename CALLBACK>
	void expect_call(const std::string &name, T1 t1, CALLBACK callback)
	{
		STUB_EXEC_SCOPE;
		Callback<CALLBACK> *c = new Callback<CALLBACK>(callback);
		unsigned long long cValue = (unsigned long long)c;
		std::string content = remote::build<std::string, int>(name, t1);
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), true, REMOTE_CALL_LOGIC_WITH_EXPECT, cValue);

		return;
	}
	template <typename T1, typename T2, typename CALLBACK>
	void expect_call(const std::string &name, T1 t1, T2 t2, CALLBACK callback)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2);
		Callback<CALLBACK> *c = new Callback<CALLBACK>(callback);
		unsigned long long cValue = (unsigned long long)c;
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), true, REMOTE_CALL_LOGIC_WITH_EXPECT, cValue);
	}
	template <typename T1, typename T2, typename T3, typename CALLBACK>
	void expect_call(const std::string &name, T1 t1, T2 t2, T3 t3, CALLBACK callback)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2, t3);
		Callback<CALLBACK> *c = new Callback<CALLBACK>(callback);
		unsigned long long cValue = (unsigned long long)c;
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), true, REMOTE_CALL_LOGIC_WITH_EXPECT, cValue);
	}
	template <typename T1, typename T2, typename T3, typename T4, typename CALLBACK>
	void expect_call(const std::string &name, T1 t1, T2 t2, T3 t3, T4 t4, CALLBACK callback)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2, t3, t4);
		Callback<CALLBACK> *c = new Callback<CALLBACK>(callback);
		unsigned long long cValue = (unsigned long long)c;
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), true, REMOTE_CALL_LOGIC_WITH_EXPECT, cValue);
	}
	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename CALLBACK>
	void expect_call(const std::string &name, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, CALLBACK callback)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2, t3, t4, t5);
		Callback<CALLBACK> *c = new Callback<CALLBACK>(callback);
		unsigned long long cValue = (unsigned long long)c;
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), true, REMOTE_CALL_LOGIC_WITH_EXPECT, cValue);
	}

	template <typename T1, typename CALLBACK>
	void async_expect_call(const std::string &name, T1 t1, CALLBACK callback)
	{
		STUB_EXEC_SCOPE;
		Callback<CALLBACK> *c = new Callback<CALLBACK>(callback);
		unsigned long long cValue = (unsigned long long)c;
		std::string content = remote::build<std::string, int>(name, t1);
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), false, REMOTE_CALL_LOGIC_WITH_EXPECT, cValue);
	}
	template <typename T1, typename T2, typename CALLBACK>
	void async_expect_call(const std::string &name, T1 t1, T2 t2, CALLBACK callback)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2);
		Callback<CALLBACK> *c = new Callback<CALLBACK>(callback);
		unsigned long long cValue = (unsigned long long)c;
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), false, REMOTE_CALL_LOGIC_WITH_EXPECT, cValue);
	}
	template <typename T1, typename T2, typename T3, typename CALLBACK>
	void async_expect_call(const std::string &name, T1 t1, T2 t2, T3 t3, CALLBACK callback)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2, t3);
		Callback<CALLBACK> *c = new Callback<CALLBACK>(callback);
		unsigned long long cValue = (unsigned long long)c;
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), false, REMOTE_CALL_LOGIC_WITH_EXPECT, cValue);
	}
	template <typename T1, typename T2, typename T3, typename T4, typename CALLBACK>
	void async_expect_call(const std::string &name, T1 t1, T2 t2, T3 t3, T4 t4, CALLBACK callback)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2, t3, t4);
		Callback<CALLBACK> *c = new Callback<CALLBACK>(callback);
		unsigned long long cValue = (unsigned long long)c;
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), false, REMOTE_CALL_LOGIC_WITH_EXPECT, cValue);
	}
	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename CALLBACK>
	void async_expect_call(const std::string &name, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, CALLBACK callback)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2, t3, t4, t5);
		Callback<CALLBACK> *c = new Callback<CALLBACK>(callback);
		unsigned long long cValue = (unsigned long long)c;
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), false, REMOTE_CALL_LOGIC_WITH_EXPECT, cValue);
	}

	template <typename T1>
	void call(const std::string &name, T1 t1)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1);
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size());
	}
	template <typename T1, typename T2>
	void call(const std::string &name, T1 t1, T2 t2)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2);
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size());
	}
	template <typename T1, typename T2, typename T3>
	void call(const std::string &name, T1 t1, T2 t2, T3 t3)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2, t3);
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size());
	}
	template <typename T1, typename T2, typename T3, typename T4>
	void call(const std::string &name, T1 t1, T2 t2, T3 t3, T4 t4)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2, t3, t4);
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size());
	}
	template <typename T1, typename T2, typename T3, typename T4, typename T5>
	void call(const std::string &name, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2, t3, t4, t5);
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size());
	}

	template <typename T1>
	void async_call(const std::string &name, T1 t1)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1);
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), false);
	}
	template <typename T1, typename T2>
	void async_call(const std::string &name, T1 t1, T2 t2)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2);
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), false);
	}
	template <typename T1, typename T2, typename T3>
	void async_call(const std::string &name, T1 t1, T2 t2, T3 t3)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2, t3);
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), false);
	}
	template <typename T1, typename T2, typename T3, typename T4>
	void async_call(const std::string &name, T1 t1, T2 t2, T3 t3, T4 t4)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2, t3, t4);
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), false);
	}
	template <typename T1, typename T2, typename T3, typename T4, typename T5>
	void async_call(const std::string &name, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
	{
		STUB_EXEC_SCOPE;
		std::string content = remote::build<std::string, int>(name, t1, t2, t3, t4, t5);
		if (content.size())
			sendCallData(name, (void *)&content[0], content.size(), false);
	}

	void sendCallData(const std::string &name, void *content, int size, bool isSync = true, int logicId = REMOTE_CALL_LOIGC_ID, unsigned long long appendData = 0)
	{
		std::string packContent;
		std::string className = getClassName(name);
		// get classname
		if (logicId == REMOTE_CALL_LOIGC_ID)
			packContent.resize(size + sizeof(LogicHeadProto) + sizeof(int) + className.size());
		else
			packContent.resize(size + sizeof(LogicHeadProto) + sizeof(int) + className.size() + sizeof(appendData));
		LogicHeadProto proto;
		proto.logicId = logicId;
		proto.sessionId = sessionId;
		// printf("sendCallData sessionId:%d\n",sessionId);
		memcpy(&packContent[0], &proto, sizeof(proto)); // push logicid
		int nameSize = className.size();
		memcpy(&packContent[sizeof(LogicHeadProto)], &nameSize, sizeof(int)); // push remote name
		memcpy(&packContent[sizeof(LogicHeadProto) + sizeof(int)], className.c_str(), nameSize);

		if (logicId == REMOTE_CALL_LOIGC_ID)
		{
			memcpy(&packContent[sizeof(LogicHeadProto) + sizeof(int) + nameSize], content, size);
		}
		if (logicId == REMOTE_CALL_LOGIC_WITH_EXPECT || logicId == REMOTE_CALL_LOGIC_WITH_EXPECT_OBJ || logicId == REMOTE_CALL_LOGIC_WITH_EXPECT_PROMISE)
		{
			memcpy(&packContent[sizeof(LogicHeadProto) + sizeof(int) + nameSize], &appendData, sizeof(appendData)); // push appendData
			memcpy(&packContent[sizeof(LogicHeadProto) + sizeof(int) + nameSize + sizeof(appendData)], content, size);
			// printf("setCallData 0x%llx \n", appendData);
		}

		sendData(&packContent[0], packContent.size());

		if (isSync)
		{
			int ret;
			// printf("等待唤醒 %s\n", name.c_str());
			recvData(&ret, sizeof(int));
			// printf("成功唤醒:%s\n", name.c_str());
		}
	}
	void awake()
	{
		if (callback && callbackType == IStub::PROMISE_FUNCTION_CALLBACK)
		{
			((CallbackIntPromise *)callback)->waitPromise->set_value(1);
		}
		int ret = 2;
		sendRaw(&ret, sizeof(int));
	}
	std::string getClassName(const std::string &name)
	{
		std::string temp;
		const char *tmpName = name.c_str();
		while (*tmpName != '\0')
		{
			if (*tmpName == ':')
			{
				break;
			}
			temp.push_back(*tmpName);
			tmpName++;
		}
		temp.push_back('\0');
		return temp;
	}

	bool has_func_repsonse()
	{
		return callback != NULL && callbackType == IStub::FUNCTION_CALLBACK;
	}
	bool has_promise_func_repsonse()
	{
		return callback != NULL && callbackType == IStub::PROMISE_FUNCTION_CALLBACK;
	}
	bool has_obj_repsonse()
	{
		return callback != NULL && callbackType == IStub::OBJECT_CALLBACK;
	}
	template <typename T>
	T &response_func()
	{
		// printf("repsonse %p\n", stub->callback);
		static T t;
		if (callback)
		{
			Callback<T> *t = (Callback<T> *)callback;
			return t->action;
		}
		return t;
	}
	template <typename T>
	T &response_promise_func()
	{
		// printf("repsonse %p\n", stub->callback);
		static T t;
		if (callback)
		{
			CallbackWithPromise<T> *t = (CallbackWithPromise<T> *)callback;
			return t->action;
		}
		return t;
	}
	template <typename T>
	void response_obj(const T &obj)
	{
		if (callback && callbackType == IStub::OBJECT_CALLBACK)
		{
			CallbackPromise<T> callb(callback);
			callb.set_value(obj);
		}
	}
};

class StubClient : public IStub
{
public:
	StubClient()
	{
		stubType = CLIENT;
	}

	virtual ~StubClient()
	{
	}
	bool connect();
};
class StubSession : public IStub
{
public:
	StubSession()
	{
		stubType = SESSION;
	}
	std::string body;
	bool init(int socket);
	bool addEvent(int epollHandler, int events);
	bool delEvent(int epollHandler, int events);
};

class StubShortClient : public StubClient
{
public:
	StubShortClient() : StubClient()
	{
	}
	bool beginCall();
	void endCall();
};

class IStubHandler
{
public:
	IStub *stub = NULL;

	virtual int handle(IStub *stub, void *data, int len) = 0;

	void clearStub()
	{
		if (stub->callback && stub->callbackType == IStub::FUNCTION_CALLBACK)
		{
			delete stub->callback;
			// printf("clearStub %p", stub->callback);
			stub->callback = NULL;
		}
		stub = NULL;
	}

	static std::map<int, IStub *> blockTags;

	void block(const int &id)
	{
		blockTags[id] = stub;
	}
	IStub *peek_block(const int &id)
	{
		auto it = blockTags.find(id);
		if (it != blockTags.end())
		{ // 如果有等待对象解锁
			auto ii = it->second;
			blockTags.erase(it);
			return ii;
		}
		return NULL;
	}
	template <typename T>
	T *peek(const int &id)
	{
		return (T *)peek_block(id);
	}
	void awake()
	{
		stub->awake();
	}

	static std::map<int, IStub *> _sessions;
	static IStub *findSession(int sessionId);
	static void addSession(int id, IStub *session);
	static void delSession(int id);
};
class StubLogic : public IStubHandler
{
public:
	virtual int handle(IStub *stub, void *data, int len)
	{
		return true;
	}
};
class ILogic : public IStubHandler
{
public:
	ILogic(const int &logicId) : logicId(logicId) {}
	int logicId = 0; // 逻辑编号
};

class Logic : public ILogic
{
public:
	Logic(int logicId) : ILogic(logicId)
	{
	}
};
#define BLOCK 0
#define NON_BLOCK 1
class RemoteCallLogic : public Logic
{
public:
	RemoteCallLogic() : Logic(REMOTE_CALL_LOIGC_ID)
	{
	}
	int handle(IStub *stub, void *data, int len)
	{
		int nameSize = *(int *)((char *)data + sizeof(LogicHeadProto));
		std::string name;
		name.resize(nameSize);
		memcpy(&name[0], ((char *)data + sizeof(LogicHeadProto) + sizeof(int)), nameSize);

		auto iter = stubHandlers->find(name.c_str());
		if (iter != stubHandlers->end())
		{
			iter->second->stub = stub;
			int ret = remote::call(iter->second, (char *)data + sizeof(LogicHeadProto) + sizeof(int) + nameSize, len);
			if (ret == BLOCK)
			{
				return 0;
			}
			iter->second->stub = NULL;
		}
		else
		{
			printf("出错了 没找到 stub 处理器:%s\n", name.c_str());
		}

		stub->awake();

		return 0;
	}
	std::map<std::string, IStubHandler *> *stubHandlers;
};

class RemoteCallLogicBase : public Logic
{
public:
	RemoteCallLogicBase(int logicType) : Logic(logicType)
	{
	}
	int handle(IStub *stub, void *data, int len)
	{
		LogicHeadProto *proto = (LogicHeadProto *)data;
		int nameSize = *(int *)((char *)data + sizeof(LogicHeadProto));
		std::string name;
		name.resize(nameSize);
		memcpy(&name[0], ((char *)data + sizeof(LogicHeadProto) + sizeof(int)), nameSize);

		unsigned long long ptr = *(unsigned long long *)((char *)data + sizeof(LogicHeadProto) + sizeof(int) + nameSize);

		auto iter = stubHandlers->find(name.c_str());
		if (iter != stubHandlers->end())
		{
			iter->second->stub = stub;
			stub->sessionId = proto->sessionId;
			handleStub(stub);
			iter->second->stub->callback = (ICallback *)ptr;
			// printf("expect call %p name:%s session:%d\n", iter->second->stub->callback, name.c_str(), stub->sessionId);
			int ret = remote::call(iter->second, (char *)data + sizeof(LogicHeadProto) + sizeof(int) + nameSize + sizeof(unsigned long long), len);

			if (ret == BLOCK)
			{
				return 0;
			}
			iter->second->clearStub();
		}
		else
		{
			printf("出错了 没找到 stub 处理器:%s\n", name.c_str());
		}

		stub->awake();
		return 0;
	}
	virtual void handleStub(IStub *stub) = 0;
	std::map<std::string, IStubHandler *> *stubHandlers;
};

class RemoteCallLogicWithExpect : public RemoteCallLogicBase
{
public:
	RemoteCallLogicWithExpect() : RemoteCallLogicBase(REMOTE_CALL_LOGIC_WITH_EXPECT)
	{
	}
	void handleStub(IStub *stub)
	{
		stub->callbackType = IStub::FUNCTION_CALLBACK;
	}
};

class RemoteCallLogicWithExpectObj : public RemoteCallLogicBase
{
public:
	RemoteCallLogicWithExpectObj() : RemoteCallLogicBase(REMOTE_CALL_LOGIC_WITH_EXPECT_OBJ)
	{
	}
	void handleStub(IStub *stub)
	{
		stub->callbackType = IStub::OBJECT_CALLBACK;
	}
};

class RemoteCallLogicWithExpectPromise : public RemoteCallLogicBase
{
public:
	RemoteCallLogicWithExpectPromise() : RemoteCallLogicBase(REMOTE_CALL_LOGIC_WITH_EXPECT_PROMISE)
	{
	}
	void handleStub(IStub *stub)
	{
		stub->callbackType = IStub::PROMISE_FUNCTION_CALLBACK;
	}
};

class StubManager : public IStub
{
public:
	static StubManager &instance()
	{
		static StubManager sm;
		return sm;
	}
	bool init(int stubCount);
	StubManager()
	{
		stubType = SERVER;
	}
	IStub *createStub(int stubId = -1);
	IStub *createShortStub(int stubId = -1);
	void destroyStub(IStub *stub);

	void addLogic(ILogic *logic);

	void wait();

	void addStubHandler(const std::string &name, IStubHandler *stubHandler);

private:
	std::map<int, ILogic *> _logics;

	std::thread *workThread = NULL;

	int _serverSocket = -1;
	int _epollHandler = -1;
	bool _isRun = true;
	bool _initServerNode();
	IStub *_createClient(int clientId);
	IStub *_createShortClient(int clientId);
	bool _createSession(int socket);
	void _workThread();

	std::vector<struct epoll_event> readEventList;

	virtual int onMessage(IStub *session, void *data, int len);

	bool handleMessage(IStub *session, void *message, int len);

	RemoteCallLogic remoteCallLogic;
	RemoteCallLogicWithExpect remoteCallWithExpect;
	RemoteCallLogicWithExpectObj remoteCallWithExpectObj;
	RemoteCallLogicWithExpectPromise remoteCallWithExpectPromise;

	std::map<std::string, IStubHandler *> stubHandlers;
};

#define BIND_REMOVE_CALL(NAME) remote::bind(#NAME, &NAME)

#define REGISTER_REMOTE_MODULE(CLASSNAME)                                           \
	class AutoBindRemoteModule##CLASSNAME                                           \
	{                                                                               \
	public:                                                                         \
		CLASSNAME cls;                                                              \
		AutoBindRemoteModule##CLASSNAME(const std::string &name)                    \
		{                                                                           \
			StubManager::instance().addStubHandler(name, &cls);                     \
			registerBinders();                                                      \
		}                                                                           \
		void registerBinders();                                                     \
	};                                                                              \
	AutoBindRemoteModule##CLASSNAME a##AutoBindRemoteModule##CLASSNAME(#CLASSNAME); \
	void AutoBindRemoteModule##CLASSNAME::registerBinders()

#define R(name) #name

#define REMOTE_API(CLASS, API)   \
	static const char *API()     \
	{                            \
		return #CLASS "::" #API; \
	}

#endif // _MT_LOGIC_H