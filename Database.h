#ifndef DATABASE_H
#define DATABASE_H

#endif // DATABASE_H

#include <QObject>
#include <QtSql/QtSql>
#include <QtCore/QString>
#include <QtCore/QObject>
#include <QtGui/QMessageBox>

class PersonData
    {
    public:
        int     id;
        QString firstname;
        QString lastname;
        int     age;
        QString gender;
        int     finger_address;
        int     kerosene;
        int     empty_flag;

    public:
    PersonData();

};




