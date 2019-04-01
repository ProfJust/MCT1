// QtLED.h
//----------------------------------
#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtLED.h"
#include <QPushButton>
#include <QSerialPort>//#include <QDebug>

class QtLED : public QMainWindow
{
	Q_OBJECT

public:
	QtLED(QWidget *parent = Q_NULLPTR);

	QSerialPort serial;
private:
	Ui::QtLEDClass ui;
	QPushButton *btnEin;
	private slots:
	void btnEinSlotFkt();
};
