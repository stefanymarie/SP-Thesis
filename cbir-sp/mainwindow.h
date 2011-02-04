#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>

class dbconnect;
namespace Ui {class mainWindow;}

class mainWindow : public QMainWindow {
    Q_OBJECT

    dbconnect *dbConnect;

signals:
    void imageFileOpened(QByteArray file);

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
    bool dbSetupOk;
    QByteArray queryFileBytes;
    void connectToClass(QByteArray);

private:
    Ui::mainWindow *ui;

};

#endif // MAINWINDOW_H


