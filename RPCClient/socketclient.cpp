#include "socketclient.h"



SocketClient::SocketClient()
    :m_remoteAddr(5000, "127.0.0.1")
{
}


SocketClient::~SocketClient()
{
}

int SocketClient::ConnectToServer()
{
    ACE_DEBUG((LM_DEBUG, "(%P|%t) Starting connect to %s:%d\n", m_remoteAddr.get_host_name(), m_remoteAddr.get_port_number()));
    if (m_connector.connect(m_clientStream, m_remoteAddr) == -1)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t) connection failed\n"));
    }
    else
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t) connected to %s\n", m_remoteAddr.get_host_name()));
    }

    return 0;
}

int SocketClient::SendToServer(char *buf, int nLength)
{
    int send_cnt = m_clientStream.send_n(buf, nLength);
    if (send_cnt < 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t) send_cnt:%d, errno:%d\n", send_cnt, errno));
        return -1;
    }

    if (send_cnt == 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t) send_cnt:%d, errno:%d\n", send_cnt, errno));
        m_clientStream.close();
        return 0;
    }

    if ((send_cnt > 0) && (send_cnt == nLength))
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t) send_cnt:%d, errno:%d\n", send_cnt, errno));
        return 1;
    }
}

int SocketClient::RecvFromServer(char *buf, int nMaxLength)
{
    int recv_cnt = m_clientStream.recv(buf, nMaxLength);
    if (recv_cnt < 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t) recv_cnt:%d, errno:%d\n", recv_cnt, errno));
        return -1;
    }

    if (recv_cnt == 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t) recv_cnt:%d, errno:%d\n", recv_cnt, errno));
        m_clientStream.close();
        return 0;
    }

    if (recv_cnt > 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t) recv_cnt:%d, errno:%d\n", recv_cnt, errno));
        return 1;
    }
}

int SocketClient::Close()
{
    if (m_clientStream.close() == -1)
    {
        ACE_DEBUG((LM_ERROR, "(%P|%t) close\n"));
    }
    else
    {
        return 0;
    }
}