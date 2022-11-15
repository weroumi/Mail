#include "user.h"
#include "emptyfield_error.h"
#include "name_error.h"

User::User(){
    m_name = "";
    m_email = "";
    m_place_of_registration = "";
    m_password = "";
}

User::User(QString name, QString email, QString place, QString password){
    if(name.isEmpty() || email.isEmpty() || place.isEmpty() || password.isEmpty())
        throw emptyfield_error();
    bool checker = 0;
    for(int i = 0; i < name.size(); ++i){
        if(name[i].isDigit()) checker = 1;
        //if(!name[i].isLetter() && !name[i].isSpace())
    }
    if(name.size() < 4) checker = 1;
    if(!name.contains(" ")) checker = 1;
    if(checker == 1)
        throw name_error();
    m_name = name;
    m_email = email;
    m_place_of_registration = place;
    m_password = password;
}

User::User(QString email){
    m_email = email;
}

User::User(QString email, QString password){
    if(email.isEmpty() || password.isEmpty())
        throw emptyfield_error();
    m_email = email;
    m_password = password;
}

User::~User(){
}

User::User(const User& other){
    this->m_name = other.m_name;
    this->m_email = other.m_email;
    this->m_place_of_registration = other.m_place_of_registration;
    this->m_received_messages = other.m_received_messages;
    this->m_sent_messages = other.m_sent_messages;
    this->m_password = other.m_password;
    this->m_draft = other.m_draft;
    this->m_draft = other.m_draft;
}

bool User::operator<(const User& other) const{
    return this->m_email < other.m_email;
}

User User::operator=(const User& other){ //повертає User, бо можна написати a = b = c = d;
    if(this != &other){ //перевірка відмінности адрес операндів
        this->m_email = other.m_email;
        this->m_name = other.m_name;
        this->m_place_of_registration = other.m_place_of_registration;
        this->m_received_messages = other.m_received_messages;
        this->m_sent_messages = other.m_sent_messages;
        this->m_password = other.m_password;
        this->m_draft = other.m_draft;
    }
    return *this;
}

QString User::get_name(){
    return m_name;
}

QString User::get_email(){
    return m_email;
}

QString User::get_place(){
    return m_place_of_registration;
}

QString User::get_password(){
    return m_password;
}

void User::push_sent_msg(Message msg){
    m_sent_messages.push_back(msg);
}

void User::push_received_msg(Message msg){
    m_received_messages.push_back(msg);
}

void User::tab_sent(QTableWidget* tab){
    if(m_sent_messages.empty() == 0){
        tab->clearContents();
        tab->setRowCount(m_sent_messages.size());
        for(int i = 0; i < m_sent_messages.size(); ++i){
            set_row(tab, i, m_sent_messages[i].get_receiver_str(), m_sent_messages[i].get_text(), m_sent_messages[i].get_time_sent());
        }
        tab->resizeRowsToContents();
    }
}

void User::tab_received(QTableWidget* tab){
    if(m_received_messages.empty() == 0){
        tab->clearContents();
        tab->setRowCount(m_received_messages.size());
        for(int i = 0; i < m_received_messages.size(); ++i)
            set_row(tab, i, m_received_messages[i].get_sender_str(), m_received_messages[i].get_text(), m_received_messages[i].get_time_sent());
        tab->resizeRowsToContents();
    }
}

void User::tab_received_filter(QTableWidget* tab, QString sender){
    std::vector<Message> msgs;
    tab->clearContents();
    int j = 0;
    for(int i = 0; i < m_received_messages.size(); ++i){
        if(m_received_messages[i].get_sender() == sender){
            tab->setRowCount(j + 1);
            set_row(tab, j, m_received_messages[i].get_sender_str(), m_received_messages[i].get_text(), m_received_messages[i].get_time_sent());
            j++;
        }
    }
    tab->resizeRowsToContents();
}

