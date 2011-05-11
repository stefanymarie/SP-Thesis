
#define MATCHPERCENTAGE	80

#include "edgedetection.h"
#include "ui_edgedetection.h"
#include "imagedetails.h"

#include "qtopencv.cpp"

using namespace std;
using namespace cv;

// constructor the edgeDetection class
edgeDetection::edgeDetection(QWidget *parent):QMainWindow(parent),
ui(new Ui::edgeDetection){ui->setupUi(this); setupConnections();}

// deconstructor of edgeDetection class
edgeDetection::~edgeDetection(){ delete ui;}

// initiliaze connection: signal & slots of buttons and menus
void edgeDetection::setupConnections(){

	connect(ui->actionOpen, SIGNAL(triggered()),
			  this, SLOT(openImage()));
	connect(ui->buttonAnalyze, SIGNAL(clicked()),
			  this, SLOT(analyzeQuery()));
	connect(ui->actionExit, SIGNAL(triggered()),
			  qApp, SLOT(quit()));
	connect(ui->actionAbout, SIGNAL(triggered()),
			  this, SLOT(showAbout()));
}

// upload image; show uploaded image
void edgeDetection::openImage(){

	currentFile = currentFile.null;
	currentFile = QFileDialog::getOpenFileName
					  (this,
						tr("Open File"),
						QDir::currentPath(),
						tr("Image File ( *.png *.bmp *.jpeg *.jpg)"));

	if (!currentFile.isEmpty()){
		QImage query(currentFile);
		if (query.isNull()){
			QMessageBox::warning(this,
										tr("Open Image .."),
										"Invalid Image Format!");
			return;
		}

		//UI:: clear box; scale image; show query image
		QLabel *bQ = ui->boxQuery;
		bQ->clear();
		bQ->setPixmap(QPixmap::fromImage(query.scaled
													(bQ->size(),
													 Qt::KeepAspectRatio,
													 Qt::SmoothTransformation)));

		connect(ui->buttonSaveImg, SIGNAL(clicked()),
				  this, SLOT(saveImage()));
	}
}

/******************************************************************/
/* FIND MATCH FRAME
/******************************************************************/


// analyze the query image >> "Find Match" button slot
void edgeDetection::analyzeQuery(){

	// match results (i.e. similar images or duplicates or query
	QListWidget *listMatches = ui->boxResult;
	listMatches->clear();

	if (!currentFile.isNull()){
		QString _queryFile = currentFile;
		const char* queryFile = _queryFile.toLocal8Bit().constData();

		// preprocess the query image
		Mat img_gray = imread(queryFile, 0);
		Mat queryEdged = preprocess(img_gray, 80);
		prepareFolder();

		// find contours of edged image;
		vector<Mat> shapes;
		shapeUp(queryEdged, &shapes);

		// find duplicates or similar images
		QList<QPair<float, int> > foundMatches = findMatch(shapes);
		qSort(foundMatches.begin(),
				foundMatches.end(),
				qGreater<QPair<float,int> >());

		QString filePath = buildPath;
		filePath.append("/images");

		QPair<float, int> currPair;
		QString currMatch;
		QPixmap thumbnail;
		QIcon icon;
		int idx = 0;

		while(idx < foundMatches.count()){
			currPair = foundMatches.at(idx);
			currMatch = QString("%1/%2.jpg")
							.arg(filePath)
							.arg(QString::number(currPair.second));

			QFileInfo f(currMatch);
			QString fname = f.baseName();
			thumbnail = QPixmap(currMatch).scaled
							(listMatches->iconSize(),
							 Qt::IgnoreAspectRatio,
							 Qt::SmoothTransformation);
			icon = QIcon(thumbnail);

			bool ok;
			int imageId = fname.toInt(&ok, 10);
			QString details = getDetails(imageId);
			QString sPercentage;
			sPercentage.sprintf("%.2f", currPair.first);
			details.append(QString("Percentage: %1\%\n")
								.arg(sPercentage));
			listMatches->addItem(new QListWidgetItem
										(icon, details, listMatches));
			idx++;
		} // exits when all matches are displayed
	} // else, no query image file uploaded
}

// preprocess the query image: desaturation, blur, canny edge
Mat edgeDetection::preprocess(Mat img, int edgeThresh){

	Mat img_blur;
	Mat img_edge;

	// canny edge algorithm threshold set to 80
	GaussianBlur(img, img_blur, Size(1,1),0, 0, 0);
	Canny(img_blur, img_edge, edgeThresh, edgeThresh*3, 3);

	return img_edge;
}

