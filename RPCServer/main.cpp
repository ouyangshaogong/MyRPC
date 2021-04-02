#include "server.h"
#include "SocketServer.h"

int main()
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgService::svc>>begin\n"));
    ACE_INET_Addr inetAddr;
    inetAddr.set(5000, "127.0.0.1");

    SocketAcceptor acceptor;
    if (acceptor.open(inetAddr, ACE_Reactor::instance()) == -1)
    {
        return 1;
    }

    ACE_Reactor::instance()->run_reactor_event_loop();
    return 0;
}