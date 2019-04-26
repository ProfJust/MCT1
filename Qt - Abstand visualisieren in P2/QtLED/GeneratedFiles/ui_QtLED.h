/********************************************************************************
** Form generated from reading UI file 'QtLED.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTLED_H
#define UI_QTLED_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtLEDClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtLEDClass)
    {
        if (QtLEDClass->objectName().isEmpty())
            QtLEDClass->setObjectName(QStringLiteral("QtLEDClass"));
        QtLEDClass->resize(600, 400);
        menuBar = new QMenuBar(QtLEDClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        QtLEDClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtLEDClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtLEDClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QtLEDClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QtLEDClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtLEDClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtLEDClass->setStatusBar(statusBar);

        retranslateUi(QtLEDClass);

        QMetaObject::connectSlotsByName(QtLEDClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtLEDClass)
    {
        QtLEDClass->setWindowTitle(QApplication::translate("QtLEDClass", "QtLED", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtLEDClass: public Ui_QtLEDClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTLED_H
