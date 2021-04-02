#include "ClientStub.h"



int main()
{
    StudentService *stub = new ClientStub;

    Student stu;
    stu.id = 10;

    stub->findStuInfoById(stu.id, stu.strName, stu.age);

    cout << stu.strName << endl;
    cout << stu.age << endl;

    delete stub;
    return 0;
}