#include "admindialog.h"
#include "ui_admindialog.h"

admindialog::admindialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admindialog)
{
    ui->setupUi(this);
}

admindialog::~admindialog()
{
    delete ui;
}

void admindialog::on_BackButton_clicked()
{
    close();
}
