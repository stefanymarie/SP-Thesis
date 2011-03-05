#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "qapplication.h"
#include "dbconnect.h"

#include <QMainWindow>
#include <QFile>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QImage>
#include <QDateTime>
#include <QPainter>

using namespace cv;

class dbconnect;
namespace Ui {class mainWindow;}

class mainWindow : public QMainWindow {
    Q_OBJECT

	dbconnect *dbConnect;

signals:
	void fileOpened();
	void analyzing();

private slots:
	void showAbout();
	void dbOk();
	void disableButtons();

public slots:
	void openImage();
	void addToDB();
	void analyzeQuery();


public:
	explicit mainWindow(QWidget *parent = 0);
	~mainWindow();

	//variables initialization
	int count;
	bool dbSetupOk;
	Mat image, gray, edge, cedge;
	QByteArray queryFileBytes;
	QSize queryImageSize;
	QString currentFile, queryImageFile;

	//functions initialization
	void connectDB();
	void onTrackbar(int, int);
	void edgeDetection(QString);
	void connectToClass(QByteArray, QSize);

private:
	Ui::mainWindow *ui;
	void setupConnections();
	QImage*  IplImage2QImage(IplImage *iplImg);
	IplImage* QImage2IplImage(QImage *qimg);

};

#endif // MAINWINDOW_H


