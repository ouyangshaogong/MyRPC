#ifndef __CLIENT_STUB__
#define __CLIENT_STUB__

#include "commonace.h"
#include "JsonSerialize.h"
#include "socketclient.h"
#include "StudentService.h"


class ClientStub: public StudentService
{
public:
    ClientStub();
    ~ClientStub();

    virtual void findStuInfoById(int nId, string &strName, int &age);
    void invoke(int nMrbCode, Json::Value &jsonInParam, Json::Value &jsonOutParam);

private:
    SocketClient m_sockClient;
    JsonSerialize m_jsonSerialize;
    StudentService *pStuService;
};

#endif