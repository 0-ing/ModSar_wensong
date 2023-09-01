#include "Client.h"

int main()
{
    Client *  client = new Client();
    client->ready();
    client->start();
    return 0;
}