// prepare the directories
// and file folders where images will be saved
void edgeDetection::prepareFolder(){

	buildPath = QDir::currentPath();
	QString b = buildPath;
	QDir buildDir(b);

	if (!buildDir.exists("images")) buildDir.mkdir("images");
	if (!buildDir.exists("temps")) buildDir.mkdir("temps");

	QString imgList = QString("%1/imgList.txt").arg(buildPath);
	if (!buildDir.exists("imgList.txt")){
		QFile _t(imgList);
		_t.open(QIODevice::WriteOnly);
		QTextStream init(&_t);
		init << "0\n";
		_t.close();
	}

	QFile countList(imgList);
	countList.open(QIODevice::ReadOnly);
	QTextStream in(&countList);
	_imgCount = in.readLine();
	countList.close();
	bool ok;
	imgCount = _imgCount.toInt(&ok, 10);
}

// get the contours of edged image
void edgeDetection::shapeUp(Mat _a, vector<Mat>* s){

	Mat a = resizeImage(128, _a);
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	findContours(a, contours, hierarchy,
					 CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	int idx = 0;
	int aNz = countNonZero(a);
	float criteria = aNz * 0.25;

	Mat b = Mat::zeros(a.rows, a.cols, CV_8UC1);
	Mat bTemp = Mat::zeros(a.rows, a.cols, CV_8UC1);
	Mat adjusted;

	while(idx >= 0){
		adjusted = adjusted.zeros(a.rows, a.cols, CV_8UC1);
		b = b.zeros(b.rows, b.cols, CV_8UC1);
		bTemp = bTemp.zeros(b.rows, b.cols, CV_8UC1);
		drawContours(bTemp, contours, idx, Scalar(255,0,0),
						 CV_FILLED, 8, hierarchy, 0);

		if ((float)countNonZero(bTemp) > criteria){
			drawContours(b, contours, idx, Scalar(255,0,0),
							 3, 8, hierarchy, 0);
			adjusted = boundRect(b);
			s->push_back(adjusted);
		}

		idx = hierarchy[idx][0];
	}
}

// adjust the "region of interest";
// crop the matrix up to the bounding pixels in all 4 sides
Mat edgeDetection::boundRect(Mat q){

	Mat _a = q;
	IplImage* z = new IplImage(_a);
	QImage* zPtr = IplImage2QImage(z);
	QImage a = *zPtr;

	Range row, col;

	row.start = a.height();
	row.end = 0;
	col.start = a.width();
	col.end = 0;

	// seek for the colrange and rowrange
	int x, y;
	for (y = 0; y < a.height(); y++)
		for (x = 0; x < a.width(); x++)
			if (qRed(a.pixel(x,y)) != 0){
				if (y < row.start) row.start = y;
				if (y > row.end) row.end = y;
				if (x < col.start) col.start = x;
				if (x > col.end) col.end = x;
			}

	// convert QImage a to IplImage
	IplImage* _temp = QImage2IplImage(&a);
	Mat aMat(_temp);

	Mat roi = Mat::zeros(q.rows, q.cols, CV_8UC1);
	roi = aMat.operator ()(row, col);

	Mat roi_gray;
	cvtColor(roi, roi_gray, CV_BGR2GRAY);
	roi_gray.convertTo(roi_gray, CV_8UC1);

	return roi_gray;
}

// find images that match with the query image
QList<QPair<float, int> > edgeDetection::findMatch(vector<Mat>& s){

	// get texxt file that contains reference
	// to contours/shapes of saved images
	QString imgRefPath = buildPath;
	imgRefPath.append("/temps/imgReference.txt");

	QList<float> pers;
	float perC = 0;
	int idx = 0, idr = 0;

	for(; idx < (int)s.size(); idx++){
		idr = 0;
		while (idr < imgCount){
			QStringList imgTemps = retrieveShapes(idr++, imgRefPath);
			float per = 0;
			const char* _tempPath;
			int ii = 1;

			for (; ii < imgTemps.size(); ii++){
				_tempPath = imgTemps.at(ii).toLocal8Bit().constData();
				Mat temp = imread(_tempPath, 0);
				per += computeSimilarity(temp, s[idx]);
			}

			per = per/(ii-1);
			perC = per;
			pers << per;

			if (idx > 0){
				float prevPer = pers.at(idr-1);
				prevPer += perC;
				pers.replace(idr-1, prevPer);
			}else{
				pers.replace(idr-1,perC);
			}
		}
	}

	QList<QPair<float, int> > foundMatches;
	int p = 0;
	float pX = 0;

	while(p < imgCount){
		pX = pers.at(p);
		pX = pX/idx;
		if (pX > (float)MATCHPERCENTAGE)
			 foundMatches.append(qMakePair(pX,p));
		p++;
	}
	return foundMatches;
}

// get the contoured images of image stored in library
QStringList edgeDetection::retrieveShapes(int i, QString f){

	QFile referenceTxt(f);
	referenceTxt.open(QIODevice::ReadOnly);

	QStringList temps;
	QTextStream find(&referenceTxt);
	QString _i = QString::number(i);
	QString d = QString("+");
	QString t;

	do t = find.readLine(0);
	while(t != _i);

	t = find.readLine(0);
	while (t != d){
		temps << t;
		t = find.readLine(0);
	}

	return temps;
}

// compute the percentage of similarity between 2 images
float edgeDetection::computeSimilarity(Mat _r, Mat _t){

	// r = reference shape
	// t = template/query shape

	Mat r = resizeImage(128, _r);
	float rEccentricity = getEccentricity(r);

	Mat t = resizeImage(128, _t);
	float tEccentricity = getEccentricity(t);

	float temp = 0, percentage = 0;
	// if r's eccentricity & t's ecccentricity > 0.5, do not proceed
	if (abs(rEccentricity - tEccentricity) > 0.5) return 0;
	else{

		float rAngle = getAngle(r);
		Mat r_rot = rotateImage(r, rAngle);

		// normalize the template, 4sets
		vector<Mat> tNorms;
		normalize(t, &tNorms);

		int id = 0;
		while (id < (int)tNorms.size()){
			temp = compareShapes(r_rot, tNorms[id]);
			if (temp > percentage) percentage = temp;
			id++;
		}
	}

	return percentage;
}

// resize the image to specified length, (_size X _size)
Mat edgeDetection::resizeImage(int _size, Mat _a){

	int height = _a.size().height;
	int width = _a.size().width;
	int nHeight, nWidth;

	int size = takeGreater(height, width);
	nHeight = size - (height%size);
	nWidth = size - (width%size);

	if (nHeight == size) nHeight = 0;
	if (nWidth == size) nWidth = 0;


	Mat aTemp = Mat::zeros(500, 500, CV_8UC1);
	copyMakeBorder(_a, aTemp,
						0, nHeight,
						0, nWidth,
						0, BORDER_CONSTANT);

	Mat a = Mat::zeros(_size, _size, CV_8UC1);
	cv::resize(aTemp, a, Size(_size, _size), 1, 1, CV_INTER_AREA);

	return a;
}

// returns the greater value
int edgeDetection::takeGreater(int a, int b){
	if(a > b) return a;
	else return b;
}

// get the eccentricity of the shape
float edgeDetection::getEccentricity(Mat a){

	Moments m = moments(a, true);

	float b = (m.mu20 + m.mu02);
	float c = (m.mu20 - m.mu02);
	float d = (m.mu11);
	float e = ((c*c) - (4*(d*d)))/(b*b);

	return e;
}

// get the tilt angle of shape
float edgeDetection::getAngle(Mat a){

	Moments m = moments(a, true);

	float c = (m.mu20 - m.mu02);
	float d = 0;

	if ((c == 0 && d == 0) || (c > 0 && d == 0)) d = 0;
	else if (c == 0 && d > 0) d = 45;
	else if (c == 0 && d < 0) d = -45;
	else if (c < 0 && d == 0) d = -90;
	else if (c > 0 && c > 0) d = 0.5 * (atan(d/c));
	else if (c > 0 && c < 0) d = 0.5 * (atan(d/c));
	else if (c < 0 && c > 0) d = (0.5 * (atan(d/c))) + 90;
	else if (c < 0 && c < 0) d = (0.5 * (atan(d/c))) - 90;

	return d;
}

// rotate the shape to the specified angle
// with respect to the x-axis
Mat edgeDetection::rotateImage(Mat t, float _angle){

	Mat tClone;
	int border = takeGreater(tClone.size().width,
									 tClone.size().height)/4;
	copyMakeBorder(t, tClone,
						border, border, border, border,
						0, BORDER_CONSTANT);

	Point2f t_center(tClone.cols/2.0F, tClone.rows/2.0F);
	double angle = (double)_angle;

	Mat rot_mat, flipped;
	rot_mat = getRotationMatrix2D(t_center, angle, 1.0);
	warpAffine(tClone, flipped, rot_mat, tClone.size());

	return flipped;
}

// function for rotation normalization
// returns 4sets of translation of shape, upright, 2flips, 180deg
void edgeDetection::normalize(Mat a, vector<Mat>* norms){
	float angle = getAngle(a);
	Mat rot = rotateImage(a, angle);
	norms->push_back(rot);

	for(int flipCode = -1; flipCode <= 1; flipCode++){
		Mat flipped;
		flip(rot, flipped, flipCode);
		norms->push_back(flipped);
	}
}

// compares 2 shapes and return similarity measure
float edgeDetection::compareShapes(Mat r, Mat t){

	Mat rRect = boundRect(r);
	Mat tRect = boundRect(t);

	Mat _rClone = resizeImage(128, rRect);
	Mat _tClone = resizeImage(128, tRect);

	Mat rClone = binarize(_rClone);
	Mat tClone = binarize(_tClone);

	Mat xored;
	bitwise_xor(rClone, tClone, xored);

	int rNz = countNonZero(rClone);
	int tNz = countNonZero(tClone);
	int xNz = countNonZero(xored);

	float p = ((float)xNz/(rNz+tNz))*100;
	return 100 - p;
}

// returns binary representation of shape
Mat edgeDetection::binarize(Mat a){

	Scalar mean, stddev;
	meanStdDev(a, mean, stddev);
	Mat b = Mat::zeros(a.rows, a.cols, CV_8UC1);
	threshold(a, b, stddev.val[0], 1, CV_THRESH_BINARY_INV);

	return b;
}

// get details about the image from reference txt file
QString edgeDetection::getDetails(int x){

	QString imageListPath = QString("%1/imageList.txt")
									.arg(buildPath);
	QFile imageList(imageListPath);
	imageList.open(QIODevice::ReadOnly);

	QTextStream find(&imageList);
	QString d = QString("+");
	QString t;

	int id = -1;

	do{
		t = find.readLine(0);
		if (t == d) id++;
	}while(id < x);

	t = find.readLine(0);
	QString name = find.readLine(0);
	QString size = find.readLine(0);
	QString loct = find.readLine(0);
	QString desc = find.readLine(0);

	QString m;
	m.append(QString("Name: %1\n").arg(name));
	m.append(QString("Size: %1\n").arg(size));
	m.append(QString("Location: %1\n").arg(loct));
	m.append(QString("Description: %1\n").arg(desc));

	imageList.close();

	return m;
}

/******************************************************************/
/* SAVE IMAGE FRAME
/******************************************************************/

// save the image to the library
void edgeDetection::saveImage(){

	prepareFolder();
	QString from = currentFile;
	addDetails();

	const char* queryFile = from.toLocal8Bit().constData();
	Mat img_gray = imread(queryFile, 0);
	Mat queryEdged = preprocess(img_gray, 80);
	vector<Mat> shapes;
	shapeUp(queryEdged, &shapes);
	storeContours(shapes);

	QString to = QString("%1/images/%2.jpg")
					 .arg(buildPath)
					 .arg(_imgCount);
	QImage image(from);
	image.save(to, "JPG");
	imgCount++;

	QString imgList = QString("%1/imgList.txt").arg(buildPath);
	modifyFile(imgList, QString::number(imgCount), false);

	disconnect(ui->buttonSaveImg,0,0,0);
}

// pop-up dialog box for image details
void edgeDetection::addDetails(){

	QDialog *dialogForDetails = new imageDetails(this);
	dialogForDetails->setWindowModality(Qt::ApplicationModal);
	dialogForDetails->show();
}

// store the contours (images) of the images in library
void edgeDetection::storeContours(vector<Mat>& s){

	QString b = buildPath;
	QString tempPath = b.append("/temps");
	QDir tempDir(tempPath);
	int idx = 0;

	QString tempRefer = QString("%1/imgReference.txt")
							  .arg(tempPath);

	if (!tempDir.exists("imgReference.txt")){
		QFile _t(tempRefer);
		_t.open(QIODevice::WriteOnly);
		QTextStream init(&_t);
		init << "0\n";
		_t.close();
	}

	QString _tempFile;
	QString referTxt = "\r\n";
	const char* tempFile;

	for(; idx < s.size(); idx++){
		_tempFile = QString("%1/shapeFor_%2_%3.jpg")
					  .arg(tempPath)
					  .arg(_imgCount)
					  .arg(QString::number(idx));

		tempFile = _tempFile.toLocal8Bit().constData();
		imwrite(tempFile,s[idx]);
		referTxt.append(_tempFile);
		referTxt.append("\r\n");
	}

	referTxt.append("+\r\n");
	referTxt.append(QString::number(imgCount+1));
	modifyFile(tempRefer, referTxt);
}

// edit a txt file
void edgeDetection::modifyFile(QString f, QString m, bool append){

	QFile fileToModify(f);
	fileToModify.open(QIODevice::ReadWrite);

	if (!append){
		QTextStream text(&fileToModify);
		text << m;
		fileToModify.close();
	}else{
		QTextStream text(&fileToModify);
		QString allText = text.readAll();
		fileToModify.close();
		fileToModify.open(QIODevice::WriteOnly);
		QTextStream nText(&fileToModify);
		nText << allText << m << endl;
		fileToModify.close();
	}
	fileToModify.close();
}

/******************************************************************/
/* HELP (?) FRAME
/******************************************************************/

// what this project is about
void edgeDetection::showAbout(){

	QMessageBox::about(this, "CBIR-SP",
							 "This is my thesis.\n"
							 "I am working with Prof. Jerry Salvador"
							 " and Prof. Sandra Mae Famador.\n\n\n"
							 "-stefanymarie-");
}

