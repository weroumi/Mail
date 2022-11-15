// This class is used to manage all users
// and their messages in the system
#ifndef MAIL_H
#define MAIL_H

#include "qlabel.h"
#include "user.h"
#include <set>
#include <vector>
#include <QTextBrowser>
class mail
{
    std::set<User> user;
    std::vector<Message> messages;
    User current_user;
    QString time_format = "dd.MM.yyyy hh:mm:ss";
public:
    mail();

    void set_mail();

    void log_in(User login_user, QTableWidget *tab_received, QTableWidget *tab_sent, QLabel* lbl);

    void log_out();

    void admin_log_in(QTableWidget* tab_users);

    void sign_up(User new_user);

    void write(Message msg, QTableWidget *tab_sent);

    void filter(QString email_filter, QTableWidget* tab);

    void admin_search_inactive_users(QTableWidget* tab_users);

    void admin_get_info_about_user(QString email, QString option, QTableWidget* tab_users, QTextBrowser* txt);

    User get_current_user();

    void edit_user(QString name, QString place);

    void reset_mail();

    void set_draft(Message draft);

    static int message_box(std::exception& exc, QIcon icon);
};

#endif // MAIL_H
