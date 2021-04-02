#ifndef __CLIENT_STUB__
#define __CLIENT_STUB__

#include "commonace.h"
#include "JsonSerialize.h"
#include "socketclient.h"

struct Student
{
    int id;
    string strName;
    int age;
};

class ClientStub
{
public:
    ClientStub();
    ~ClientStub();

    void findStuInfoById(int nId, string &strName, int &age);

private:
    SocketClient m_sockClient;
    JsonSerialize m_jsonSerialize;
};

#endif