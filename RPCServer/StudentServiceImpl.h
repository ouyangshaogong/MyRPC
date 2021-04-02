#ifndef __STUDENT_SERVICE_IMPL__
#define __STUDENT_SERVICE_IMPL__

#include "StudentService.h"

class StudentServiceImpl: public StudentService
{
public:
    StudentServiceImpl();
    ~StudentServiceImpl();

    void findStuInfoById(int nId, string &strName, int &age);
};

#endif