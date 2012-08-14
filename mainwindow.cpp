#include "mainwindow.h"
#include "admindialog.h"
#include "userdialog.h"
#include "LibFinger.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_UserButton_clicked()
{
    UserDialog Usr;
    Usr.exec();

}

void MainWindow::on_AdminButton_clicked()
{
    admindialog adm;
    adm.exec();
}

