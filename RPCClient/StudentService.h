#ifndef __STUDENT_SERVICE__
#define __STUDENT_SERVICE__

#include "commonace.h"

struct Student
{
    int id;
    string strName;
    int age;
};

class StudentService
{
public:
    virtual void findStuInfoById(int nId, string &strName, int &age) = 0;
};

#endif