void User::tab_sent_to(QTableWidget* tab){
    tab->clearContents();
    tab->setRowCount(0);
    int count = 1;
    for(int i = 0; i < m_sent_messages.size(); ++i){
        bool checker = 1;
        for(int j = 0; j < i; ++j){
            if(i != 0){
                if(m_sent_messages[i].get_receiver_str() == m_sent_messages[j].get_receiver_str())
                    checker = 0;
                else checker = 1;
            }
        }
        if(checker == 1){
            tab->setRowCount(count);
            QStringList receiver = m_sent_messages[i].get_receiver_str().split("\n");
            set_row(tab, count - 1, receiver[0], receiver[1], receiver[2]);
            count++;
        }
    }
}

void User::tab_received_from(QTableWidget* tab){
    tab->clearContents();
    tab->setRowCount(0);
    int count = 1;
    for(int i = 0; i < m_received_messages.size(); ++i){
        bool checker = 1;
        for(int j = 0; j < i; ++j){
            if(i != 0){
                if(m_received_messages[i].get_sender_str() == m_received_messages[j].get_sender_str())
                    checker = 0;
                else checker = 1;
            }
        }
        if(checker == 1){
            tab->setRowCount(count);
            QStringList sender = m_received_messages[i].get_sender_str().split("\n");
            count++;
        }
    }
}

void User::sort_sent_msgs_size (bool order, QTableWidget *tab){
    if(order == ascending){
        std::sort(m_sent_messages.begin(), m_sent_messages.end());
    }
    else std::sort(m_sent_messages.rbegin(), m_sent_messages.rend());
    tab_sent(tab);
}

void User::sort_rece_msgs_size (bool order, QTableWidget *tab){
    if(order == ascending){
        std::sort(m_received_messages.begin(), m_received_messages.end());
    }
    else std::sort(m_received_messages.rbegin(), m_received_messages.rend());
    tab_received(tab);
}

void User::sort_sent_msgs_time(bool order, QTableWidget *tab){
    if(order == ascending){
        std::sort(m_sent_messages.begin(), m_sent_messages.end(), [](const Message& a, const Message& b){
            return a.get_qdatetime_sent() < b.get_qdatetime_sent();
        });
    }
    else std::sort(m_sent_messages.rbegin(), m_sent_messages.rend(), [](const Message& a, const Message& b){
        return a.get_qdatetime_sent() < b.get_qdatetime_sent();
    });
    tab_sent(tab);
}

void User::sort_rece_msgs_time(bool order, QTableWidget *tab){
    if(order == ascending){
        std::sort(m_received_messages.begin(), m_received_messages.end(), [](const Message& a, const Message& b){
            return a.get_qdatetime_sent() < b.get_qdatetime_sent();
        });
    }
    else std::sort(m_received_messages.rbegin(), m_received_messages.rend(), [](const Message& a, const Message& b){
        return a.get_qdatetime_sent() < b.get_qdatetime_sent();
    });
    tab_received(tab);
}

bool User::is_inactive(){
    return m_sent_messages.empty();
}

QString User::last_address(){
    return m_sent_messages[m_sent_messages.size() - 1].get_receiver_str();
}

void User::log_out(){
    this->m_email = "";
    this->m_name = "";
    this->m_place_of_registration = "";
    this->m_password = "";
    this->m_received_messages.clear();
    this->m_sent_messages.clear();
}

void User::edit(QString name, QString place){
    m_name = name;
    m_place_of_registration = place;
}

void User::set_draft(Message draft){
    m_draft = draft;
}

Message User::get_draft(){
    return m_draft;
}

void User::set_row(QTableWidget* tab, int row, QString item_col1, QString item_col2, QString item_col3){
    QTableWidgetItem* new_item1 = new QTableWidgetItem;
    QTableWidgetItem* new_item2 = new QTableWidgetItem;
    QTableWidgetItem* new_item3 = new QTableWidgetItem;
    new_item1->setText(item_col1);
    new_item2->setText(item_col2);
    new_item3->setText(item_col3);
    tab->setItem(row, 0, new_item1);
    tab->setItem(row, 1, new_item2);
    tab->setItem(row, 2, new_item3);
}
