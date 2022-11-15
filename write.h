// This class is used to implement an additional
// window for creating message
#ifndef WRITE_H
#define WRITE_H

#include <QDialog>
#include "message.h"

namespace Ui {
class write;
}

class write : public QDialog
{
    Q_OBJECT

public:
    explicit write(QWidget *parent = nullptr);
    ~write();

    void set_draft(QString text, QString receiver);
private:
    Ui::write *ui;

signals:
    void signal_write(Message msg);
    void signal_draft(Message draft);
private slots:
    void on_btn_send_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // WRITE_H
