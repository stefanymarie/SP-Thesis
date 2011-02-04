#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>

class dbconnect;
namespace Ui {class mainWindow;}

class mainWindow : public QMainWindow {
    Q_OBJECT

    dbconnect *dbConnect;

private slots:
    void setupConnections();
    void dbOk();

public slots:
    void openImage();
    void connectDB();
    void addToDB();
    void showAbout();


public:
    explicit mainWindow(QWidget *parent = 0);
    ~mainWindow();
    QFile queryImage;
    bool dbSetupOk;

private:
    Ui::mainWindow *ui;

};

#endif // MAINWINDOW_H
