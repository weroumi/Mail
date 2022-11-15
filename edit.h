#ifndef EDIT_H
#define EDIT_H

#include "user.h"
#include <QDialog>

namespace Ui {
class edit;
}

class edit : public QDialog
{
    Q_OBJECT

public:
    explicit edit(QWidget *parent = nullptr);
    ~edit();

    void set(User current);

signals:
    void signal_edit(QString name, QString place);

private slots:
    void on_btn_save_clicked();

private:
    Ui::edit *ui;
};

#endif // EDIT_H
