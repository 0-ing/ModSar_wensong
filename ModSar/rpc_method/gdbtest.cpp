#include <iostream>
#include <thread>
#include <chrono>

void* thread_1_job(void* name)
{
    printf("this is %s\n",(char*)name);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    printf("测试\n");

    return NULL;
}

void* thread_2_job(void* name)
{
    printf("this is %s\n",(char*)name);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    printf("测试\n");

    return NULL;
}




int main()
{
    pthread_t tid1,tid2;

    pthread_create(&tid1, NULL, thread_2_job, (char*)"thread_1");
    pthread_create(&tid2, NULL, thread_2_job, (char*)"thread_2");
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    printf("this is main\n");

    return 0;
}
