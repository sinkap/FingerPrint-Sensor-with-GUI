#ifndef USERADD_H
#define USERADD_H

#include <QDialog>

namespace Ui {
    class UserAdd;
}

class UserAdd : public QDialog
{
    Q_OBJECT

public:
    explicit UserAdd(QWidget *parent = 0);
    ~UserAdd();

    Ui::UserAdd *ui;

public:

    void Add_FingerPrint();
    int finger_success;
    int finger_addr;


private slots:
    void on_AddFingerPrint_clicked();
    void on_SubmitButton_clicked();
    void on_pushButton_clicked();
};

#endif // USERADD_H
