#ifndef LOG
#define LOG
#include"qstring.h"
#endif // LOG
class Log
{
private:
    Book book;
    char book_usr[20];
    int date[3];
public:
    Log(){}
    Log(Book b,QString usr,int year,int month,int day){
        book=b;
        strcpy(book_usr,usr.toLocal8Bit().data());
        date[0]=year;
        date[1]=month;
        date[2]=day;
    }
    ~Log(){}
    QString getBook_name()
    {
        return book.getBook_name();
    }
    QString getBook_id()
    {
        return book.getBook_id();
    }
    int getBook_kind()
    {
        return book.getBook_kind();
    }
    QString getUsr_name()
    {
        return book_usr;
    }
    int get_year()
    {
        return date[0];
    }
    int get_month()
    {
        return date[1];
    }
    int get_day()
    {
        return date[2];
    }
};
