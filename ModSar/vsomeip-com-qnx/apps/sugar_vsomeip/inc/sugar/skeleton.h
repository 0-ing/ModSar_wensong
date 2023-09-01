#ifndef _SUGAR_COM_SKELETON_H
#define _SUGAR_COM_SKELETON_H
#include "sugar/com/common.h"
#include "sugar/instance_identifier.h"

namespace sugar
{
    class BaiscSkeleton : public com::ISkeleton{
    public:
        

        BaiscSkeleton() {

        }
        sugar::InstanceIdentifier instance_identifier;
    };

    class Skeleton {
    public:
        Skeleton(const sugar::InstanceIdentifier & instance_identifier);
        virtual bool OfferService();

        BaiscSkeleton* getSkeleton() { return _skeleton;}
        void setSkeleton(BaiscSkeleton *skeleton) {_skeleton = skeleton;}
    private:
        BaiscSkeleton *_skeleton = NULL;
        sugar::InstanceIdentifier instance_identifier;
        std::promise<int> ready_promise;
    };
    
} // namespace sugar


#endif // _SUGAR_COM_SKELETON_H
