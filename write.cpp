#include "write.h"
#include "ui_write.h"
#include <QDateTime>
#include <QMessageBox>
#include <string>
#include <QFile>
#include <QFileDialog>

write::write(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::write)
{
    ui->setupUi(this);
}

write::~write()
{
    delete ui;
}

void write::on_btn_send_clicked()
{
    QDateTime current = QDateTime::currentDateTime();
    try{
    emit signal_write(Message(ui->txt_message->toPlainText(), ui->txt_receiver->text(), current));
    }catch(std::exception& exc){
        QMessageBox msg;
        msg.setWindowIcon(this->windowIcon());
        msg.setText(QString::fromStdString(std::string(exc.what())));
        msg.setIcon(QMessageBox::Critical);
        QPushButton *btn_ok = msg.addButton(QMessageBox::Ok);
        msg.exec();
        if(msg.clickedButton() == btn_ok) return;
    }
    ui->txt_message->clear();
    ui->txt_receiver->clear();
}


void write::on_pushButton_clicked()
{
    try{
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file1(filename);
    if(file1.open(QFile::ReadOnly)){
        QTextStream in(&file1);
        ui->txt_message->setPlainText(in.readLine());
    }
    file1.close();
    }catch(std::exception& exc){
        QMessageBox msg;
        msg.setWindowIcon(this->windowIcon());
        msg.setText(QString::fromStdString(std::string(exc.what())));
        msg.setIcon(QMessageBox::Critical);
        QPushButton *btn_ok = msg.addButton(QMessageBox::Ok);
        msg.exec();
        if(msg.clickedButton() == btn_ok) return;
    }
}


void write::on_pushButton_2_clicked()
{
    try{
        emit signal_draft(Message(ui->txt_message->toPlainText(), ui->txt_receiver->text()));
    }catch(std::exception& exc){
        QMessageBox msg;
        msg.setWindowIcon(this->windowIcon());
        msg.setText(QString::fromStdString(std::string(exc.what())));
        msg.setIcon(QMessageBox::Critical);
        QPushButton *btn_ok = msg.addButton(QMessageBox::Ok);
        msg.exec();
        if(msg.clickedButton() == btn_ok) return;
    }
    ui->txt_message->clear();
    ui->txt_receiver->clear();
}

void write::set_draft(QString text, QString receiver){
    ui->txt_receiver->setText(receiver);
    ui->txt_message->setPlainText(text);
}
