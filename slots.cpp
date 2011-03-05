#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "QtGui"

#include "dbconnect.h"

#include <iostream>

//let the user open a query image
void mainWindow::openImage(){

	count=0;
	currentFile = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(), tr("Image File ( *.png *.bmp *.jpeg *.jpg)"));

	if (!currentFile.isEmpty()) {
		//data needed for the database
		QFile queryFile(currentFile);
		queryFile.open(QIODevice::ReadOnly);
		queryFileBytes = queryFile.readAll();

		//conversion needed for showing image
		QImage query(currentFile);
		if (query.isNull()) {
			QMessageBox::warning(this, tr("Open Image .."), "Invalid Image Format!");
			return;
		}

		//get size of the image added
		queryImageSize = query.size();

		//clear the QLabel before adding showing another image
		ui->boxImageQuery->clear();

		//in showing the image, keep the aspect ration for elegance.
		query = query.scaled(ui->boxImageQuery->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
		ui->boxImageQuery->setAlignment(Qt::AlignCenter);
		ui->boxImageQuery->setPixmap(QPixmap::fromImage(query));

		//connect signal and slot
		connect(ui->buttonAddToDB, SIGNAL(clicked()), this, SLOT(addToDB()));
		connect(ui->buttonAnalyze, SIGNAL(clicked()), this, SLOT(analyzeQuery()));
		queryImageFile = currentFile;
		emit analyzing();

	}
}

//sets accessibility of database to ok (true)
void mainWindow::dbOk(){
		dbSetupOk = true;
		return;
}

//attempt to add the image to the database
void mainWindow::addToDB(){

		if (!dbSetupOk) connectDB();
		else	connectToClass(queryFileBytes, queryImageSize);
}

void mainWindow::disableButtons(){

	ui->buttonAddToDB->blockSignals(true);
	ui->buttonAnalyze->blockSignals(true);
	//ui->buttonAddToDB->disconnect(this,0);
	//ui->buttonAnalyze->disconnect(this,0);
}

void mainWindow::showAbout(){

	QMessageBox::warning(this, tr("About"), "My SP/THESIS na SUPER DUPER ang kalisod.");

}
