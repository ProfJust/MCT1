// QtLED.h
//----------------------------------
#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtLED.h"
#include <QPushButton>
#include <QSerialPort>
#include <QTimer>
#include <QDebug>
#include <QLabel>
#include <QPainter>
#include <QPainterPath>
#include <QSpinBox>
#include <QString>
#include <QStringList>



class QtLED : public QMainWindow
{
	Q_OBJECT

public:
	QtLED(QWidget *parent = Q_NULLPTR);

	QSerialPort serial;
	QTimer *myTimer;
		
	//Variablen für Rectangle-Bar
	int x;
	int y;
	int size_x;
	int size_y;

	struct RectangleBar {
		int x; //X-Koordinate
		int y; //Y-Koordinate
		int size_x; //Länge in X-Richtung
		int size_y; //Länge in Y-Richtung
		QString einheit;
		int minimalwert;
		int maximalwert;

	};
	RectangleBar rb;
	RectangleBar rb_cm;
	QLabel *beschr_sensorwert;
	QLabel *anzeige_sensorwert;
	QLabel *beschr_cm;
	QLabel *anzeige_cm;
	QSpinBox* COMportNr;
	QLabel* COMlbl;
	QPushButton* pb_setComNr;
	

private:
	Ui::QtLEDClass ui;
		
	void QtLED::paintEvent(QPaintEvent *e);
	void QtLED::drawRect(int x, int y, int size_x, int size_y);
	void QtLED::drawRectBar(RectangleBar rb);

	private slots:
	void myTimerSlot();
	void COMportInit();
};


