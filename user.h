// This class is used to manage data of one user
// including their sent and received messages
#ifndef USER_H
#define USER_H
#include <QString>
#include <vector>
#include <QTableWidget>
#include "message.h"

class User
{
    QString m_name;
    QString m_email;
    QString m_place_of_registration;
    QString m_password;
    std::vector<Message> m_sent_messages;
    std::vector<Message> m_received_messages;
    Message m_draft;
public:
    const static bool ascending = 1;
    const static bool descending = 0;

    User();

    User(QString name, QString email, QString place, QString password);

    User(QString email);

    User(QString email, QString password);

    User(const User& other);

    ~User();

    bool operator<(const User& other) const;

    User operator=(const User& other);

    QString get_name();

    QString get_email();

    QString get_place();

    QString get_password();

    void push_sent_msg(Message msg);

    void push_received_msg(Message msg);

    void tab_sent(QTableWidget* tab);

    void tab_received(QTableWidget* tab);

    void tab_received_filter(QTableWidget* tab, QString sender);

    void tab_sent_to(QTableWidget* tab);

    void tab_received_from(QTableWidget* tab);

    void sort_sent_msgs_size (bool order, QTableWidget* tab);

    void sort_rece_msgs_size (bool order, QTableWidget* tab);

    void sort_sent_msgs_time(bool order, QTableWidget* tab);

    void sort_rece_msgs_time(bool order, QTableWidget* tab);

    bool is_inactive();

    QString last_address();

    void log_out();

    void edit(QString name, QString place);

    void set_draft(Message draft);

    Message get_draft();

    static void set_row(QTableWidget* tab, int row, QString item_col1, QString item_col2, QString item_col3);
};

#endif // USER_H
