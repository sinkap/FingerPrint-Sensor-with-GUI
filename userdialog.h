#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>

namespace Ui {
    class UserDialog;
}

class UserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserDialog(QWidget *parent = 0);
    ~UserDialog();
    int MatchFingerPrint();

private slots:
    void on_BackButton_clicked();

    void on_AuthenticateButton_clicked();

private:
    Ui::UserDialog *ui;
};

#endif // USERDIALOG_H
