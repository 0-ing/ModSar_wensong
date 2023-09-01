#include "protocol.h"
 
class HelloworldSkeleton : public sugar::Skeleton, public IHelloworldProto
{
public:
    HelloworldSkeleton(const sugar::InstanceIdentifier &instance_identifier) : sugar::Skeleton(instance_identifier) {}

    int sayHello(int);
    RetObject retObject(int);
    void init();
};

int main()
{
    sugar::skeleton::init();

    sugar::InstanceIdentifier ins("11-1111");
    auto skeleton = new HelloworldSkeleton(ins);
    skeleton->init();
    skeleton->OfferService();
    skeleton->wantToSayEvent.one = 10002;
    skeleton->wantToSayEvent.notify();
    printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX wantToSayEvent\n");
    sugar::skeleton::destroy();
}

void HelloworldSkeleton::init()
{

    register_method(testMethod, std::bind(&HelloworldSkeleton::sayHello, this, std::placeholders::_1));
    register_method(testMethodRetObj, std::bind(&HelloworldSkeleton::retObject, this, std::placeholders::_1));
    register_field(testField);
    register_event(wantToSayEvent);

    testField.onSet(
        [&]()
        {
            testField.one = " xxx?????XXXX ";
            printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>onSet in Skeleton t1:%s\n", testField.one.c_str());
        });
    testField.onGet(
        [&]()
        {
            testField.one = "onGetActionChanged";
            printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>onGet in Skeleton t1:%s\n", testField.one.c_str());
        });
}

int HelloworldSkeleton::sayHello(int a)
{
    printf("HelloworldSkeleton::sayHello %d\n", a);
    return 222212;
}

RetObject HelloworldSkeleton::retObject(int a)
{
    printf("HelloworldSkeleton::sayHello %d\n", a);
    RetObject rr;
    rr.hello = "hello,world from skeleton";
    rr.v = 111111;
    return rr;
}
