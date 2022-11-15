// This is class for additional window of the program
// so that it could be easier to sign up
#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include "user.h"

namespace Ui {
class signup;
}

class signup : public QDialog
{
    Q_OBJECT

public:
    explicit signup(QWidget *parent = nullptr);
    ~signup();

private:
    Ui::signup *ui;
signals:
    void signal_signup(User new_user);
private slots:
    void on_btn_signup_clicked();
};

#endif // SIGNUP_H
