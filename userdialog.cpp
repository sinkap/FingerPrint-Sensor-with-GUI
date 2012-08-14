#include "userdialog.h"
#include "ui_userdialog.h"
#include "profile.h"
#include "Database.h"

//external prototypes
extern int match_fingerprint_id (unsigned short , unsigned short);
extern PersonData getPerson(int, PersonData);

//main class source

UserDialog::UserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDialog)
{
    ui->setupUi(this);
}

UserDialog::~UserDialog()
{
    delete ui;
}

void UserDialog::on_BackButton_clicked()
{
    close();
}

void UserDialog::on_AuthenticateButton_clicked()
{
    QMessageBox msg;
    int match_id;
    PersonData person;
    Profile user;
    match_id = MatchFingerPrint();

    if (match_id > 0) {

        printf("%d\n",match_id);
    person = getPerson(match_id,person);

        if (person.empty_flag){

            QString sex;
            if (person.gender == "M")
                sex = "Male";
            if (person.gender == "F")
                sex = "Female";

            user.firstname->setText(user.firstname->text() + person.firstname);
            user.lastname->setText(user.lastname->text() + person.lastname);
            user.gender->setText(user.gender->text() + sex);
            user.age->setText(user.age->text() + QString("%1").arg(person.age));
            user.kerosene->setText(user.kerosene->text() + QString("%1").arg(person.kerosene));
            user.litres->setRange(1,person.kerosene);
            user.exec();


        }


        else {
            msg.setText("Your Profile Does Not Exist Contact Admin");
            msg.exec();
        }
    }

}

int UserDialog::MatchFingerPrint(){

 //wrapper around the match_fingerprint_id function

    QMessageBox msgBox;
    int result;
    int i;


    for (i=0; i< 3; i++) {

    result = match_fingerprint_id(0x000A,0x00FF);

    //The scanning range is from location 11 to location 256 thereby allowing the database to store
    //around 240 user templates..



    if( result > 0x000A) {

        return result;

    }

    if ( (result >= 0x0000) && (result < 0x000A)  ) {


         msgBox.setText("You are an admin..Login from the admin account");
         msgBox.exec();
         result = -1;
         i=3;
    }
    if (result < 0)

        msgBox.setText("Try Swiping Again");
        msgBox.exec();
    }

    if  (result < 0) {
        msgBox.setText("Not Validated ..Contact admin");
        msgBox.exec();
  }

    return result;
}

