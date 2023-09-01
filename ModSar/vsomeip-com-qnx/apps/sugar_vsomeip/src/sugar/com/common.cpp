#include "sugar/com/common.h"
#include <sstream>
#include <stdarg.h>
namespace sugar
{

    namespace com
    {
        int println(const char *fmt, ...)
        {
            char printf_buf[1024];
            va_list args;
            int printed;

            va_start(args, fmt);
            printed = vsprintf(printf_buf, fmt, args);
            va_end(args);

            puts(printf_buf);

            return printed;
        }
        void printbin(const char *xxx, void *content, int size)
        {
            std::stringstream ss;
            ss << xxx << "";
            char *pointer = (char *)content;
            for (int i = 0; i < size; ++i)
            {
                char temp[32] = {'\0'};
                sprintf(temp, " %d", (unsigned int)pointer[i]);
                ss << temp;
            }
            printf("%s\n", ss.str().c_str());
        }
        BasicObject::BasicObject(const std::string &file, int line,IProtocol *proto)
        {
            std::stringstream ss;
            ss << file << line;
            std::string name = ss.str();
            printf("BasicMethod::BasicMethod :%s line:%d\n", file.c_str(), line);
            for (auto it = name.rbegin(); it != name.rend(); ++it)
            {
                if (*it == '/' || *it == '\\')
                {
                    break;
                }
                head.uniqueTag.push_back(*it);
            }
            this->_proto = proto;
        }
        ISkeleton *BasicObject::getSkeleton()
        {
            if (this->_proto)
                return this->_proto->skeleton;
            return NULL;
        }
        IProxy *BasicObject::getProxy()
        {
            if (this->_proto)
                return this->_proto->proxy;
            return NULL;
        }
        void BasicObject::setProtocol(IProtocol *proto)
        {
            this->_proto = proto;
        }
        IProtocol *BasicObject::getProtocol()
        {
            return this->_proto;
        }
        BasicEvent::BasicEvent(const std::string &file, int line, IProtocol *proto) : BasicObject(file, line, proto)
        {
        }
        BasicField::BasicField(const std::string &file, int line, IProtocol *proto) : BasicEvent(file, line, proto)
        {
        }
        BasicMethod::BasicMethod(const std::string &file, int line, IProtocol *proto) : BasicObject(file, line, proto)
        {
        }
        IStub *getMainStub()
        {
            return StubManager::instance().getMainStub();
        }
    } // namespace com

} // namespace sugar
