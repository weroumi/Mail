#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    login_dialog = new login(this);
    signup_dialog = new signup(this);
    write_dialog = new write(this);
    edit_dialog = new edit(this);

    ui->tab_sent->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tab_received->setContextMenuPolicy(Qt::CustomContextMenu);

    ui->tab_sent->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tab_sent->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tab_sent->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->tab_sent->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tab_received->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tab_received->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tab_received->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->tab_received->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tab_users->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tab_users->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tab_users->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->tab_users->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(login_dialog, &login::signal_login, this, &MainWindow::slot_login);
    connect(signup_dialog, &signup::signal_signup, this, &MainWindow::slot_signup);
    connect(write_dialog, &write::signal_write, this, &MainWindow::slot_write);
    connect(edit_dialog, &edit::signal_edit, this, &MainWindow::slot_edit);
    connect(write_dialog, &write::signal_draft, this, &MainWindow::slot_draft);
    connect(ui->tab_sent, &MainWindow::customContextMenuRequested, this, &MainWindow::show_context_menu_sent);
    connect(ui->tab_received, &MainWindow::customContextMenuRequested, this, &MainWindow::show_context_menu_received);

    mail.set_mail();

    ui->widget_admin->hide();
    ui->actionSign_out->setDisabled(true);
    ui->actionWrite->setDisabled(true);
    ui->actionWrite->setToolTip("Log in to write an email");
    login_dialog->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete login_dialog;
    delete signup_dialog;
    delete write_dialog;
}

