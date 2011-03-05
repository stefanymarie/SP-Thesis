#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "QtGui"

#include "dbconnect.h"
#include "qtopencv.cpp"
#include "slots.cpp"

#include <iostream>

using namespace cv;
using namespace std;

mainWindow::mainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::mainWindow){ ui->setupUi(this); setupConnections(); }

mainWindow::~mainWindow(){ delete ui;}

//GUI: connect ui to corresponding functions
void mainWindow::setupConnections(){

	dbSetupOk = false;

	//menuBar connections
	connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openImage()));
	connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
	connect(ui->actionDBconnect, SIGNAL(triggered()), this, SLOT(addToDB()));
	connect(ui->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));

}


/********************************************************************************
DATABASE RELATED FUNCTIONS
********************************************************************************/

//connect to database, a dialog form will appear to guide the user
void mainWindow::connectDB(){

    //initialize member class dbconnect
    QDialog *dbForm = new dbconnect(this);
    dbForm->setWindowModality(Qt::ApplicationModal);
    dbForm->setVisible(true);

    //set db connection status connected if database set is open
    connect(dbForm, SIGNAL(connected()), this, SLOT(dbOk()));
    return;
}

//adds the image to the database, table: images
void mainWindow::connectToClass(QByteArray bytes, QSize size){

    bool ok = dbConnect->insertImageToDB(bytes,size);
    if (ok) QMessageBox::warning(this, tr("Open Image .."), "Image added, check it out!");
}


/********************************************************************************
FEATURE EXTRACTION FUNCTIONS
********************************************************************************/


void mainWindow::analyzeQuery(){

	//connect(this, SIGNAL(analyzing()), this, SLOT(disableButtons()));
	//connect(this, SIGNAL(analyzing()), this, SLOT(disableButtons()));
	edgeDetection(currentFile);
}

void mainWindow::edgeDetection(QString file){

	int edgeThresh = 30;
	string filename = file.toLocal8Bit().constData();
	image = imread(filename, 1);
	cedge.create(image.size(), image.type());
	cvtColor(image, gray, CV_BGR2GRAY);

	blur(gray, edge, Size(3,3));

	// fixed edgeThreshold at 30/100
	Canny(edge, edge, edgeThresh, edgeThresh*3, 3);
	cedge = Scalar::all(0);

	image.copyTo(cedge, edge);
	//imshow("Edge map", cedge);
	IplImage* cedgeImg = new IplImage(cedge);

	QImage* cedgePtr = IplImage2QImage(cedgeImg);
	QImage cedgeQ = *cedgePtr;
	cedgeQ = cedgeQ.scaled(ui->boxImageResult->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
	ui->boxImageResult->setAlignment(Qt::AlignCenter);
	ui->boxImageResult->setPixmap(QPixmap::fromImage(cedgeQ));

}
