#include "imagedetails.h"
#include "ui_imagedetails.h"

#include "QtGui"

// constructor of imageDetails class
imageDetails::imageDetails(QWidget *parent):QDialog(parent),
ui(new Ui::imageDetails){

   ui->setupUi(this);
   connect(ui->boxConfirm, SIGNAL(accepted()),
           this, SLOT(writeDetails()));
}

// deconstructor of imageDetails class
imageDetails::~imageDetails(){delete ui;}

// write details of image in reference txt file
void imageDetails::writeDetails(){

   QString builder = QDir::currentPath();
   QDir builderDir = QDir(builder);

	QString imageList = QString("%1/imageList.txt").arg(builder);
	if (!builderDir.exists("imageList.txt")){
		QFile _t(imageList);
		_t.open(QIODevice::WriteOnly);
		QTextStream init(&_t);
		init << "+\n";
		_t.close();
	}

	QString details = "\r\n";
	details.append(ui->lineName->text());
	details.append("\r\n");
	details.append(ui->lineSize->text());
	details.append("\r\n");
	details.append(ui->lineLoct->text());
	details.append("\r\n");
	details.append(ui->lineDesc->text());
	details.append("\r\n+");

	edged->modifyFile(imageList, details);
}

