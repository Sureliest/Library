#ifndef RETURN_H
#define RETURN_H

#include <QDialog>

namespace Ui {
class Return;
}

class Return : public QDialog
{
    Q_OBJECT

public:
    explicit Return(QWidget *parent = 0);
    ~Return();

private slots:
    void on_pushButton_clicked();

    void on_OK_Button_clicked();

private:
    Ui::Return *ui;
};

#endif // RETURN_H
