#include "mail.h"
#include "QFile"
#include <QMessageBox>
#include "login_error.h"
#include "write_error.h"
#include "existinguser_error.h"

mail::mail()
{}

void mail::set_mail(){
    //get users from csv
    QFile file1("userstest.csv");
    if(file1.open(QFile::ReadOnly)){
        QTextStream in(&file1);
        QList< QStringList > lists;
        QString line;
        do{
            line = in.readLine();
            lists << line.split(";");
        }while(!line.isNull());
        for(int i = 0; i < lists.size() - 1; ++i){
            User new_user(lists[i][0], lists[i][1], lists[i][2], lists[i][3]);
            user.insert(new_user);
        }
    }
    file1.close();
    //get messages from csv
    QFile file2("messages.csv");
    if(file2.open(QFile::ReadOnly)){
        QTextStream in(&file2);
        QList< QStringList > lists;
        QString line;
        do{
            line = in.readLine();
            lists << line.split(";");
        }while(!line.isNull());
        for(int i = 0; i < lists.size() - 1; ++i){
            QDateTime time_sent = QDateTime::fromString(lists[i][3], time_format);
            QDateTime time_received = QDateTime::fromString(lists[i][4], time_format);
            Message new_message(lists[i][0], lists[i][1], lists[i][2], time_sent, time_received);
            messages.push_back(new_message);
        }
    }
    file2.close();
    //set sent and received messages for users
    for(int i = 0; i < messages.size(); ++i){
        User find_sender(messages[i].get_sender());
        User find_receiver(messages[i].get_receiver());
        User sender = *user.find(find_sender);
        User receiver = *user.find(find_receiver);
        user.erase(find_sender);
        user.erase(find_receiver);
        messages[i].set_sender(sender.get_email() + "\n" + sender.get_name() + "\n" + sender.get_place());
        messages[i].set_receiver(receiver.get_email() + "\n" + receiver.get_name() + "\n" + receiver.get_place());
        receiver.push_received_msg(messages[i]);
        sender.push_sent_msg(messages[i]);
        user.insert(sender);
        user.insert(receiver);
    }

    // set drafts
    QFile file3("drafts.csv");
    if(file3.open(QFile::ReadOnly)){
        QTextStream in(&file3);
        QList< QStringList > lists;
        QString line;
        do{
            line = in.readLine();
            lists << line.split(";");
        }while(!line.isNull());
        for(int i = 0; i < lists.size() - 1; ++i){
            User find_sender = *user.find(User(lists[i][0]));
            find_sender.set_draft(Message(lists[i][2], lists[i][1]));
            user.erase(find_sender);
            user.insert(find_sender);
        }
    } file3.close();
}

void mail::log_in(User login_user, QTableWidget* tab_received, QTableWidget* tab_sent, QLabel* lbl){
    if(user.find(login_user) != user.cend()){
        current_user = *user.find(login_user);
        if(current_user.get_password() != login_user.get_password()){
            current_user.log_out();
            throw login_error();
        }
        current_user.tab_sent(tab_sent);
        current_user.tab_received(tab_received);
        lbl->setText(current_user.get_name());
    }else throw login_error();
}

void mail::log_out(){
    current_user.log_out();
}

void mail::admin_log_in(QTableWidget* tab_users){
    tab_users->show();
    tab_users->setRowCount(user.size());
    int i = 0;
    for(auto it = user.begin(); it != user.end(); ++it){
        User i_user = *it;
        User::set_row(tab_users, i, i_user.get_name(), i_user.get_email(), i_user.get_place());
        ++i;
    }
}

void mail::sign_up(User new_user){
    if(user.find(new_user) == user.cend()){
        //add new user to set
        user.insert(new_user);
        //add new user to csv file
        QString filename = "users.csv";
        QFile file(filename);
        if (file.open(QFile::WriteOnly | QFile::Append)){
            QTextStream data( &file );
            QStringList strList;
            strList << new_user.get_name() + ";" + new_user.get_email() + ";" + new_user.get_place() + ";" + new_user.get_password();
            data << strList.join( ";" )+"\n";
        }
        file.close();
    }else throw existinguser_error();
}

