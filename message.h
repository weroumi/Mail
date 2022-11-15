// This class is used to store and manage data of one message
#ifndef MESSAGE_H
#define MESSAGE_H
#include <QString>
#include <QDateTime>
#include <vector>

class Message
{
    int m_size;
    QString m_text;
    QString m_sender;   //email\nname\nplace of registration
    QString m_receiver; //email\nname\nplace of registration
    QDateTime m_time_sent;
    QDateTime m_time_received;
public:
    Message();

    Message(QString text, QString sender, QString receiver, QDateTime time_sent, QDateTime time_received);

    Message(QString text, QString receiver, QDateTime time_sent);

    Message(QString text, QString receiver);

    Message(const Message& other);

    ~Message();

    bool operator<(const Message& other) const;

    Message operator=(const Message& other);

    QString get_sender();

    QString get_receiver();

    QString get_sender_str();

    QString get_receiver_str();

    QString get_text();

    QString get_time_sent();

    QDateTime get_qdatetime_sent() const;

    QString get_time_received();

    void set_sender(QString name);

    void set_receiver(QString name);
};

#endif // MESSAGE_H
