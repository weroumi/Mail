#include "edit.h"
#include "ui_edit.h"

edit::edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit)
{
    ui->setupUi(this);
}

edit::~edit()
{
    delete ui;
}

void edit::set(User current){
    ui->txt_name->setText(current.get_name());
    ui->txt_place->setText(current.get_place());
}

void edit::on_btn_save_clicked()
{
    emit signal_edit(ui->txt_name->text(),  ui->txt_place->text());
    close();
}

