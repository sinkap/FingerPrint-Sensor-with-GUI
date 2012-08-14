#include "adminmatch.h"
#include "ui_adminmatch.h"
#include "useradd.h"

#include <QtGui>

extern void init_DB();
extern int add_fingerprint(unsigned short);

adminmatch::adminmatch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminmatch)
{

    ui->setupUi(this);
    ui->try_2->setVisible(false);
}

adminmatch::~adminmatch()
{
    delete ui;
}


void adminmatch::on_pushButton_clicked()
{
    UserAdd newUser;
    close();
    newUser.exec();
}

void adminmatch::on_pushButton_2_clicked()
{
    ui->label->setText("Wait..");
    init_DB();

    short addr = 5;
    QMessageBox msg;
    msg.setText("Place Your Left Thumb on the sensor");
    msg.exec();
    if (add_fingerprint(addr))
       ui->try_2->setVisible(true);
    else
        ui->label->setText("Done..");


}


void adminmatch::on_try_2_clicked()
{
    short addr = 5;
    if(add_fingerprint(addr))
        ui->label->setText("Faileed..Try Again");
    else{

        ui->label->setText("Done..");
        ui->try_2->setVisible(false);
    }
}
