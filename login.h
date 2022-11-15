// Class for additional window
// to log in to acount
#ifndef LOGIN_H
#define LOGIN_H

#include "user.h"
#include <QDialog>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_btn_log_in_clicked();

    void on_btn_sign_up_clicked();

private:
    Ui::login *ui;
signals:
    void signal_login(User login_user);
};

#endif // LOGIN_H
