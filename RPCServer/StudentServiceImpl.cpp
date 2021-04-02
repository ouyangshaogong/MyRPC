#include "StudentServiceImpl.h"



StudentServiceImpl::StudentServiceImpl()
{
}


StudentServiceImpl::~StudentServiceImpl()
{
}

void StudentServiceImpl::findStuInfoById(int nId, string &strName, int &age)
{
    cout << "ID:" << nId << endl;
    strName = "zhangsan";
    age = 26;
}
