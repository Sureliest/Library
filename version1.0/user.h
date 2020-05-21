#ifndef USER
#define USER
#endif // USER
#include"qstring.h"

class User
{
private:
    char usr_name[20];
    char usr_pwd[20];
    int maxbook;
    int currentbook;
    bool level;

public:
    User(){}
    User(QString name,QString pwd,bool l)
    {
        strcpy(usr_name,name.toLocal8Bit().data());
        strcpy(usr_pwd,pwd.toLocal8Bit().data());
        level=l;
        if(l==true)
            maxbook=5;
        else maxbook=3;
        currentbook=0;
    }
    ~User(){}
    QString getUsr_name()
    {
        return usr_name;
    }
    /*int checkUsr_pwd(QString pwd)
    {
       if(strcmp(usr_pwd,pwd.toLocal8Bit().data())==0)
           return 0;
       else return 1;
    }*/
    QString getUsr_pwd()
    {
        return usr_pwd;
    }

    int getMax()
    {
        return maxbook;
    }
    void setCurrent(int num)
    {
        currentbook=num;
    }
    int getCurrent()
    {
        return currentbook;
    }
    bool getLevel()
    {
        return level;
    }
};
