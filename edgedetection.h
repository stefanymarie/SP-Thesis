#ifndef EDGEDETECTION_H
#define EDGEDETECTION_H

// opencv libraries
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv/cxcore.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

// qt creator
#include <QMainWindow>
#include <QtGui>
#include <QFile>

// c++ general lib
#include <iostream>
#include <vector>
#include <cmath>

using namespace cv;

class imageDetails;
namespace Ui {class edgeDetection;}

class edgeDetection : public QMainWindow{
   Q_OBJECT

private slots:
   void openImage();
   void analyzeQuery();
   void saveImage();
   void showAbout();

public:
    explicit edgeDetection(QWidget *parent = 0);
    ~edgeDetection();

    QString currentFile;
    void modifyFile(QString f, QString m, bool append=true);

private:
    Ui::edgeDetection *ui;

    // find match frame
    void setupConnections();
    Mat preprocess(Mat a, int e);
    void prepareFolder();
    void shapeUp(Mat a, vector<Mat>* s);
    Mat boundRect(Mat a);
    QList<QPair<float, int> > findMatch(vector<Mat>& s);
    QStringList retrieveShapes(int i, QString f);
    float computeSimilarity(Mat r, Mat t);
    Mat resizeImage(int _size, Mat _a);
    int takeGreater(int a, int b);
    float getEccentricity(Mat a);
    float getAngle(Mat a);
    Mat rotateImage(Mat a, float _a);
    void normalize(Mat a, vector<Mat>* norms);
    float compareShapes(Mat a, Mat b);
    Mat binarize(Mat a);
    QString getDetails(int x);

    // save image frame
    void addDetails();
    void storeContours(vector<Mat>& s);

    // variables
    QString buildPath;
    QString _imgCount;
    int imgCount;


    // open-source *copy-paste*
    // reference: http://umanga.wordpress.com/
    // 04-19-2010 post, accessed: 02-12-2011
    QImage*  IplImage2QImage(IplImage *iplImg);
    IplImage* QImage2IplImage(QImage *qimg);

};

#endif // EDGEDETECTION_H
