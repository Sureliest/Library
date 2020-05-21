#ifndef LEND_H
#define LEND_H

#include <QDialog>

namespace Ui {
class Lend;
}

class Lend : public QDialog
{
    Q_OBJECT

public:
    explicit Lend(QWidget *parent = 0);
    ~Lend();

private slots:
    void on_sort_clicked();

private:
    Ui::Lend *ui;
};

#endif // LEND_H
