//****************************************************************/
/* Mikrocontrollertechnik MCT1                                   */
/*                                                                */
/*****************************************************************/
/* E-Blocks                                                      */
// Combo-Board EB083 an A0-A7 und D0-D7
/*****************************************************************/
/* Datum:  18.02.2018                                            */
/* Autor:  Olaf Just                                             */
/* µC:     Arduino Mega auf EB092                                */
/*****************************************************************/
#include "clLED.h"
clLED LED1(A2);
clLED LED2(A3);

void setup() {
  LED1.off();
  LED2.on();
}

void loop() {
  LED1.toggle();
  LED2.toggle();
  delay(200);
  LED2.toggle();
  delay(200);
}
