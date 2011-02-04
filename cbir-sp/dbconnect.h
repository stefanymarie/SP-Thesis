#ifndef DBCONNECT_H
#define DBCONNECT_H

#include <QDialog>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {class dbconnect;}

class dbconnect : public QDialog {
    Q_OBJECT

signals:
    void connected();

public slots:
    void setupdbConnections();
    void insertImageToDB(QFile imageFile);

public:
    explicit dbconnect(QWidget *parent = 0);
    ~dbconnect();
    QSqlDatabase db;


private:
    Ui::dbconnect *ui;
};

#endif // DBCONNECT_H