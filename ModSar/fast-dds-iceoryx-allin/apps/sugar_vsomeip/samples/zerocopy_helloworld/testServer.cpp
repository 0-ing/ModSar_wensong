#include "protocol.h"
 
class HelloworldSkeleton : public sugar::Skeleton, public IHelloworldProto
{
public:
    HelloworldSkeleton(const sugar::InstanceIdentifier &instance_identifier) : sugar::Skeleton(instance_identifier) {}
 
    void init();
};

int main()
{
    sugar::skeleton::init();

    sugar::InstanceIdentifier ins("11-1111");
    auto skeleton = new HelloworldSkeleton(ins);
    skeleton->init();
    skeleton->OfferService();
    int count_a = 100;
    int count_b = 200;
    while(1) {
        count_a ++;
        count_b ++;
        skeleton->wantToSayEvent->a = count_a;
        skeleton->wantToSayEvent->b = count_b;
        skeleton->wantToSayEvent.Publish();
        printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX wantToSayEvent\n");
        printf("push_a:%d, push_b:%d\n", count_a, count_b);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    
    sugar::skeleton::destroy();
}

void HelloworldSkeleton::init()
{

    
}

 