#include "JsonSerialize.h"



JsonSerialize::JsonSerialize()
{
}


JsonSerialize::~JsonSerialize()
{
}

void JsonSerialize::EnCode(Json::Value body, string &strBody)
{
    Json::FastWriter fwriter;
    strBody = fwriter.write(body);
    cout << "strBody:" << endl;
}

int JsonSerialize::DeCode(string strBody, Json::Value &body)
{
    Json::Value json;
    Json::Reader reader;
    if (!reader.parse(strBody.c_str(), body))
    {
        return 0;
    }
    
    return -1;
}