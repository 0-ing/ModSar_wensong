#include "Server.h"

int main()
{
    Server* server = new Server();
    server->ready();
    server->start();
    return 0;
}
