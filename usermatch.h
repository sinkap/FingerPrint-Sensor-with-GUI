#ifndef USERMATCH_H
#define USERMATCH_H

#include <QDialog>
#include <QtGui/QMessageBox>

namespace Ui {
    class UserMatch;
}

class UserMatch : public QDialog
{
    Q_OBJECT

public:
    explicit UserMatch(QWidget *parent = 0);
    ~UserMatch();


private slots:



private:
    Ui::UserMatch *ui;
};

#endif // USERMATCH_H
