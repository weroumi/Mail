#include "signup.h"
#include "ui_signup.h"
#include <QMessageBox>

signup::signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);
}

signup::~signup()
{
    delete ui;
}

void signup::on_btn_signup_clicked()
{
    try {
        emit signal_signup(User(ui->txt_name->text(), ui->txt_email->text(), ui->txt_place->text(), ui->txt_password->text()));
    } catch (std::exception& exc) {
        QMessageBox msg;
        msg.setWindowIcon(this->windowIcon());
        msg.setText(QString::fromStdString(std::string(exc.what())));
        msg.setIcon(QMessageBox::Critical);
        QPushButton *btn_ok = msg.addButton(QMessageBox::Ok);
        msg.exec();
        if(msg.clickedButton() == btn_ok) return;
    }

    ui->txt_name->clear();
    ui->txt_email->clear();
    ui->txt_place->clear();
    ui->txt_password->clear();
}
