#include "MTSLogic.h"

#include <fcntl.h>

#define url "socket.stub.rvc"

StubExecScope::StubExecScope(IStub *stub)
{
    this->stub = stub;
    stub->beginCall();
}
StubExecScope::~StubExecScope()
{
    stub->endCall();
}

std::map<int, IStub *> IStubHandler::blockTags;
int IStub::sendData(void *data, int len)
{
    std::string content;
    content.resize(sizeof(int) + len);
    memcpy(&content[0], &len, sizeof(int));
    memcpy(&content[sizeof(int)], data, len);
    return sendRaw(&content[0], content.size());
}

int IStub::sendRaw(void *data, int len)
{
    return ::send(socket, data, len, 0);
}
int IStub::recvData(void *data, int len)
{
    int n = ::recv(socket, data, len, 0);
    if (n == -1)
    { // recv函数返回错误
    }
    else if (n == 0)
    { // client端套接字被关闭
    }
    else
    { // 读取成功
    }
    return n;
}

std::map<int, IStub *> IStubHandler::_sessions;
IStub *IStubHandler::findSession(int sessionId)
{
    auto it = _sessions.find(sessionId);
    if (it != _sessions.end())
    {
        return it->second;
    }
    return NULL;
}
void IStubHandler::addSession(int id, IStub *session)
{
    _sessions[id] = session;
}
void IStubHandler::delSession(int id)
{
    auto it = _sessions.find(id);
    if (it != _sessions.end())
    {
        _sessions.erase(it);
    }
}

bool StubClient::connect()
{
    struct sockaddr_un server_addr;

    /*创建unix域套接字*/
    int conn_fd = ::socket(AF_UNIX, SOCK_STREAM, 0);
    if (conn_fd == -1)
    {
        printf("socket create error\n");
        return NULL;
    }

    /*指定将连接的server信息*/
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, url);

    /*连接到server*/
    int retryCount = 0;
    while (::connect(conn_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1 && retryCount++ < 3)
    {
        printf("connect error retryCount:%d", retryCount);
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    }
    if (retryCount >= 3)
    {
        return false;
    }
    socket = conn_fd;
    return true;
}

bool StubShortClient::beginCall()
{
    return connect();
}
void StubShortClient::endCall()
{
    ::close(socket);
}

bool StubSession::init(int socket)
{
    this->socket = socket;
    return true;
}
bool StubSession::addEvent(int epollHandler, int events)
{
    struct epoll_event ev;
    ev.events = events;
    ev.data.ptr = this;
    int oldSocketFlag = fcntl(socket, F_GETFL, 0);
    int newSocketFlag = oldSocketFlag | O_NONBLOCK;
    fcntl(socket, F_SETFL, newSocketFlag);
    if (epoll_ctl(epollHandler, EPOLL_CTL_ADD, socket, &ev))
    {
        printf("绑定Epoll失败\n");
        return false;
    }
    // printf("创建Session\n");

    return true;
}
bool StubSession::delEvent(int epollHandler, int events)
{
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLERR | EPOLLPRI | EPOLLHUP;
    ev.data.ptr = this;
    if (epoll_ctl(epollHandler, EPOLL_CTL_DEL, socket, &ev))
    {
        printf("绑定Epoll失败\n");
        return false;
    }
    return true;
}

bool StubManager::init(int stubCount)
{
    _epollHandler = epoll_create(stubCount + 1);

    // 构建服务节点
    if (!_initServerNode())
    {
        printf("初始化失败\n");
        return false;
    }
    _logics[REMOTE_CALL_LOIGC_ID] = &remoteCallLogic;
    remoteCallLogic.stubHandlers = &this->stubHandlers;
    _logics[REMOTE_CALL_LOGIC_WITH_EXPECT] = &remoteCallWithExpect;
    remoteCallWithExpect.stubHandlers = &this->stubHandlers;

    _logics[REMOTE_CALL_LOGIC_WITH_EXPECT_OBJ] = &remoteCallWithExpectObj;
    remoteCallWithExpectObj.stubHandlers = &this->stubHandlers;

    _logics[REMOTE_CALL_LOGIC_WITH_EXPECT_PROMISE] = &remoteCallWithExpectPromise;
    remoteCallWithExpectPromise.stubHandlers = &this->stubHandlers;

    _isRun = true;

    printf("初始化 %s 成功\n", url);

    workThread = new std::thread(&StubManager::_workThread, this);

    readEventList.resize(stubCount + 1);
    return true;
}

