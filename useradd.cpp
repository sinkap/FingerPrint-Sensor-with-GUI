#include "useradd.h"
#include "ui_useradd.h"
#include "Database.h"

extern int add_fingerprint(unsigned short);
extern int search_fingerprint_id(unsigned short);
extern int getAddress();
extern void updateLocation(int);
extern QSqlDatabase openDB(QString);

UserAdd::UserAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserAdd)
{
    ui->setupUi(this);
    finger_success = 0;

    ui->comboBox->insertItem(1,"Male");
    ui->comboBox->insertItem(2,"Female");

    QRegExp regExp("^[A-Za-z]{1,30}$");
    QRegExp regAge("^[0-9]{1,3}$");

    ui->FirstNameEdit->setValidator(new QRegExpValidator(regExp, this));
    ui->LastNameEdit->setValidator(new QRegExpValidator(regExp, this));
    ui->AgeEdit->setValidator(new QRegExpValidator(regAge, this));


}

UserAdd::~UserAdd()
{
    delete ui;
}


void UserAdd::Add_FingerPrint() {

    int addr;
    addr = getAddress();
    printf("%d\n",addr);
    QMessageBox msg;

    if (search_fingerprint_id(addr)) {

       if(!(add_fingerprint(addr))) {
            msg.setText("FingerPrint added");
            ui->lcdNumber->display(addr);
            updateLocation(addr);
            finger_success = 1;
            finger_addr = addr;
            msg.exec();
       }

        else {
            msg.setText("Looks Like a problem...Try Again..");
            msg.exec();
       }
    }


    else {
        updateLocation(addr);
        msg.setText("Looks Like a problem...Try Again..(Database Location Full)");
        msg.exec();

    }


}

void UserAdd::on_AddFingerPrint_clicked()
{
    Add_FingerPrint();

}

void UserAdd::on_SubmitButton_clicked()
{   QString gender;
    QSqlDatabase db;
    QMessageBox outcome;
    int error = 0;
    outcome.setText("The following errors were found:");
    QSqlQuery query;


    if(!ui->FirstNameEdit->hasAcceptableInput()) {
        outcome.setText(outcome.text() + "\nFirst Name has to be 1 to 30 characters long and can contain only alphabets");
        error += 1;
    }


    if(!ui->LastNameEdit->hasAcceptableInput()) {
        outcome.setText(outcome.text() + "\nLast Name has to be 1 to 30 characters long and can contain only alphabets");
        error += 1;
     }

    if(!ui->AgeEdit->hasAcceptableInput()) {
        outcome.setText(outcome.text() + "Age can contain only numbers to a maximum of 999");
        error += 1;
    }

    if(finger_success == 0){

        outcome.setText(outcome.text() + "You have not added the finger Print");
        error += 1;
    }


    if (error)
        outcome.exec();

    if (!error) {

        query.exec("select max(id) from user");
        query.next();
        int max_id;
        max_id = query.value(0).toInt();
        if (ui->comboBox->currentText() == "Male")
            gender = "M";
         if (ui->comboBox->currentText() == "Female")
             gender = "F";

        max_id += 1;
        query.exec(QString("insert into user values('%1','%2','%3','%4','%5','%6','%7')").arg(max_id).arg(ui->FirstNameEdit->text()).arg(ui->LastNameEdit->text()).arg(ui->AgeEdit->text()).arg(gender).arg(finger_addr).arg(ui->keroseneSpinBox->value()));

        close();
    }


}



void UserAdd::on_pushButton_clicked()
{
    close();
}
