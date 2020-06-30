/*
 * Westfaelischer Hochschule Campus Bocholt
 * MikroControllerTechnik 1 Tutorium 
 * Fischertechnik - Robotics in Industry
 * Gerald Hebinck, Mai 2019
 * 
 * Diese Klasse dient zur Ansteuerung des Greif-Arm-Roboters mittels PWM.
 * Die Ansteuerung der einzelnen Achsen erfolgt Ã¼ber die Klasse clEncPWMDrive.
 * Die Referenzfahrt oeffnet zuerst das Werkzeug, hebt des dann an und dreht dann den Turm.
 */

#include "clEncPWMDrive.h"

class clRoboter {
  private:
    clEncPWMDrive rot;
    clEncPWMDrive lift;
    clEncPWMDrive pick;

  public:
    clRoboter(int pin[3][5], int limit[3][2], bool limits[3], volatile int* enc_val[3]);
    int drive_rot(int value, int scale);
    int drive_lift(int value, int scale);
    int drive_pick(int value, int scale);
    void refDrive();
};

//Was ist das hier ?
// Konstruktor mit default-Werten? Wieso dann so viele? ne sind nur 3
clRoboter::clRoboter(int pin[3][5], int limit[3][2], bool limits[3], volatile int* enc_val[3]) :  
                     rot (pin[0], limit[0], limits[0], enc_val[0]),
                     lift(pin[1], limit[1], limits[1], enc_val[1]),
                     pick(pin[2], limit[2], limits[2], enc_val[2]) 
                     {};

int clRoboter::drive_rot(int value, int scale) {
  return rot.directDrive(value, scale);
}
int clRoboter::drive_lift(int value, int scale) {
  return lift.directDrive(value, scale);
}
int clRoboter::drive_pick(int value, int scale) {
  return pick.directDrive(value, scale);
}

void clRoboter::refDrive() {
  pick.refDrive();
  pick.setInit();
  lift.refDrive();
  lift.setInit();
  rot.refDrive();
  rot.setInit();
}