void MainWindow::slot_login(User login_user){
    try{
        ui->lbl_greeting->clear();
        ui->actionSign_out->setDisabled(false);
        if(login_user.get_email() == "admin" && login_user.get_password() == "admin"){
            ui->txt_a_email->clear();
            ui->txt_a_address->clear();
            ui->widget_admin->show();
            ui->actionWrite->setDisabled(true);
            ui->actionLog_in->setDisabled(true);
            ui->actionSign_up->setDisabled(true);
            ui->actionEdit->setDisabled(true);
            ui->actionDrafts->setDisabled(true);
            ui->actionWrite->setToolTip("Log in as a user to write an email");
            mail.admin_log_in(ui->tab_users);
            login_dialog->close();
            return;
        }
        ui->actionWrite->setToolTip("Write");
        ui->actionWrite->setDisabled(false);
        ui->actionLog_in->setDisabled(false);
        ui->actionSign_up->setDisabled(false);
        ui->actionEdit->setDisabled(false);
        ui->actionDrafts->setDisabled(false);
        ui->widget_admin->hide();
        ui->txt_filter_received->clear();
        ui->tab_received->clearContents();
        ui->tab_sent->clearContents();
        ui->tab_received->setRowCount(0);
        ui->tab_sent->setRowCount(0);
        ui->tab_received->sortItems(2, Qt::AscendingOrder);
        ui->tab_sent->sortItems(2, Qt::AscendingOrder);
        mail.log_in(login_user, ui->tab_received, ui->tab_sent, ui->lbl_greeting);
        login_dialog->close();
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

void MainWindow::slot_signup(User new_user){
    mail.sign_up(new_user);
    mail.log_out();
    mail.log_in(new_user, ui->tab_received, ui->tab_sent, ui->lbl_greeting);
    ui->actionWrite->setDisabled(false);
    signup_dialog->close();
}

void MainWindow::slot_write(Message msg){
    mail.write(msg, ui->tab_sent);
    write_dialog->close();
}

void MainWindow::slot_draft(Message draft){
    mail.set_draft(draft);
    write_dialog->close();
}

void MainWindow::on_btn_log_in_clicked()
{
    login_dialog->show();
}

void MainWindow::show_context_menu_sent(QPoint pos){
    QPoint globalPos = ui->tab_sent->mapToGlobal(pos);
    tab = ui->tab_sent;
    QMenu menu;
    menu.addAction("Sort by time (ascending)", this, SLOT(sort_time_asc()));
    menu.addAction("Sort by time (descending)",  this, SLOT(sort_time_desc()));
    menu.addAction("Sort by size (ascending)", this, SLOT(sort_size_asc()));
    menu.addAction("Sort by size (descending)", this, SLOT(sort_size_desc()));
    // Show context menu at handling position
    menu.exec(globalPos);
}

void MainWindow::show_context_menu_received(QPoint pos){
    QPoint globalPos = ui->tab_received->mapToGlobal(pos);
    tab = ui->tab_received;
    QMenu menu;
    menu.addAction("Sort by time (ascending)", this, SLOT(sort_time_asc()));
    menu.addAction("Sort by time (descending)",  this, SLOT(sort_time_desc()));
    menu.addAction("Sort by size (ascending)", this, SLOT(sort_size_asc()));
    menu.addAction("Sort by size (descending)", this, SLOT(sort_size_desc()));
    // Show context menu at handling position
    menu.exec(globalPos);

}

void MainWindow::sort_time_asc(){
    tab->setSortingEnabled(false);
    if(tab == ui->tab_sent)
       mail.get_current_user().sort_sent_msgs_time(User::ascending, tab);
    else if(tab == ui->tab_received)
        mail.get_current_user().sort_rece_msgs_time(User::ascending, tab);
}

void MainWindow::sort_time_desc(){
    tab->setSortingEnabled(false);
    if(tab == ui->tab_sent)
       mail.get_current_user().sort_sent_msgs_time(User::descending, tab);
    else if(tab == ui->tab_received)
        mail.get_current_user().sort_rece_msgs_time(User::descending, tab);
}

void MainWindow::sort_size_asc(){
    tab->setSortingEnabled(false);
    if(tab == ui->tab_sent)
        mail.get_current_user().sort_sent_msgs_size(User::ascending, tab);
    else if(tab == ui->tab_received)
         mail.get_current_user().sort_rece_msgs_size(User::ascending, tab);
}

void MainWindow::sort_size_desc(){
    tab->setSortingEnabled(false);
    if(tab == ui->tab_sent)
       mail.get_current_user().sort_sent_msgs_size(User::descending, tab);
    else if(tab == ui->tab_received)
        mail.get_current_user().sort_rece_msgs_size(User::descending, tab);
}

void MainWindow::on_txt_filter_received_editingFinished()
{
    try{
    mail.filter(ui->txt_filter_received->text(), ui->tab_received);
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

void MainWindow::on_actionLog_in_triggered()
{
    login_dialog->show();
}

void MainWindow::on_actionSign_up_triggered()
{
    signup_dialog->show();
}

void MainWindow::on_actionWrite_triggered()
{
    write_dialog->show();
}

void MainWindow::on_btn_search_inactive_clicked()
{
    mail.admin_search_inactive_users(ui->tab_users);
}

void MainWindow::on_txt_a_email_editingFinished()
{
    ui->txt_a_address->clear();
    if(ui->txt_a_email->text().isEmpty()){
        mail.admin_search_inactive_users(ui->tab_users);
        ui->txt_a_email->clear();
        return;
    }
    try{
        mail.admin_get_info_about_user(ui->txt_a_email->text(), ui->comboBox->currentText(), ui->tab_users, ui->txt_a_address);
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

void MainWindow::on_actionSign_out_triggered()
{
    ui->widget_admin->hide();
    ui->tab_received->clearContents();
    ui->tab_received->setRowCount(0);
    ui->tab_sent->clearContents();
    ui->tab_sent->setRowCount(0);
    mail.log_out();
    ui->actionWrite->setDisabled(true);
    ui->actionLog_in->setDisabled(false);
    ui->actionSign_up->setDisabled(false);
    ui->actionSign_out->setDisabled(true);
    ui->actionEdit->setDisabled(true);
    ui->actionDrafts->setDisabled(true);
    ui->actionWrite->setToolTip("Log in to write an email");
    ui->lbl_greeting->clear();
}


void MainWindow::on_actionEdit_triggered()
{
    edit_dialog->set(mail.get_current_user());
    edit_dialog->show();
}

void MainWindow::slot_edit(QString name, QString place){
    mail.edit_user(name, place);
}

void MainWindow::on_actionDrafts_triggered()
{
    write_dialog->set_draft(mail.get_current_user().get_draft().get_text(), mail.get_current_user().get_draft().get_receiver_str());
    write_dialog->show();
}


void MainWindow::on_comboBox_editTextChanged(const QString &arg1)
{
    ui->txt_a_email->editingFinished();
}

