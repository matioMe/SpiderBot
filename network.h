#ifndef NETWORK_H
#define NETWORK_H

#include <SFML/Network.hpp>
#include <iostream>

#define DATA_TRAME_LENGH 10

using namespace std;

class network
{
public:
    network(int port);
    ~network();
    string getLastTrame(void);

private:
    char m_lastTrame[DATA_TRAME_LENGH];
    bool m_quitThread;
};

#endif // NETWORK_H
