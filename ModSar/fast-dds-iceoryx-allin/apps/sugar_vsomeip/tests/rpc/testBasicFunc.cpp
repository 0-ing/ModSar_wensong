#include <functional>
#include <stdio.h>
class BasicMethod {
public:
	virtual void dispatch(void *stream,int size) = 0;
};

class BasicField :public BasicMethod{
public:

};
//support 10 args
template <typename RET, typename T1 = void, typename T2 = void, typename T3 = void, typename T4 = void, typename T5 = void, typename T6 = void>
class Method : public BasicMethod{
public:
    std::function<RET(T1,T2,T3,T4,T5,T6)> func;
    void dispatch(void*,int)
    {
        T1 t1;
        T2 t2;
        T3 t3;
        T4 t4;
        T5 t5;
        func(t1,t2,t3,t4,t5);
    }
};
template<typename RET>
class Method<RET> : public BasicMethod {
public:
	std::function<RET()> func;
	void dispatch(void *stream,int size)
	{
		func();
	}
	Method(std::function<RET()> func):func(func)
	{}
};


template<typename RET,typename A>
class Method<RET,A> : public BasicMethod {
public:
	std::function<RET(A)> func;
	void dispatch(void *stream,int size)
	{
		A a;
		func(a);
	}
	Method(std::function<RET(A)> func):func(func)
	{}
    Method(){}
    RET operator()(A a)
    {
        RET ret;
        printf("method invoked in proxy!\n");
        return ret;
    }
};

template<typename RET,typename CLASS,typename T1>
Method<RET,T1> bindrpc(CLASS *obj,RET (CLASS::*func)(T1 arg1))
{
    Method<RET,T1> m1(std::bind(func,obj,std::placeholders::_1));
    m1.dispatch(NULL,0);
    return m1;
}

template<typename RET,typename CLASS>
Method<RET> bindrpc(RET (CLASS::*func)())
{
    Method<RET> m1;
    m1.dispatch(NULL,0);
    return m1;
}

// support 6 count
template <typename T1 = void, typename T2 = void, typename T3 = void, typename T4 = void, typename T5 = void, typename T6 = void>
class Field : public BasicField{
public:
    T1 t1;
    T2 t2;
    void dispatch(void*,int) // run in skeleton
    {
    }
};
template<typename T1>
class Field<T1> : public BasicField {
public:
    T1 t1;
	void dispatch(void *stream,int size)
	{
	}
};


template<typename T1,typename T2>
class Field<T1,T2> : public BasicMethod {
public:
    T1 t1;
    T2 t2;
	void dispatch(void *stream,int size)
	{
        // 获取值并更新
	}
    Field(){}
    void set()
    {
        // handle set logic
    }
    void get()
    {
        // handle get logic
    }
    void onSet(const std::function<void()> &onSetCallback)
    {}

    void onGet(const std::function<void()> &onGetCallback)
    {

    }
    Field& operator()(T1 t1,T2 t2)
    {
        this->t1 = t1;
        this->t2 = t2;
        return *this;
    }
};

class Interface {
public:
    Method<int/**return type*/,int /**first argument*/> testFunc; // define a method
    Field<int/**first argument*/,int /**second argument*/ > testField; // define a field
};

class Implemation : public Interface {
public:
    void init()
    {
        testFunc = bindrpc(this,&Implemation::realAction);
        testField.onGet(std::bind(&Implemation::onGetTestField,this)); // skeleton
    }
    int realAction(int x)
    {
        printf("realAction %d\n",x);
        return 0;
    }
    void onGetTestField()
    {

    }
};

//REGISER_SKELETON(Implemation,"Hello");
//class HelloProxy : public Interface{
//public:
//    void onRead() {

//    };
//};

//REGISER_PROXY(HelloProxy,"Hello"); // bind service name

int main()
{
    //Interface *proxy = getProxy("Hello");
    //if (proxy)
    //{
       // handle logic
    //}
    Method<int>  m1([=]()->int{
        printf("m1\n");
        return 0;
    });

    m1.dispatch(NULL,0);

    Method<void,int>  m2 ( [=](int)->void{
        printf("m2\n");
    });
    m2.dispatch(NULL,0);

    Implemation imp;
    imp.init();

    imp.testFunc(1);


    imp.testField(1,1);
    imp.testField.get();
}
