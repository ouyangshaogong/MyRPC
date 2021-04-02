#ifndef __SOCKET_SERVER__
#define __SOCKET_SERVER__

#include "commonace.h"
#include <ace/SOCK_Connector.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/Auto_Ptr.h>
#include "ace/Acceptor.h"

class SocketServer: public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_MT_SYNCH>
{
public:
    SocketServer();
    ~SocketServer();

    int open(void *p);

    virtual int handle_input(ACE_HANDLE fd);

    virtual int handle_output(ACE_HANDLE fd);

    // 释放相应资源
    virtual int handle_close(ACE_HANDLE, ACE_Reactor_Mask mask);

    void Process(string strBody, int nLength);
};

typedef ACE_Acceptor<SocketServer, ACE_SOCK_ACCEPTOR> SocketAcceptor;

#endif