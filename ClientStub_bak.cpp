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

    

    //��������
    Json::Value jsonId;
    jsonId["id"] = nId;
    //���л�
    string strBody;
    m_jsonSerialize.EnCode(jsonId, strBody);
    //�������ݵ�������

    const int MAX_LENGTH = 2048;
    char buf[MAX_LENGTH] = { 0 };
    strcpy(buf, strBody.c_str());
    m_sockClient.SendToServer(buf, strBody.length());

    memset(buf, 0, MAX_LENGTH);
    //�ӷ�������ȡ����
    m_sockClient.RecvFromServer(buf, MAX_LENGTH);
    //�����л�
    Json::Value jsonStu;
    m_jsonSerialize.DeCode(string(buf), jsonStu);
    //��ֵ
    strName = jsonStu["name"].asString();
    age = jsonStu["age"].asInt();
}
