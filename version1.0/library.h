#ifndef LIBRARY_H
#define LIBRARY_H

#include <QDialog>

namespace Ui {
class Library;
}

class Library : public QDialog
{
    Q_OBJECT

public:
    explicit Library(QWidget *parent = 0);
    ~Library();

private slots:
    void on_OK_Button_clicked();

private:
    Ui::Library *ui;
};

#endif // LIBRARY_H
