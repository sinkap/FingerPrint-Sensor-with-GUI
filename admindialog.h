#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>

namespace Ui {
    class admindialog;
}

class admindialog : public QDialog
{
    Q_OBJECT

public:
    explicit admindialog(QWidget *parent = 0);
    ~admindialog();

private slots:
    void on_BackButton_clicked();

    void on_AuthenticAdmButton_clicked();

    int MatchFingerPrint();

private:
    Ui::admindialog *ui;
};

#endif // ADMINDIALOG_H
