#ifndef __JSON_SERIALIZE__
#define __JSON_SERIALIZE__

#include "commonace.h"
#include "json/json.h"

class JsonSerialize
{
public:
    JsonSerialize();
    ~JsonSerialize();

    void EnCode(Json::Value body, string &strBody);
    int DeCode(string strBody, Json::Value &body);
};

#endif