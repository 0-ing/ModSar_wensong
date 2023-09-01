// how to use non-stardard API to adapter the com

// 基本特征 非AP标准 自有实现规则呈现
// 1. 除依赖项配置外 本身零配置
// 2. C++ 代码一镜到底 业务无生成代码
// 3. 相对自然的method event field 的语义实现

// this example show how to define a rpc in service

// define the interface which this service can support

// IHelloService.h 接口文件
struct HelloData{
	int value;
};
class IHelloService {
public:
	// method
	virtual std::string returnStringFromSerice(const int& type) = 0;
	REMOTE_API(returnStringFromSerice);
	
	// event
	Event<HelloData> event;
	
	// field
	Field<HelloData> field;
}; 




// HelloProxy.cpp Proxy接口使用范例

int main()
{
	Proxy<IHelloService>()->event.subcrible([=](const Result<HelloData> &data) {
		// 事件响应
		if (data.state == OK)
		{
			// 处理逻辑
		}
	});
	Proxy<IHelloService>()->field.set(1); // Field 设置
	Result<HelloData> data = Proxy<IHelloService>()->field.get();
	if (data.state == OK)
	{
		// 演示获取行为
	}
	Result<std::string> ret = Proxy<IHelloService>()->invoke(IHelloService::returnStringFromSerice(),1);
	if (ret.state == OK)
	{
		std::cout << "proxy get string from service" << ret.value <<std::endl;
	}
	
}


// HelloService.cpp Skeleton 实现接口范例

class HelloService : public IHelloService {
public:
	std::string returnStringFromSerice(const int &type)
	{
		event.data = 2;
		event.notify(); // 演示 event 在skeleton 端的行为
		if (type == 1)
		{
			return "is 1 now from HelloProxy";
		}
		else if (type == 2)
		{
			return "is 2 now from HelloService";
		}
	}
	void init()
	{
		field.onGet([=](const HelloData &data){
			
		})
		
		field.onSet([=](const HelloData &data){
			// 演示 get / set 行为
		});
	}
};

REGISTER_SERVICE_WITH_NAME(HelloService,"hello")
{
	BIND_REMOTE_CALL(HelloService,returnStringFromSerice);
}