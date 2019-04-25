
//MCT1_Kap08_sw04_ExampleScheduler.ino
/** 
 *  TaskScheduler Test
 *
 *  Initially only tasks 1 and 2 are enabled
 *  Task1 runs every 2 seconds 10 times and then stops
 *  Task2 runs every 3 seconds indefinitely
 *  Task1 enables Task3 at its first run
 *  Task3 run every 5 seconds
 *  Task1 disables Task3 on its last iteration and changed Task2 to run every 1/2 seconds
 *  At the end Task2 is the only task running every 1/2 seconds
 */
 
 
#include <TaskScheduler.h>

// Callback methods prototypes
void t1Callback();
void t2Callback();
void t3Callback();

//Tasks
Task t4();
Task t1(2000, 10, &t1Callback);
Task t2(3000, TASK_FOREVER, &t2Callback);
Task t3(5000, TASK_FOREVER, &t3Callback);

Scheduler myScheduler;


void t1Callback() {
    Serial.print("t1: ");
    Serial.println(millis());

    //t3 wird bei der ersten Ausführung von t1 gestartet
    if (t1.isFirstIteration()) {
      myScheduler.addTask(t3);
      t3.enable();
      Serial.println("t1: enabled t3 and added to the chain");
    }
    //t3 wird bei der letzten Ausführung von t1 gestoppt
    if (t1.isLastIteration()) {
      t3.disable();
      myScheduler.deleteTask(t3);
      t2.setInterval(500);
      Serial.println("t1: disable t3 and delete it from the chain. t2 interval set to 500");
    }
}

void t2Callback() {
    Serial.print("t2: ");
    Serial.println(millis());
  
}

void t3Callback() {
    Serial.print("t3: ");
    Serial.println(millis());
  
}

void setup () {
  Serial.begin(115200);
  Serial.println("Scheduler TEST");
  
  myScheduler.init();
  Serial.println("Initialized scheduler");
  
  myScheduler.addTask(t1);
  Serial.println("added t1");
  
  myScheduler.addTask(t2);
  Serial.println("added t2");

  delay(5000);
  
  t1.enable();
  Serial.println("Enabled t1");
  t2.enable();
  Serial.println("Enabled t2");
}


void loop () {
  myScheduler.execute();
}
