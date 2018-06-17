#include "network.h"
#include <SFML/Network.hpp>
#include <thread>

network::network(int port)
{

}

network::~network()
{

}

int threadNetwork()
{
    /*
    sf::TcpListener listener;
    int dataNum=10;
    char data[dataNum];
    std::size_t received=0;
    m_quitThread=FALSE;

    // lie l'écouteur à un port
    if (listener.listen(port) != sf::Socket::Done)
    {
        cout<<"error listening TCP port"<<port<<endl;
    }


    while(m_quitThread != TRUE)
    {
        // accepte une nouvelle connexion
        sf::TcpSocket client;
        if (listener.accept(client) != sf::Socket::Done)
        {
            cout<<"error connection"<<endl;
        }

        // socket TCP:
        if (client.receive(data, dataNum, received) != sf::Socket::Done)
        {
            cout<<"erreur reveiving TCP trame"<<endl;
        }

        for(int i=0; i<DATA_TRAME_LENGH; i++)
        {
            m_lastTrame[i]=data[i];
        }
    }*/
}


string getLastTrame(void)
{

}
