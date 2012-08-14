#ifndef ADMINMATCH_H
#define ADMINMATCH_H

#include <QDialog>

namespace Ui {
    class adminmatch;
}

class adminmatch : public QDialog
{
    Q_OBJECT

public:
    explicit adminmatch(QWidget *parent = 0);
    ~adminmatch();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();



    void on_try_2_clicked();

private:
    Ui::adminmatch *ui;
};

#endif // ADMINMATCH_H
