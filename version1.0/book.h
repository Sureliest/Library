#ifndef BOOK
#define BOOK
#endif // BOOK
#include"qstring.h"
class Book
{
private:
    char book_name[20];
    int book_kind;
    char book_id[3];

public:
    Book(){}
    Book(QString name,int kind,QString id)
    {
        strcpy(book_name,name.toLocal8Bit().data());
        book_kind=kind;
        strcpy(book_id,id.toLocal8Bit().data());
    }

    ~Book(){}

    QString getBook_name()
    {
        return book_name;
    }
    QString getBook_id()
    {
        return book_id;
    }
    int getBook_kind()
    {
        return book_kind;
    }
};
