#include <ESP32Servo.h>
#include <Ps3Controller.h>

Servo testServo; 

int degreesToTest[] = {0, 90, 180, 90, 0}; 
int numDegrees = sizeof(degreesToTest) / sizeof(degreesToTest[0]); 

void setup() {
  testServo.attach(12); 
  Serial.begin(115200); 
  testServo.write(0);
  Ps3.begin("40:f5:20:45:10:f6"); 
  Serial.println("Waiting for PS3 Controller...");
}

void loop() {
  if (Ps3.isConnected()) {
    if(Ps3.event.button_down.cross) {
      for (int i = 0; i < numDegrees; i++) {
        int currentDegree = degreesToTest[i];
        testServo.write(currentDegree); 
        Serial.print("Moving servo to: ");
        Serial.print(currentDegree);
        Serial.println(" degrees");
        delay(1000); 
      }
      delay(2000); 
    }
  }
}