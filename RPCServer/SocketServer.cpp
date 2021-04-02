#include "SocketServer.h"
#include "JsonSerialize.h"
#include "StudentServiceImpl.h"

SocketServer::SocketServer()
{
}


SocketServer::~SocketServer()
{
}

int SocketServer::open(void *p)
{

    if (ACE_Svc_Handler::open(p) == -1)
    {
        return -1;
    }

    ACE_TCHAR peer_name[512];
    ACE_INET_Addr peer_addr;
    if (this->peer().get_remote_addr(peer_addr) == 0
        && peer_addr.addr_to_string(peer_name, 512) == 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t|)iMapMsgService::open>>connection success.peer_name:%s\n", peer_name));
    }

    return 0;
}

int SocketServer::handle_input(ACE_HANDLE fd)
{
    const int BUFFER_MAX_LENGTH = 2048;
    //从内核缓存区读取消息头
    char buf[BUFFER_MAX_LENGTH] = { 0 };
    int recv_cnt = peer().recv(buf, BUFFER_MAX_LENGTH);
    if (recv_cnt > 0)
    {
        Process(buf, recv_cnt);
    }

    if (recv_cnt == 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendCmdMsgToProc>>recv_cnt:%d, errno:%d\n", recv_cnt, errno));
        return -1;
    }

    if (recv_cnt < 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendCmdMsgToProc>>recv_cnt:%d, errno:%d\n", recv_cnt, errno));
        return 0;
    }

    return 0;
}

int SocketServer::handle_output(ACE_HANDLE fd)
{
    return 0;
}

// 释放相应资源
int SocketServer::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask mask)
{
    if (mask == ACE_Event_Handler::WRITE_MASK)
        return 0;
    return ACE_Svc_Handler::handle_close(handle, mask);
}

void SocketServer::Process(string strBody, int nLength)
{
    Json::Value jsonIn;
    JsonSerialize jsonSerialize;
    jsonSerialize.DeCode(strBody, jsonIn);

    int nId = jsonIn["id"].asInt();
    StudentService *service = new StudentServiceImpl();

    string strName;
    int age = 0;
    service->findStuInfoById(nId, strName, age);

    Json::Value jsonOut;
    jsonOut["name"] = strName.c_str();
    jsonOut["age"] = age;

    string strOut;
    jsonSerialize.EnCode(jsonOut, strOut);

    int send_cnt = peer().send_n(strOut.c_str(), strOut.length());
    if (send_cnt > 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)SocketServer::Process>>send_cnt:%d, errno:%d\n", send_cnt, errno));
    }

    if (send_cnt == 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)SocketServer::Process>>send_cnt:%d, errno:%d\n", send_cnt, errno));
        return ;
    }

    if (send_cnt < 0)
    {
        ACE_DEBUG((LM_DEBUG, "(%P|%t)iMapMsgHandle::SendCmdMsgToProc>>recv_cnt:%d, errno:%d\n", send_cnt, errno));
        return;
    }
}

