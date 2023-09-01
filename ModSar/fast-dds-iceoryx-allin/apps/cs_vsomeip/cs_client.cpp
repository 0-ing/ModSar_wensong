#include "Client.h"

int main()
{
    Client *  client = new Client();
    client->ready();
    client->start();
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    client->callMethod(99);
    return 0;
}
