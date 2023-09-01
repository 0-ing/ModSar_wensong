#include "MTSLogic.h"

#include "signal.h"
#include "functional"

class FrameInfo : public cmd::Object
{
public:
    int frameId = 0;

    SERIALIZE_CMD()
    {
        BIND_MSG(frameId);
    }
};

std::map<int, std::list<FrameInfo>> frameInfos;

/***
 * 模拟生成消费者
 */
class FrameHandler : public StubLogic
{
public:
    /***
     * 来自 producer 线程
     */
    int push(const int &id, const FrameInfo &info)
    {
        
        //printf("FrameHandler::push id:%d size:%d frameId:%d\n", id, (int)frameInfos[id].size(), info.frameId);
        IStub *otherstub = peek<IStub>(id);
        if (otherstub)
        { 
            // 如果当前正在等待 则直接反馈当前数据
            if (otherstub->has_obj_repsonse()) {
                otherstub->response_obj(info); // 新方案处理obj的返回
            }
            otherstub->awake();
            return NON_BLOCK;
        }
        frameInfos[id].push_back(info);
        return NON_BLOCK;
    }

    /***
     * 多个 consumer 会调用
     */
    int pop(const int &id)
    {
      //  printf("pop :%d\n",id);
        if (frameInfos[id].size())
        {
            auto frameInfo = frameInfos[id].front();
            
           // printf("FrameHandler::pop id:%d size:%d frameInfo:%d\n", id, (int)frameInfos[id].size(), frameInfo.frameId);
            if (stub->has_obj_repsonse()) {
                stub->response_obj(frameInfo); // 新方案处理obj的返回
            }
            frameInfos[id].pop_front();
            return NON_BLOCK;
        }
       // printf("会阻塞虚拟camera id:%d\n", id);

        block(id);
        return BLOCK;
    }
    
    REMOTE_API(FrameHandler,pop);
    REMOTE_API(FrameHandler,push);
};

REGISTER_REMOTE_MODULE(FrameHandler)
{
    BIND_REMOVE_CALL(FrameHandler::push);
    BIND_REMOVE_CALL(FrameHandler::pop);
}

class VirtualDevice
{
public:
    VirtualDevice(int virtualID) : virtualID(virtualID)
    {
        init();
    }
    bool init()
    {
        stub = StubManager::instance().createStub();
        return true;
    }
    int virtualID = 0;
    IStub *stub = NULL;

    /**
     * 当队列为空 时 等待
     */
    void getFrame(FrameInfo &info)
    {
        //printf("getFrame virtualID:%d\n",virtualID);
     
        info = stub->invoke<FrameInfo>(FrameHandler::pop(), virtualID);

        printf("getFrame virtualID:%d id:%d\n",virtualID,info.frameId);
    }
};
void consumer1()
{
    printf("consumer1 start \n");
    VirtualDevice vd(1);
    // 快的消费者
    while (true)
    {
        FrameInfo info;
        vd.getFrame(info);
        sleep(1);
    }
}
void consumer2()
{
    printf("consumer2 start \n");
    VirtualDevice vd(2);
    while (true)
    {
        FrameInfo info;
        vd.getFrame(info);
        sleep(2);
    }
}
void consumer3()
{
    printf("consumer3 start \n");
    VirtualDevice vd(3);
    while (true)
    {
        FrameInfo info;
        vd.getFrame(info);
        sleep(3);
    }
}
void consumer4()
{
    printf("consumer4 start \n");
    VirtualDevice vd(4);
    while (true)
    {
        FrameInfo info;
        vd.getFrame(info);
        sleep(4);
    }
}

void producer()
{
    printf("producer start\n");

    IStub *stub2 = StubManager::instance().createStub();
    if (stub2)
    {
        FrameInfo info;
        while (true)
        {

            info.frameId++;
            stub2->call(FrameHandler::push(), 1, info);
            stub2->call(R(FrameHandler::push), 2, info);
            stub2->call(R(FrameHandler::push), 3, info);
            stub2->call(R(FrameHandler::push), 4, info);

            sleep(5);
        }
    }
}


 
int main()
{
    
    signal(SIGPIPE, SIG_IGN);

    StubManager::instance().init(5); // 最多4个stub

    std::thread c1(consumer1);
    std::thread c2(consumer2);
    std::thread c3(consumer3);
    std::thread c4(consumer4);
    std::thread p(producer);

    printf("try to wait\n");
    StubManager::instance().wait();

    return 0;
}