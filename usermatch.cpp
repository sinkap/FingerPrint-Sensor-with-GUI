#include "usermatch.h"
#include "ui_usermatch.h"





UserMatch::UserMatch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserMatch)
{
    ui->setupUi(this);

}

UserMatch::~UserMatch()
{
    delete ui;
}




