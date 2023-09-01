#include "MTSLogic.h"

class FrameInfo
{
public:
    int frameId = 0;
};

class FrameQueue
{
public:
    bool isEmpty()
    {
        return frames.empty();
    }
    void add(const FrameInfo &info)
    {
        frames.push_back(info);
    }
    bool get(FrameInfo &info)
    {
        if (frames.empty())
            return false;
        info = frames.front();
        frames.pop_front();
        return true;
    }
    std::list<FrameInfo> frames;
};
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
        // printf("getFrame..\n");
        char deviceName[125];
        sprintf(deviceName, "camera_%d", virtualID);

        stub->exec_promise([&](IStubHandler *stubH, ExecEnvironment &env, void *) -> int {
            // 构建安全逻辑
            FrameQueue* queue = env.addComponent<FrameQueue>(deviceName);
            if (queue) {
                if (queue->isEmpty()) {
                    stubH->block(virtualID); // 为空时阻塞对方
                    return BLOCK;
                } else {
                    queue->get(info);
                }
            }
            return NON_BLOCK; 
        });
    }
    ~VirtualDevice()
    {
        if (stub)
            StubManager::instance().destroyStub(stub);
        stub = NULL;
    }
};

class PhysicsDdevice
{
public:
    PhysicsDdevice()
    {
        init();
    }
    bool init()
    {
        stub = StubManager::instance().createStub();
        return true;
    }

    IStub *stub = NULL;
    void splitFrames(const std::string &deviceName, int virtualID)
    {
        stub->exec_promise([=](IStubHandler *stubH, ExecEnvironment &env, void *) -> int {
            // 构建安全逻辑
            FrameQueue *queue = env.addComponent<FrameQueue>(deviceName);
            if (queue)
            {

                queue->add(info);

                IStub *otherstub = stubH->peek<IStub>(virtualID);
                if (otherstub)
                { // 尝试唤醒消费者
                    // printf("需要唤醒其他\n");

                    if (otherstub->has_promise_func_repsonse())
                    {
                        auto fn = otherstub->response_promise_func<callback_func>();
                        fn(stubH, env, NULL);
                        otherstub->awake(); // 唤醒对方
                    }
                }
            }
            return NON_BLOCK; 
        });
    }
    FrameInfo info;
};
/***
 * 生产者 每5s生成 其他消费者不同的时间去获取数据 构建一个模拟行为
 */
void producer()
{
    PhysicsDdevice pd;
    while (true)
    {
        pd.splitFrames("camera_1", 1);
        pd.splitFrames("camera_2", 2);
        pd.splitFrames("camera_3", 3);
        pd.splitFrames("camera_4", 4);
        pd.info.frameId++;
        sleep(5);
    }
}
void consumer1()
{
    VirtualDevice vd(1);
    FrameInfo info;
    int count = 1;
    while (count ++ < 10)
    {
        vd.getFrame(info);
        printf("**** cameraId:%d getFrame id:%d\n", vd.virtualID, info.frameId);
        sleep(1);
    }
}

void consumer2()
{
    VirtualDevice vd(2);
    FrameInfo info;
    int count = 1;
    while (count ++ < 5)
    {
        vd.getFrame(info);
        printf("***** cameraId:%d getFrame id:%d\n", vd.virtualID, info.frameId);
        sleep(2);
    }
}

void consumer3()
{
    VirtualDevice vd(3);
    FrameInfo info;
    while (true)
    {
        vd.getFrame(info);
        printf("***** cameraId:%d getFrame id:%d\n", vd.virtualID, info.frameId);
        sleep(3);
    }
}

void consumer4()
{
    VirtualDevice vd(4);
    FrameInfo info;
    while (true)
    {
        vd.getFrame(info);
        printf("***** cameraId:%d getFrame id:%d\n", vd.virtualID, info.frameId);
        sleep(4);
    }
}

int main()
{
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
