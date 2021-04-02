#include "ClientStub.h"



ClientStub::ClientStub()
{
    m_sockClient.ConnectToServer();
}


ClientStub::~ClientStub()
{
    m_sockClient.Close();
}

void ClientStub::invoke(int nMrbCode, Json::Value &jsonInParam, Json::Value &jsonOutParam)
{
    string strBody;
    m_jsonSerialize.EnCode(jsonInParam, strBody);
    //发送数据到服务器

    const int MAX_LENGTH = 2048;
    char buf[MAX_LENGTH] = { 0 };
    strcpy(buf, strBody.c_str());
    m_sockClient.SendToServer(buf, strBody.length());

    memset(buf, 0, MAX_LENGTH);
    m_sockClient.RecvFromServer(buf, MAX_LENGTH);
    
    m_jsonSerialize.DeCode(string(buf), jsonOutParam);
}


void ClientStub::findStuInfoById(int nId, string &strName, int &age)
{
    //构造数据
    Json::Value jsonInParam;
    jsonInParam["id"] = nId;

    Json::Value jsonOutParam;
    invoke(1, jsonInParam, jsonOutParam);
    
    strName = jsonOutParam["name"].asString();
    age = jsonOutParam["age"].asInt();
}
