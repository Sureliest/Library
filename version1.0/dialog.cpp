#include "dialog.h"
#include "ui_dialog.h"
#include "address.h"
#include "qstring.h"
#include "qlineedit.h"
#include "QFile"
#include "QTextStream"
#include "book.h"
#include "log.h"
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QRegExp regExp("[A-Z][0-9][1-9]{0,2}");
    ui->lineEdit->setValidator(new QRegExpValidator(regExp,this));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_line_textChanged()
{
    ui->pushButton->setEnabled(ui->lineEdit->hasAcceptableInput());
}

void Dialog::on_pushButton_clicked()
{
    QString id=ui->lineEdit->text();
    //Book b1;
    int flag=0;
    QFile file(AddressOfBookMessage);
    if(file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        while(!stream.atEnd())
        {
            QStringList list=stream.readLine().split(QRegExp("\\s+"));
            if(list.contains(id)==true)
            {
                Book b1(list.at(0),static_cast<QString>(list.at(1)).toInt(),list.at(2));
                ui->label_2->setText(b1.getBook_name()+" 类别："+QString::number(b1.getBook_kind()));
                flag=1;
                break;
            }
        }
    }
    file.close();
    if(flag==0)
        ui->label_2->setText(tr("无此书，请联系图书馆"));
}

void Dialog::on_Lend_Button_clicked()
{
    int flag=0;
    QString id=ui->lineEdit->text();
    QFile file(AddressOfLogMessage);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream log(&file);
        while(!log.atEnd())
        {
            QStringList list=log.readLine().split(QRegExp("\\s+"));
            if(list.contains(id)==true)
            {
               flag=1;
               ui->label_3->setText(tr("已被出借"));
               break;
            }
        }
    }
    file.close();
    if(flag==0)
    {
        Book b;
        QString name;
        QFile book(AddressOfBookMessage);
        if(book.open(QIODevice::ReadOnly))
        {
            QTextStream info(&book);
            while(!info.atEnd())
            {
                QStringList list=info.readLine().split(QRegExp("\\s+"));
                if(list.contains(id)==true)
                {
                    Book c(list.at(0),static_cast<QString>(list.at(1)).toInt(),list.at(2));
                    b=c;
                    break;
                }
            }
        }
        book.close();
        QFile usr(AddressOfCurrentMessage);
        if(usr.open(QIODevice::ReadOnly))
        {
            QTextStream u(&usr);
            while(!u.atEnd())
            {
                name=u.readLine();
            }
        }
        usr.close();

        int flag1=0;
        //判断当前借书数量
        QFile usrinfo(AddressOfUserMessage);
        QStringList line[20];
        int i=0;
        if(usrinfo.open(QIODevice::ReadWrite|QIODevice::Text))
        {
            QTextStream check(&usrinfo);
            while(!check.atEnd())
            {
                QStringList list=check.readLine().split(QRegExp("\\s+"));
                if(list.contains(name))
                {
                    int current_book_num=list.at(3).toInt();
                    int max_book_num=list.at(4).toInt();
                    if(current_book_num==max_book_num)
                        flag1=1;
                    else
                    {
                        int re=current_book_num+1;
                        //list.replaceInStrings(list.at(3),QString::number(re));
                        QStringList l;
                        l<<list.at(0)<<list.at(1)<<list.at(2)<<QString::number(re)<<list.at(4);
                        list=l;
                        //check<<list.at(3)<<endl;
                    }
                }
                line[i]=list;
                i++;
            }
        }
        usrinfo.close();
        usrinfo.resize(0);
        if(usrinfo.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&usrinfo);
            for(int j=0;j<i;j++)
            {
                stream<<line[j].join(" ")<<endl;
            }
        }
        usrinfo.close();

        if(flag1==0){
            QFile out(AddressOfLogMessage);
            if(out.open(QIODevice::WriteOnly|QIODevice::Append))
            {
                Log log(b,name,2019,8,3);
                QTextStream in(&out);
                QString bookname=log.getBook_name();
                int bookkind=log.getBook_kind();
                QString bookid=log.getBook_id();
                QString usrname=log.getUsr_name();
                int year=log.get_year();
                int month=log.get_month();
                int day=log.get_day();
                in<<bookname<<" "<<bookkind<<" "<<bookid<<" "<<usrname<<" "<<year<<" "<<month<<" "<<day<<endl;
                //in<<log.getBook_name()<<" "<<log.getBook_kind()<<" "<<log.getBook_id().toLocal8Bit().data()<<" "<<log.getUsr_name()<<" "<<log.get_year()<<" "<<log.get_month()<<" "<<log.get_day()<<" "<<"\r\n";
            }
            out.close();
            ui->label_3->setText("借书成功！");
        }
        else ui->label_3->setText("借书数量已经达到最大值");
    }
}
