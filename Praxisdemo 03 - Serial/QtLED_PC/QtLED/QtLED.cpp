// QtLED.cpp
//----------------------------------
#include "QtLED.h"

QtLED::QtLED(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	serial.setPortName("COM3");
	serial.open(QIODevice::ReadWrite);
	serial.setBaudRate(QSerialPort::Baud9600);
	serial.setDataBits(QSerialPort::Data8);
	serial.setParity(QSerialPort::NoParity);
	serial.setStopBits(QSerialPort::OneStop);
	serial.setFlowControl(QSerialPort::NoFlowControl);
	while (!serial.isOpen()) serial.open(QIODevice::ReadWrite);
	/*if (serial.isOpen() && serial.isWritable()){
		qDebug()<<"Serial is open";
	}*/

	//--- Create bntEin --
	btnEin = new QPushButton(this);
	btnEin->setGeometry(10, 10, 100, 100);
	btnEin->setText("LED ein");
	connect(btnEin, SIGNAL(clicked()), this, SLOT(btnEinSlotFkt()));
}

void QtLED::btnEinSlotFkt() {
	static bool einschaltbar = true;
	QByteArray output;

	if (einschaltbar) {
		output = "#1e"; //Einschaltcode
		btnEin->setText("LED aus");
		einschaltbar = false;
	}
	else 
	{
		output = "#1a"; //Ausschaltcode
		btnEin->setText("LED ein");
		einschaltbar = true;
	}

	serial.write(output);
	serial.flush();
}