/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Feb 5 00:12:21 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainWindow
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionAnalyze;
    QAction *actionAbout;
    QAction *actionContents;
    QAction *actionDBconnect;
    QWidget *centralWidget;
    QFrame *line;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QLabel *boxImageQuery;
    QPushButton *buttonAnalyze;
    QLabel *imageQuery_2;
    QGroupBox *groupBox;
    QPushButton *buttonAddToDB;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QMenu *menuTools;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *mainWindow)
    {
        if (mainWindow->objectName().isEmpty())
            mainWindow->setObjectName(QString::fromUtf8("mainWindow"));
        mainWindow->resize(800, 500);
        mainWindow->setMinimumSize(QSize(800, 500));
        mainWindow->setMaximumSize(QSize(800, 500));
        actionOpen = new QAction(mainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionExit = new QAction(mainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionAnalyze = new QAction(mainWindow);
        actionAnalyze->setObjectName(QString::fromUtf8("actionAnalyze"));
        actionAbout = new QAction(mainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionContents = new QAction(mainWindow);
        actionContents->setObjectName(QString::fromUtf8("actionContents"));
        actionDBconnect = new QAction(mainWindow);
        actionDBconnect->setObjectName(QString::fromUtf8("actionDBconnect"));
        centralWidget = new QWidget(mainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(250, 10, 16, 431));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(280, 30, 491, 241));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 489, 239));
        scrollArea->setWidget(scrollAreaWidgetContents);
        boxImageQuery = new QLabel(centralWidget);
        boxImageQuery->setObjectName(QString::fromUtf8("boxImageQuery"));
        boxImageQuery->setGeometry(QRect(30, 40, 200, 150));
        boxImageQuery->setMaximumSize(QSize(200, 150));
        boxImageQuery->setFrameShape(QFrame::StyledPanel);
        boxImageQuery->setLineWidth(2);
        buttonAnalyze = new QPushButton(centralWidget);
        buttonAnalyze->setObjectName(QString::fromUtf8("buttonAnalyze"));
        buttonAnalyze->setGeometry(QRect(50, 250, 161, 31));
        imageQuery_2 = new QLabel(centralWidget);
        imageQuery_2->setObjectName(QString::fromUtf8("imageQuery_2"));
        imageQuery_2->setGeometry(QRect(280, 290, 200, 150));
        imageQuery_2->setMaximumSize(QSize(200, 150));
        imageQuery_2->setFrameShape(QFrame::StyledPanel);
        imageQuery_2->setLineWidth(2);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(500, 330, 271, 111));
        buttonAddToDB = new QPushButton(centralWidget);
        buttonAddToDB->setObjectName(QString::fromUtf8("buttonAddToDB"));
        buttonAddToDB->setGeometry(QRect(50, 210, 161, 31));
        mainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(mainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        mainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(mainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        mainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionContents);
        menuTools->addAction(actionDBconnect);

        retranslateUi(mainWindow);

        QMetaObject::connectSlotsByName(mainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *mainWindow)
    {
        mainWindow->setWindowTitle(QApplication::translate("mainWindow", "mainWindow", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("mainWindow", "Open", 0, QApplication::UnicodeUTF8));
        actionOpen->setShortcut(QApplication::translate("mainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("mainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionExit->setShortcut(QApplication::translate("mainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionAnalyze->setText(QApplication::translate("mainWindow", "Analyze", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("mainWindow", "About", 0, QApplication::UnicodeUTF8));
        actionContents->setText(QApplication::translate("mainWindow", "Contents", 0, QApplication::UnicodeUTF8));
        actionContents->setShortcut(QApplication::translate("mainWindow", "F1", 0, QApplication::UnicodeUTF8));
        actionDBconnect->setText(QApplication::translate("mainWindow", "Connect to Database", 0, QApplication::UnicodeUTF8));
        boxImageQuery->setText(QString());
        buttonAnalyze->setText(QApplication::translate("mainWindow", "Analyze", 0, QApplication::UnicodeUTF8));
        imageQuery_2->setText(QString());
        groupBox->setTitle(QApplication::translate("mainWindow", "Details", 0, QApplication::UnicodeUTF8));
        buttonAddToDB->setText(QApplication::translate("mainWindow", "Add Image to Database", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("mainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("mainWindow", "Help", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("mainWindow", "Tools", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mainWindow: public Ui_mainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