void mail::write(Message msg, QTableWidget* tab_sent){
    if(user.find(User(msg.get_receiver())) != user.cend()){
        //new message
        QDateTime time_received = QDateTime::currentDateTime();
        Message new_message(msg.get_text(), current_user.get_email(), msg.get_receiver(), msg.get_qdatetime_sent(), time_received);
        messages.push_back(new_message);
        //add for sender and receiver
        User find_user(msg.get_receiver());
        User temp = *user.find(find_user);
        user.erase(find_user);
        user.erase(current_user);
        new_message.set_receiver(temp.get_email() + "\n" + temp.get_name() + "\n" + temp.get_place());
        new_message.set_sender(current_user.get_email() + "\n" + current_user.get_name() + "\n" + current_user.get_place());
        current_user.push_sent_msg(new_message);
        temp.push_received_msg(new_message);
        user.insert(temp);
        user.insert(current_user);
        //add to file
        QString filename = "messages.csv";
        QFile file(filename);
        if (file.open(QFile::WriteOnly | QFile::Append)){
            QTextStream data( &file );
            QStringList strList;
            strList << new_message.get_text() + ";" + new_message.get_sender() + ";" + new_message.get_receiver() + ";" + new_message.get_time_sent() + ";" + new_message.get_time_received();
            data << strList.join( ";" )+"\n";
        }
        file.close();
        // remove from drafts
        QFile file1("drafts.csv");
        if(file1.open(QFile::ReadWrite | QFile::Text)){
            QString new_file_contents;
            QTextStream in(&file1);
            while(!in.atEnd()){
                QStringList line = in.readLine().split(";");
                if(!(line[0] == current_user.get_email()))
                    new_file_contents.append(in.readLine() + "\n");
            }
            file1.resize(0);
            in << new_file_contents;
            file1.close();
        }
        current_user.set_draft(Message());
        //add to tab
        current_user.tab_sent(tab_sent);
    }else throw write_error();
}

void mail::filter(QString email_filter, QTableWidget* tab){
    if(email_filter == ""){
        current_user.tab_received(tab);
        tab->sortItems(2, Qt::DescendingOrder);
        return;
    }
    if(user.find(User(email_filter)) != user.cend()){
    current_user.tab_received_filter(tab, email_filter);
    tab->sortItems(2, Qt::DescendingOrder);
    }else throw write_error();
}

void mail::admin_search_inactive_users(QTableWidget* tab_users){
    int i = 0;
    for(auto it = user.begin(); it != user.end(); ++it){
        User i_user = *it;
        if(i_user.is_inactive()){
            tab_users->setRowCount(i + 1);
            User::set_row(tab_users, i, i_user.get_name(), i_user.get_email(), i_user.get_place());
            ++i;
        }
    }
}

void mail::admin_get_info_about_user(QString email, QString option, QTableWidget* tab_users, QTextBrowser* txt){
    if(user.find(User(email)) != user.cend()){
        User find_user = *user.find(User(email));
        if(option == "Sent to")
            find_user.tab_sent_to(tab_users);
        else if(option == "Received from")
            find_user.tab_received_from(tab_users);
        txt->setPlainText(find_user.last_address());
    }else throw write_error();
}

User mail::get_current_user(){
    return current_user;
}


void mail::edit_user(QString name, QString place){
    // edit current user
    QString old_name = current_user.get_name();
    QString old_place = current_user.get_place();
    current_user.edit(name, place);
    // edit file users
    QFile file("userstest.csv");
    QString file_contents;
    if(file.open(QFile::ReadOnly)){
        QTextStream in(&file);
        file_contents = in.readAll();
        file_contents.replace(old_name, name);
        file_contents.replace(old_place, place);
    }
    file.close();
    if(file.open(QFile::WriteOnly)){
        QTextStream in(&file);
        in << file_contents;
    }
    file.close();
    // reset mail
    reset_mail();
}

void mail::reset_mail(){
    user.clear();
    messages.clear();
    set_mail();
}

void mail::set_draft(Message draft){
    // current system
    current_user.set_draft(draft);
    user.erase(current_user);
    user.insert(current_user);
    // file
    QFile file("drafts.csv");
    if(file.open(QFile::ReadWrite | QFile::Text)){
        QString new_file_contents;
        QTextStream in(&file);
        while(!in.atEnd()){
            QStringList line = in.readLine().split(";");
            if(!(line[0] == current_user.get_email()))
                new_file_contents.append(line[0] + ";" + line[1] + ";" + line[2] + "\n");
        }
        file.resize(0);
        new_file_contents.append(current_user.get_email() + ";" + draft.get_receiver_str() + ";" + draft.get_text() + "\n");
        in << new_file_contents;
        file.close();
    }
}
