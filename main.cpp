#include <QtGui/QApplication>
#include <QtSql/QtSql>
#include <QtGui>
#include "mainwindow.h"
#include "Database.h"
#include "progress.h"

extern int serial_init();
extern int empty_db();
extern QSqlDatabase openDB(QString path) {

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel,
                     QMessageBox::NoButton);

    }

return db;
}




extern int getAddress(){

  QSqlDatabase db;
  int addr;
  db = openDB("/sdcard/db.fpsense");
  QSqlQuery query(QString("select * from location where occupied = 'N' and id > 10 limit 1"));
  if (query.next())
    addr = query.value(0).toInt();
  else {


      return -1;

  }

  return addr;

}

extern void updateLocation(int addr){
    QSqlDatabase db;
    db = openDB("/sdcard/db.fpsense");
    QSqlQuery query;
    query.exec(QString("update location set occupied = 'Y' where id = %1").arg(addr));

}

extern PersonData getPerson(int id, PersonData person)
    {
        QSqlDatabase db;
        db = openDB("/sdcard/db.fpsense");
        QSqlQuery query(QString("select * from user where finger_addr = %1").arg(id));

        if (query.next()){
        person.id = query.value(0).toInt();
        person.firstname = query.value(1).toString();
        person.lastname = query.value(2).toString();
        person.age = query.value(3).toInt();
        person.gender = query.value(4).toString();
        person.kerosene = query.value(6).toInt();
        person.empty_flag = 1;
        }


        return person;
    }

extern void init_DB()

{


 QSqlDatabase db;

 empty_db();
 openDB("/sdcard/db.fpsense");
 QSqlQuery query;
 QMessageBox msg;
 query.exec("DROP TABLE location");
 query.exec("DROP TABLE user");
 query.exec("CREATE TABLE user (id int primary key, firstname varchar[20], lastname varchar[20], age int, gender char, finger_addr int, kerosene int) ");
 query.exec("CREATE TABLE location (id int primary key , occupied char )");

int i;
 for(i=0; i < 50; i++){

     query.exec(QString("INSERT INTO location values('%1','N')").arg(i));

 }

 /*QVariantList ids;
 QVariantList occ;

 int i;
 for (i=0; i < 50; i++) {

     ids << i;
     occ << "N";
 }

 query.prepare("insert into location values (?, ?)");
 query.addBindValue(ids);
 query.addBindValue(occ);
 if (!query.execBatch())
      qDebug() << query.lastError();
*/



}

int main(int argc, char *argv[])
{



    QApplication a(argc, argv);

    QSplashScreen *splash = new QSplashScreen;

    splash->setPixmap(QPixmap("images/splash.png"));
    splash->show();
    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash->showMessage(QObject::tr("serial port..."),
                        topRight, Qt::white);
    serial_init();
    sleep(2);

    splash->showMessage(QObject::tr("databases..."),
                        topRight, Qt::white);
    sleep(2);


    splash->showMessage(QObject::tr("Kapileshwar..."),
                      topRight, Qt::white);
    sleep(1);
    splash->showMessage(QObject::tr("Salil..."),
                      topRight, Qt::white);
    sleep(1);

    splash->showMessage(QObject::tr("Sonal..."),
                      topRight, Qt::white);
    sleep(1);
    splash->showMessage(QObject::tr("Setting up window..."),
                      topRight, Qt::white);


    sleep(2);
    MainWindow M;

    M.show();
    splash->finish(&M);
    PersonData person;


    return a.exec();
}

