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
	while (!serial.isOpen()) 
		serial.open(QIODevice::ReadWrite);

	// ---- Create Rectangle-Bar ------------------
	this->setFixedWidth(1100);
	this->setFixedHeight(1000);
	
	//--- Create Labels für Sensor-Values
	beschr_sensorwert = new QLabel(this);
	beschr_sensorwert->setText("Sensorwert:");
	beschr_sensorwert->setGeometry(50, 10, 200, 100);
	anzeige_sensorwert = new QLabel(this);
	anzeige_sensorwert->setGeometry(60, 120, 200, 100);
	beschr_cm = new QLabel(this);
	beschr_cm->setText("Cm:");
	beschr_cm->setGeometry(325, 10, 200, 100);
	anzeige_cm = new QLabel(this);
	anzeige_cm->setGeometry(330, 120, 400, 100);

	//--- Set Fonts for Labels
	QFont font_sensorwert = anzeige_sensorwert->font();
	font_sensorwert.setPointSize(40);
	anzeige_sensorwert->setFont(font_sensorwert);

	QFont font_label1 = beschr_sensorwert->font();
	font_label1.setPointSize(15);
	beschr_sensorwert->setFont(font_label1);

	QFont font_cm = anzeige_cm->font();
	font_cm.setPointSize(40);
	anzeige_cm->setFont(font_sensorwert);

	QFont font_label2 = beschr_cm->font();
	font_label2.setPointSize(15);
	beschr_cm->setFont(font_label2);

	// Rectangle-Values for Initializing Struct RectangleBar

	// Daten für Balkenanzeige der Sensorwerte
	rb.x = 50;
	rb.y = 300;
	rb.size_x = 100;
	rb.size_y = 100;
	rb.einheit = "Sensor-Value";
	rb.minimalwert = 0;
	rb.maximalwert = 1023;


	// Daten für Balkenanzeige der cm-Werte
	rb_cm.x = 50;
	rb_cm.y = 500;
	rb_cm.size_x = 100;
	rb_cm.size_y = 100;
	rb_cm.einheit = "Cm:";
	rb_cm.minimalwert = 0;
	rb_cm.maximalwert = 157;


	//--- Create Timer --
	myTimer = new QTimer(this);
	connect(myTimer, SIGNAL(timeout()), this, SLOT(myTimerSlot()),Qt::UniqueConnection);
	myTimer->setInterval(200);
	myTimer->start();
	qDebug() << "Jetzt geht es los!";
}

void QtLED::myTimerSlot() {
	// vom Arduino kommt z.B. der String
	// sensor = 1011 output [cm] = 6
	//---------------------------------
	//Leeres Byte Array zum speichern des empfangenen Strings
	QByteArray input="                                         "; 
	
	//--- cm lesen --
	if (serial.canReadLine()) {  //Zeile lesbar?
		input = serial.readAll(); // In QBytearray speichern
	    // C-String vorbereiten
		char *str = new char[input.size() + 1];
		strcpy(str, input.data()); //Zeichen aus input in str einkopieren

    //--- Sensorwert lesen -----
		int sensorWert;
		// [9] ist das Zeichen nach "sensor = "
		int numbOfScan_sens = sscanf(&str[9], "%04d", &sensorWert);
	//--- cm Wert lesen ---
		int cmWert;
		// Suchen nach dem Buchstaben m im String und dann bei Index 5 hinzuaddieren --> Startindex für cm-Wert
		int index;
		const char *ptr = strchr(str, 'm');
		if (ptr) {
			index = ptr - str + 5;
		}
		int numbOfScan_cm = sscanf(&str[index], "%04d", &cmWert);

		//--- GUI-Anzeigen aktualisieren ----
		if (numbOfScan_sens == 1){
			anzeige_sensorwert->setText(QString("%1").arg(sensorWert));
			rb.size_x = sensorWert*0.9;  //Faktor, damit es in das Fenster passt
			this->repaint();
		}
		if (numbOfScan_cm == 1){
			anzeige_cm->setText(QString("%1").arg(cmWert));
			rb_cm.size_x = cmWert * 6 - 20; //Faktor und Verschiebung, damit es in das Fenster passt
			this->repaint();
		}
	}	
	else {
		qDebug() << "ERROR: Nichts empfangen";
	}
}
void QtLED::paintEvent(QPaintEvent *e)
{
	//Balken für Sensorwert
	drawRectBar(rb);

	//Balken für Cm-Wert
	drawRectBar(rb_cm);
}

void QtLED::drawRect(int x, int y, int size_x, int size_y)
{
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing);
	QPainterPath path1;
	path1.addRect(QRectF(x, y, size_x, size_y));
	p.fillPath(path1, Qt::darkGreen);
	p.drawPath(path1);
}

void QtLED::drawRectBar(RectangleBar rb)
{
	//Beschriftungen
	QLabel *einheit = new QLabel(this);
	einheit->setText(rb.einheit);
	einheit->setGeometry(rb.x, rb.y - 70, 200, 100);
	QFont font_label3 = einheit->font();
	font_label3.setPointSize(10);
	einheit->setFont(font_label3);
	einheit->show();

	QLabel *min = new QLabel(this);
	min->setText(QString("%1").arg(rb.minimalwert));
	min->setGeometry(rb.x - 5, rb.y + 70, 200, 100);
	QFont font_label4 = min->font();
	font_label4.setPointSize(10);
	min->setFont(font_label4);
	min->show();

	QLabel *max = new QLabel(this);
	max->setText(QString("%1").arg(rb.maximalwert));
	max->setGeometry(rb.x + 900, rb.y + 70, 200, 100);
	QFont font_label5 = max->font();
	font_label5.setPointSize(10);
	max->setFont(font_label5);
	max->show();

	//Balken zeichnen
	drawRect(rb.x, rb.y, rb.size_x, rb.size_y);
}
