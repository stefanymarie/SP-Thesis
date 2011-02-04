#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtGui"

#include "dbconnect.h"

#include <stdio.h>

mainWindow::mainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::mainWindow){ ui->setupUi(this); setupConnections(); }

mainWindow::~mainWindow(){ delete ui;}

void mainWindow::setupConnections(){

    dbSetupOk = false;

    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openImage()));
    connect(ui->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->actionDBconnect, SIGNAL(triggered()), this, SLOT(connectDB()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
    //connect(ui->actionContents, SIGNAL(triggered()), this, SLOT(showHelp()));
}

void mainWindow::connectDB(){

    //initialize member class dbconnect
    QDialog *dbForm = new dbconnect(this);
    dbForm->setWindowModality(Qt::ApplicationModal);
    dbForm->setVisible(true);

    printf ("connectDB() here");

    //set db connection status connected if database set is open
    connect(dbForm, SIGNAL(connected()), this, SLOT(dbOk()));
    return;
}

void mainWindow::dbOk(){
    dbSetupOk = true;
    printf("dbOk() ");
    return;
}

void mainWindow::addToDB(){

    if (!dbSetupOk) connectDB();
    else {
        printf("addToDB");
        connectToClass(queryFileBytes);
    }

}

void mainWindow::connectToClass(QByteArray bytes){

    printf("connectToClass()");
    bool ok = dbConnect->insertImageToDB(bytes);
    if (ok) QMessageBox::warning(this, tr("Open Image .."), "Image added, check it out!");
}

void mainWindow::openImage(){

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(), tr("Image File ( *.png *.bmp *.jpeg *.jpg)"));

    QFile queryFile(fileName);
    queryFile.open(QIODevice::ReadOnly);
    queryFileBytes = queryFile.readAll();

    if (!fileName.isEmpty()) {
        QImage query(fileName);
        if (query.isNull()) {
            QMessageBox::warning(this, tr("Open Image .."), "Invalid Image Format!");
            return;
        }

        query = query.scaled(ui->boxImageQuery->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        ui->boxImageQuery->setPixmap(QPixmap::fromImage(query));
        connect(ui->buttonAddToDB, SIGNAL(clicked()), this, SLOT(addToDB()));
    }
}


void mainWindow::showAbout(){

    QMessageBox::about(this,("About"), "This is for my SP! Let's do this. Wohoo d:");
}

