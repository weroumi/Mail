// Class for the main window of the program
// connects GUI and the program itself
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <set>
#include <QFile>
#include <QTextStream>

#include "edit.h"
#include "qurl.h"
#include "user.h"
#include "login.h"
#include "signup.h"
#include "write.h"
#include "mail.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_log_in_clicked();

    void slot_login(User login_user);

    void slot_signup(User new_user);

    void slot_write(Message msg);

    void slot_edit(QString name, QString place);

    void slot_draft(Message draft);

    void show_context_menu_sent(QPoint pos);

    void show_context_menu_received(QPoint pos);

    void sort_time_asc();

    void sort_time_desc();

    void sort_size_asc();

    void sort_size_desc();

    void on_txt_filter_received_editingFinished();

    void on_actionLog_in_triggered();

    void on_actionSign_up_triggered();

    void on_actionWrite_triggered();

    void on_btn_search_inactive_clicked();

    void on_txt_a_email_editingFinished();

    void on_actionSign_out_triggered();

    void on_actionEdit_triggered();

    void on_actionDrafts_triggered();

    void on_comboBox_editTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    login* login_dialog;
    signup* signup_dialog;
    write* write_dialog;
    edit* edit_dialog;
    mail mail;
    QTableWidget* tab;
};
#endif // MAINWINDOW_H
