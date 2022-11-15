#include "message.h"
#include "custom_exception.h"
#include "emptyfield_error.h"

Message::Message()
{
    this->m_size = 0;
    this->m_receiver = "";
    this->m_sender = "";
    this->m_text = "";
}

Message::Message(QString text, QString sender, QString receiver, QDateTime time_sent, QDateTime time_received) :
    m_size(text.size()),
    m_text(text),
    m_sender(sender),
    m_receiver(receiver),
    m_time_sent(time_sent),
    m_time_received(time_received)
{
    if(text.contains("\n")){
        newline_error ex;
        throw ex;
    }
}

Message::Message(QString text, QString receiver, QDateTime time_sent){
    if(text.contains("\n") || text.contains(";"))
        throw newline_error();
    if(text.isEmpty() || receiver.isEmpty())
        throw emptyfield_error();
    m_size = text.size();
    m_text = text;
    m_receiver = receiver;
    m_time_sent = time_sent;
}

Message::Message(const Message& other){
    this->m_receiver = other.m_receiver;
    this->m_sender = other.m_sender;
    this->m_size = other.m_size;
    this->m_text = other.m_text;
    this->m_time_received = other.m_time_received;
    this->m_time_sent = other.m_time_sent;
}

Message::Message(QString text, QString receiver){
    if(text.contains("\n") || text.contains(";"))
        throw newline_error();
    m_text = text;
    m_receiver = receiver;
}

Message::~Message(){}

bool Message::operator<(const Message& other) const{
    return this->m_size < other.m_size;
}

Message Message::operator=(const Message& other){
    if(this != &other){
        this->m_receiver = other.m_receiver;
        this->m_sender = other.m_sender;
        this->m_size = other.m_size;
        this->m_text = other.m_text;
        this->m_time_received = other.m_time_received;
        this->m_time_sent = other.m_time_sent;
    }
    return *this;
}

QString Message::get_sender(){
    QStringList list = m_sender.split("\n");
    return list[0];
}

QString Message::get_receiver(){
    QStringList list = m_receiver.split("\n");
    return list[0];
}

QString Message::get_sender_str(){
    return m_sender;
}

QString Message::get_receiver_str(){
    return m_receiver;
}

QString Message::get_text(){
    return m_text;
}

QString Message::get_time_sent(){
    return m_time_sent.toString("dd.MM.yyyy hh:mm:ss");
}

QDateTime Message::get_qdatetime_sent() const{
    return m_time_sent;
}

QString Message::get_time_received(){
    return m_time_received.toString("dd.MM.yyyy hh:mm:ss");
}

void Message::set_sender(QString name){
    m_sender = name;
}

void Message::set_receiver(QString name){
    m_receiver = name;
}





