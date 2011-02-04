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

void dbconnect::insertImageToDB(QFile imageFile){


    QMessageBox::warning(this, tr("Open Image .."), "Invalid Image Format!");
    //QString sql = QString("CREATE TABLE images (image BLOB)");
    QSqlQuery q(db);
    bool ok;

    imageFile.open(QIODevice::ReadOnly);
    QByteArray bytes = imageFile.readAll();

    q.prepare("INSERT INTO images (img) VALUES(:img)");
    q.bindValue(":img", QVariant(bytes));
    ok = q.exec();

    if (ok) QMessageBox(this);

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
