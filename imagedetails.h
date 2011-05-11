#ifndef IMAGEDETAILS_H
#define IMAGEDETAILS_H

#include <QDialog>
#include "edgedetection.h"

class edgeDetection;

namespace Ui {class imageDetails;}

class imageDetails : public QDialog{
    Q_OBJECT

   edgeDetection *edged;

private slots:
   void writeDetails();

public:
    explicit imageDetails(QWidget *parent = 0);
    ~imageDetails();

private:
    Ui::imageDetails *ui;
};

#endif // IMAGEDETAILS_H
