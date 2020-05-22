// State Machine Ampel.cpp : 
#include "stdafx.h"
#include <stdio.h>
#include <windows.h>

void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

char  state = 0;  // globale Variable für den Zustand

//---- Die Zustände ----
#define ROT 0
#define ROT_GELB 1
#define GRUEN 2
#define GELB 3

//---- Schriftfarben für die Konsole ---
#define DOS_ROT 12
#define DOS_GELB 14
#define DOS_GRUEN 10
#define DOS_GREY 8

void setFontColor(int colorNr) {
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bgcolor * 16 + fgcolor);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + colorNr);
}
				  //------------ Der Zustandsautomat ---------------------
void nextState()
{
	switch (state) {
	case ROT: //#0 in der Grafik
		setFontColor(DOS_ROT);
		printf("\n Rot              ");   //Treiber Simulation
		printf("\n  \xFE");
		setFontColor(DOS_GREY);
		printf("\n  \xFE");
		printf("\n  \xFE");
		state = ROT_GELB;
		break;
	case ROT_GELB: //#1 in der Grafik
		setFontColor(DOS_ROT);
		printf("\n Rot");
		setFontColor(DOS_GELB); 
		printf("_Gelb        ");
		setFontColor(DOS_ROT);
		printf("\n  \xFE");
		setFontColor(DOS_GELB);
		printf("\n  \xFE");
		setFontColor(DOS_GREY);
		printf("\n  \xFE");
		state = GRUEN;
		break;
	case GRUEN: //#2 in der Grafik
		setFontColor(DOS_GRUEN);
		printf("\n Gruen           ");
		setFontColor(DOS_GREY);
		printf("\n  \xFE");
		printf("\n  \xFE");
		setFontColor(DOS_GRUEN);
		printf("\n  \xFE");
		state = GELB;
		break;
	case GELB: //#3 in der Grafik
		setFontColor(DOS_GELB);
		printf("\n Gelb             ");
		setFontColor(DOS_GREY);
		printf("\n  \xFE");
		setFontColor(DOS_GELB);
		printf("\n  \xFE");
		state = ROT;
		setFontColor(DOS_GREY);
		printf("\n  \xFE");
		break;
	default:
		setFontColor(DOS_ROT);
		printf("\n Fehlerzustand !");
		state = ROT;
		break;
	}
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int main(void)
{
	printf("Ampel-Automat");

	while (1) {
		Sleep(2000);  //´Warten  = Takt /CLk
		gotoxy(3, 2);
		nextState();        //In den nächsten Zustand springen
	}
	return 0;
}


