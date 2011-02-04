#include "dbconnect.h"
#include "ui_dbconnect.h"
#include "QtGui"

#define DB_DRIVER   "QMYSQL"

dbconnect::dbconnect(QWidget *parent):QDialog(parent),ui(new Ui::dbconnect){
    ui->setupUi(this);
    ui->textPassword->setEchoMode(QLineEdit::Password);
    connect(ui->boxConfirm, SIGNAL(accepted()),this, SLOT(setupdbConnections()));   //if the user clicked ok
}

dbconnect::~dbconnect(){delete ui;}

bool dbconnect::insertImageToDB(QByteArray queryBytes){

    QSqlQuery query;
    query.prepare("INSERT INTO images(img) VALUES (:img)");
    query.bindValue(":img", QVariant(queryBytes));
    bool ok = query.exec();

    return ok;

}

void dbconnect::setupdbConnections(){

    bool ok = false;
    if (QSqlDatabase::isDriverAvailable(DB_DRIVER)) {
        QString dbName = ui->textDatabase->displayText();
        QString dbHost = ui->textHost->displayText();
        QString dbUser = ui->textUsername->displayText();
        QString dbPass = ui->textPassword->displayText();
        db = QSqlDatabase::addDatabase(DB_DRIVER);
        db.setDatabaseName(dbName);
        db.setHostName(dbHost);
        db.setUserName(dbUser);
        db.setPassword(dbPass);
        ok = db.open();
    }

    if (ok) emit connected();
}
