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
    proxy->wantToSayEvent.Subscrible(1);
    printf("1\n");
    proxy->wantToSayEvent.SetReceiveHandler(
    [&]()
    {
            printf("2\n");
            proxy->wantToSayEvent.GetOneSample([&](SharedObject*obj){
                // handle obj
                while(1) {
                    printf("get_a:%d, get_b:%d\n",obj->a,obj->b);
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));

                }
                
            });
    });

        

    sugar::proxy::destroy();
}

void HelloworldProxy::init()
{
    // 处理 event 的注册
}
