#ifndef __CLASS_FACTORY__
#define __CLASS_FACTORY__

typedef void* (*PTRCreateObject)(void);

//工厂类的定义
class ClassFactory
{
public:   
    void* getClassByName(string className);  
    void registClass(string name, PTRCreateObject method) ;  
    static ClassFactory& getInstance() ;  
private:
    map<string, PTRCreateObject> m_classMap ;  
    ClassFactory(){}; //构造函数私有化

};

class RegisterAction{
public:
    RegisterAction(string className,PTRCreateObject ptrCreateFn){
        ClassFactory::getInstance().registClass(className,ptrCreateFn);
    }
};
 
#define REGISTER(className)                                             \
    className* objectCreator##className(){                              \
        return new className;                                           \
    }                                                                   \
    RegisterAction g_creatorRegister##className(                        \
        #className,(PTRCreateObject)objectCreator##className)



#endif
