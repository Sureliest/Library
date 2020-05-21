#ifndef CHECKKIND_H
#define CHECKKIND_H

#include <QDialog>

namespace Ui {
class CheckKind;
}

class CheckKind : public QDialog
{
    Q_OBJECT

public:
    explicit CheckKind(QWidget *parent = 0);
    ~CheckKind();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CheckKind *ui;
};

#endif // CHECKKIND_H