void StubManager::_workThread()
{
    while (_isRun)
    {
        int retcode = epoll_wait(_epollHandler, &readEventList[0], readEventList.size(), -1);
        if (retcode > 0)
        {
            for (int i = 0; i < retcode; i++)
            {
                IStub *stub = (IStub *)readEventList[i].data.ptr;
                if (readEventList[i].events & (EPOLLERR | EPOLLPRI | EPOLLHUP))
                {
                    if (stub->stubType == IStub::SESSION)
                    {
                        // printf("套接字异常错误\n");
                        ((StubSession *)stub)->delEvent(_epollHandler, EPOLLERR | EPOLLPRI | EPOLLHUP | EPOLLIN);
                        // 标识session 删除
                        if (stub)
                            delete stub;
                    }
                    // 套接字出现错误

                    readEventList[i].data.ptr = NULL;
                }
                else
                {
                    if ((readEventList[i].events & EPOLLIN) && stub)
                    {
                        if (stub->stubType == IStub::SERVER)
                        {
                            struct sockaddr_in addr;
                            socklen_t len = sizeof(struct sockaddr_in);
                            bzero(&addr, sizeof(struct sockaddr_in));

                            int socket = TEMP_FAILURE_RETRY(::accept(_serverSocket, (struct sockaddr *)&addr, &len));
                            // 构建Session
                            _createSession(socket);
                        }
                        else if (stub->stubType == IStub::SESSION || stub->stubType == IStub::CLIENT)
                        {
                            // 套接字准备好了读取操作
                            //  连续回去socket 数据 直至取完

                            char buffer[1024] = {0};
                            int size = -1;
                            while ((size = recv(stub->socket, buffer, 1024, 0)) > 0)
                            {
                                //  printf("收到数据... :%d\n", size);
                                onMessage(stub, buffer, size);
                            }
                        }
                    }
                }
                readEventList[i].events = 0;
            }
        }
    }
}

bool StubManager::_initServerNode()
{
    struct sockaddr_un server_addr;
    struct sockaddr_un conn_addr;
    socklen_t len;
    int conn_fd = -1;
    int server_fd = -1;

    /*创建unix域套接字*/
    server_fd = ::socket(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (server_fd == -1)
    {
        printf("server socket create error!\n");
        return false;
    }

    /*指定server信息并绑定*/
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    snprintf(server_addr.sun_path, sizeof(server_addr.sun_path) - 1, url);

    unlink(url); // 如果系统中存在该路径，bind将失败，因此先调用unlink删除该路径。
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        printf("server socket bind error! %s\n", strerror(errno));
        return false;
    }

    /*监听server描述符*/
    if (listen(server_fd, 5) == -1)
    {
        printf("server socket listen error!\n");
        return false;
    }

    struct timeval tv_out;
    tv_out.tv_sec = 3;
    tv_out.tv_usec = 0;
    setsockopt(server_fd, SOL_SOCKET, SO_RCVTIMEO, &tv_out, sizeof(tv_out));

    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.ptr = this;
    if (epoll_ctl(_epollHandler, EPOLL_CTL_ADD, server_fd, &ev))
    {
        printf("绑定Epoll失败\n");
        return false;
    }
    _serverSocket = server_fd;
    printf("启动成功\n");
    return true;
}

