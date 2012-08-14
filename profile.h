#ifndef PROFILE_H
#define PROFILE_H

#endif // PROFILE_H

#include <QDialog>
#include <QSpinBox>

class QLabel;
class QPushButton;

class Profile:public QDialog{

    Q_OBJECT;

public:

    Profile(QWidget *parent = 0);

public:

    QLabel *firstname;
    QLabel *lastname;
    QLabel *age;
    QLabel *gender;
    QLabel *kerosene;
    QSpinBox *litres;
    QPushButton *dispense;
};
