#include "profile.h"
#include <QtGui>



Profile::Profile(QWidget *parent)
          : QDialog(parent) {

 firstname = new QLabel(tr("Name: "));
 lastname = new QLabel(tr("Last Name: "));
 age= new QLabel(tr("Age: "));
 gender= new QLabel(tr("Gender: "));
 kerosene= new QLabel(tr("Kerosene Quota: "));
 litres = new QSpinBox;
 dispense = new QPushButton(tr("Dispense"));

 QHBoxLayout *bottomButtons = new QHBoxLayout;
 QVBoxLayout *topLeftLabels = new QVBoxLayout;
 QVBoxLayout *mainLayout = new QVBoxLayout;

 //labels added to the top left layout
 topLeftLabels->addWidget(firstname);
 topLeftLabels->addWidget(lastname);
 topLeftLabels->addWidget(age);
 topLeftLabels->addWidget(gender);
 topLeftLabels->addWidget(kerosene);

 bottomButtons->addWidget(dispense);
 bottomButtons->addWidget(litres);

 mainLayout->addLayout(topLeftLabels);
 mainLayout->addLayout(bottomButtons);

 setLayout(mainLayout);

 setWindowTitle(tr("User Profile"));
 setFixedHeight(290);
 setFixedWidth(240);
}
