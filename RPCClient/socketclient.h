#ifndef __SOCKET_CLIENT__
#define __SOCKET_CLIENT__

#include "ace/SOCK_Connector.h"
#include "ace/SOCK_Stream.h"
#include "commonace.h"
#include "ace/INET_Addr.h"

class SocketClient
{
public:
    SocketClient();
    ~SocketClient();

    int ConnectToServer();

    int SendToServer(char *buf, int nLength);

    int RecvFromServer(char *buf, int nMaxLength);

    int Close();

private:
    ACE_SOCK_Stream m_clientStream;
    ACE_INET_Addr m_remoteAddr;
    ACE_SOCK_Connector m_connector;
};

#endif