IStub *StubManager::createStub(int stubId)
{
    if (stubId != -1)
    {
        return _createClient(stubId);
    }
    static int clientid = 1;
    return _createClient(clientid++);
}

IStub *StubManager::createShortStub(int stubId)
{
    if (stubId != -1)
    {
        return _createShortClient(stubId);
    }
    static int clientid = 1;
    return _createShortClient(clientid++);
}

IStub *StubManager::_createClient(int id)
{
    StubClient *stub = new StubClient;
    if (!stub->connect())
    {
        delete stub;
        return NULL;
    }
    stub->sessionId = id;

    printf("创建client成功\n");
    return stub;
}

IStub *StubManager::_createShortClient(int id)
{
    StubShortClient *stub = new StubShortClient;
    if (!stub->connect())
    {
        delete stub;
        return NULL;
    }
    stub->sessionId = id;

    printf("创建client成功\n");
    return stub;
}

void StubManager::destroyStub(IStub *stub)
{
    ::close(stub->socket);
    delete stub;
}

bool StubManager::_createSession(int socket)
{
    StubSession *stub = new StubSession;
    stub->init(socket);
    if (!stub->addEvent(_epollHandler, EPOLLIN | EPOLLERR | EPOLLPRI | EPOLLHUP))
    {
        delete stub;
        return false;
    }
    return true;
}

int StubManager::onMessage(IStub *session, void *data, int len)
{
    StubSession *stub = (StubSession *)session;
    auto &content = stub->body;
    int bodyLength = 0;
    for (int i = 0; i < len; i++)
    {
        if (content.size() >= sizeof(int))
        {
            bodyLength = *(int *)&content[0];
        }
        if (bodyLength != 0)
        {
            if (content.size() == bodyLength + sizeof(int))
            {
                handleMessage(session, &content[sizeof(int)], bodyLength);
                content.clear();
            }
        }
        content.push_back(*((char *)data + i));
    }
    if (bodyLength != 0)
    {
        if (content.size() == bodyLength + sizeof(int))
        {
            handleMessage(session, &content[sizeof(int)], bodyLength);
            content.clear();
        }
    }
    return 0;
}

bool StubManager::handleMessage(IStub *session, void *message, int len)
{
    //  printf("收到消息 并转发\n");
    LogicHeadProto *proto = (LogicHeadProto *)message;
    auto it = _logics.find(proto->logicId);
    if (it != _logics.end())
    {
        it->second->handle(session, message, len);
        return true;
    }
    printf("没找到消息处理器:%d\n", proto->logicId);
    return false;
}

void StubManager::addLogic(ILogic *logic)
{
    _logics[logic->logicId] = logic;
    printf("增加消息处理器:%d\n", logic->logicId);
}

void StubManager::addStubHandler(const std::string &name, IStubHandler *stubHandler)
{
    stubHandlers[name] = stubHandler;
    printf("%s %s\n", "StubManager::addStubHandler", name.c_str());
}

void StubManager::wait()
{
    if (workThread)
        workThread->join();
}

class ExecuteLogic : public StubLogic
{
public:
    ExecEnvironment env;
    int exec(int id)
    {
        if (stub->has_func_repsonse())
        {
            auto fn = stub->response_func<callback_func>();
            return fn(this, env, NULL);
        }
        return NON_BLOCK;
    }
};

REGISTER_REMOTE_MODULE(ExecuteLogic)
{
    BIND_REMOVE_CALL(ExecuteLogic::exec);
}

class ExecutePromiseLogic : public StubLogic
{
public:
    ExecEnvironment env;
    int exec(int id)
    {
        if (stub->has_promise_func_repsonse())
        {
            auto fn = stub->response_promise_func<callback_func>();
            return fn(this, env, NULL);
        }
        return NON_BLOCK;
    }
};

REGISTER_REMOTE_MODULE(ExecutePromiseLogic)
{
    BIND_REMOVE_CALL(ExecutePromiseLogic::exec);
}