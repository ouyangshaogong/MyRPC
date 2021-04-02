#include "ClientStub.h"



ClientStub::ClientStub()
{
    m_sockClient.ConnectToServer();
}


ClientStub::~ClientStub()
{
    m_sockClient.Close();
}

void ClientStub::findStuInfoById(int nId, string &strName, int &age)
{

    

    //构造数据
    Json::Value jsonId;
    jsonId["id"] = nId;
    //序列化
    string strBody;
    m_jsonSerialize.EnCode(jsonId, strBody);
    //发送数据到服务器

    const int MAX_LENGTH = 2048;
    char buf[MAX_LENGTH] = { 0 };
    strcpy(buf, strBody.c_str());
    m_sockClient.SendToServer(buf, strBody.length());

    memset(buf, 0, MAX_LENGTH);
    //从服务器获取数据
    m_sockClient.RecvFromServer(buf, MAX_LENGTH);
    //反序列化
    Json::Value jsonStu;
    m_jsonSerialize.DeCode(string(buf), jsonStu);
    //赋值
    strName = jsonStu["name"].asString();
    age = jsonStu["age"].asInt();
}
