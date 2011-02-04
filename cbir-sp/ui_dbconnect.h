/********************************************************************************
** Form generated from reading UI file 'dbconnect.ui'
**
** Created: Sat Feb 5 00:12:21 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DBCONNECT_H
#define UI_DBCONNECT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_dbconnect
{
public:
    QDialogButtonBox *boxConfirm;
    QLabel *labelDatabase;
    QLineEdit *textDatabase;
    QLabel *labelHost;
    QLineEdit *textHost;
    QLineEdit *textUsername;
    QLabel *labelUsername;
    QLabel *labelPassword;
    QLineEdit *textPassword;

    void setupUi(QDialog *dbconnect)
    {
        if (dbconnect->objectName().isEmpty())
            dbconnect->setObjectName(QString::fromUtf8("dbconnect"));
        dbconnect->setWindowModality(Qt::ApplicationModal);
        dbconnect->resize(338, 258);
        dbconnect->setMinimumSize(QSize(338, 258));
        dbconnect->setMaximumSize(QSize(338, 258));
        dbconnect->setAutoFillBackground(false);
        dbconnect->setSizeGripEnabled(false);
        dbconnect->setModal(true);
        boxConfirm = new QDialogButtonBox(dbconnect);
        boxConfirm->setObjectName(QString::fromUtf8("boxConfirm"));
        boxConfirm->setGeometry(QRect(0, 200, 301, 32));
        boxConfirm->setOrientation(Qt::Horizontal);
        boxConfirm->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        labelDatabase = new QLabel(dbconnect);
        labelDatabase->setObjectName(QString::fromUtf8("labelDatabase"));
        labelDatabase->setGeometry(QRect(30, 30, 91, 16));
        textDatabase = new QLineEdit(dbconnect);
        textDatabase->setObjectName(QString::fromUtf8("textDatabase"));
        textDatabase->setGeometry(QRect(120, 30, 181, 21));
        labelHost = new QLabel(dbconnect);
        labelHost->setObjectName(QString::fromUtf8("labelHost"));
        labelHost->setGeometry(QRect(30, 70, 91, 16));
        textHost = new QLineEdit(dbconnect);
        textHost->setObjectName(QString::fromUtf8("textHost"));
        textHost->setGeometry(QRect(120, 70, 181, 21));
        textUsername = new QLineEdit(dbconnect);
        textUsername->setObjectName(QString::fromUtf8("textUsername"));
        textUsername->setGeometry(QRect(120, 110, 181, 21));
        labelUsername = new QLabel(dbconnect);
        labelUsername->setObjectName(QString::fromUtf8("labelUsername"));
        labelUsername->setGeometry(QRect(30, 110, 91, 16));
        labelPassword = new QLabel(dbconnect);
        labelPassword->setObjectName(QString::fromUtf8("labelPassword"));
        labelPassword->setGeometry(QRect(30, 150, 91, 16));
        textPassword = new QLineEdit(dbconnect);
        textPassword->setObjectName(QString::fromUtf8("textPassword"));
        textPassword->setGeometry(QRect(120, 150, 181, 21));

        retranslateUi(dbconnect);
        QObject::connect(boxConfirm, SIGNAL(accepted()), dbconnect, SLOT(accept()));
        QObject::connect(boxConfirm, SIGNAL(rejected()), dbconnect, SLOT(reject()));

        QMetaObject::connectSlotsByName(dbconnect);
    } // setupUi

    void retranslateUi(QDialog *dbconnect)
    {
        dbconnect->setWindowTitle(QApplication::translate("dbconnect", "Dialog", 0, QApplication::UnicodeUTF8));
        labelDatabase->setText(QApplication::translate("dbconnect", "Database:", 0, QApplication::UnicodeUTF8));
        labelHost->setText(QApplication::translate("dbconnect", "Host:", 0, QApplication::UnicodeUTF8));
        labelUsername->setText(QApplication::translate("dbconnect", "Username:", 0, QApplication::UnicodeUTF8));
        labelPassword->setText(QApplication::translate("dbconnect", "Password:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class dbconnect: public Ui_dbconnect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DBCONNECT_H
