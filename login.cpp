#include "login.h"
#include <QMessageBox>
#include "ui_login.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_btn_log_in_clicked()
{
    try {
        emit signal_login(User(ui->txt_email_address->text(), ui->txt_password->text()));
    } catch (std::exception& exc) {
        QMessageBox msg;
        msg.setWindowIcon(this->windowIcon());
        msg.setText(QString::fromStdString(std::string(exc.what())));
        msg.setIcon(QMessageBox::Critical);
        QPushButton *btn_ok = msg.addButton(QMessageBox::Ok);
        msg.exec();
        if(msg.clickedButton() == btn_ok) return;
    }
    ui->txt_email_address->clear();
    ui->txt_password->clear();
}


void login::on_btn_sign_up_clicked()
{

}

