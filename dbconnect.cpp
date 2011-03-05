#include "dbconnect.h"
#include "ui_dbconnect.h"
#include "QtGui"
#include <QtDebug>

#define DB_DRIVER   "QMYSQL"

dbconnect::dbconnect(QWidget *parent):QDialog(parent),ui(new Ui::dbconnect){
    ui->setupUi(this);
    ui->textPassword->setEchoMode(QLineEdit::Password);

    //if the user clicked ok in the dbForm
    connect(ui->boxConfirm, SIGNAL(accepted()),this, SLOT(setupdbConnections()));
}

dbconnect::~dbconnect(){delete ui;}

bool dbconnect::insertImageToDB(QByteArray queryBytes, QSize querySize){

    QSqlQuery query;
    query.prepare("INSERT INTO images(img, height, width) VALUES (:img, :height, :width)");
    query.bindValue(":img", QVariant(queryBytes));
    query.bindValue(":height", querySize.height());
    query.bindValue(":width", querySize.width());
    bool ok = query.exec();
    return ok;

}

void dbconnect::setupdbConnections(){

    bool ok = false;
    if (QSqlDatabase::isDriverAvailable(DB_DRIVER)) {
        //QString dbName = ui->textDatabase->displayText();
        //QString dbHost = ui->textHost->displayText();
        //QString dbUser = ui->textUsername->displayText();
        //QString dbPass = ui->textPassword->displayText();
        db = QSqlDatabase::addDatabase(DB_DRIVER);
        //db.setDatabaseName(dbName);
        //db.setHostName(dbHost);
        //db.setUserName(dbUser);
        //db.setPassword(dbPass);
        db.setDatabaseName("sp");
        db.setHostName("127.0.0.1");
        db.setUserName("root");
        db.setPassword("root");
        ok = db.open();

    }
	else {
		db = QSqlDatabase::addDatabase("QMYSQL");
		db.lastError();
	}
    if (ok) emit connected();
}
