#include "protocol.h"

class HelloworldProxy : public IHelloworldProto
{
public:
    void init();
};

int main()
{
    sugar::proxy::init();
    printf(">>>>>>>>>>>>>> start >>>>>>>>>>>>>>>>>>>>>>>>\n");

    sugar::InstanceIdentifier ins("11-1111");
    auto proxy = sugar::FindProxy<HelloworldProxy>(ins);
    proxy->init();
    int ret = proxy->testMethod(1);
    printf("》》》》》testMethod 》》》》》》》》》》》》 %d\n", ret);

    RetObject ro = proxy->testMethodRetObj(1000);
    printf("》》》》》》》》testMethodRetObj 》》》》》》》》》 content:%s len:%d\n", ro.hello.c_str(), ro.v);
    proxy->testField.onChange(
        [&]()
        {
            printf("<><><><><>><><><<<<>>><><>><<><><<>><><<>><><>><><<<<<>>> on changed %s\n", proxy->testField.one.c_str());
        });
    std::string hello = "action";
    proxy->testField(hello);

    proxy->testField.get();
    printf("get From Skeleton %s\n", proxy->testField.one.c_str());

    proxy->wantToSayEvent.subscrible(
        [&]() {
            printf("<><><><><>><><><<<<>>><><>><<><><<>><><<>><><>><><<<<<>>>want To Say Hello :%d",proxy->wantToSayEvent.one);
        });

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    sugar::proxy::destroy();
}

void HelloworldProxy::init()
{
    // 处理 event 的注册
}
