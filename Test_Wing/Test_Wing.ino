#include <ESP32Servo.h>
#include <Ps3Controller.h>

Servo lwing;
Servo rwing;

#define lwing_pin 12
#define rwing_pin 27

const int deadzone = 20;  
const int minAngle = 0;   
const int maxAngle = 180;  
int currentAngle = 90;     
bool increasing = true;

unsigned long lastUpdate = 0;
const unsigned long flapSpeed = 20; 

void setup() {
  Serial.begin(115200);
  lwing.attach(lwing_pin);
  rwing.attach(rwing_pin);
  lwing.write(45);
  rwing.write(45);
  Ps3.begin("40:f5:20:45:10:f6");
  Serial.println("Waiting for PS3 Controller...");
}

void loop() {
  if (Ps3.isConnected()) { 
    int lx = Ps3.data.analog.stick.lx;
    int ly = Ps3.data.analog.stick.ly;
    unsigned long currentMillis = millis();

    if (currentMillis - lastUpdate >= flapSpeed) {
      lastUpdate = currentMillis;

      if (increasing) {
        currentAngle += 2;
        if (currentAngle >= maxAngle) {
          increasing = false; // reverse at the top
        }
      } else {
        currentAngle -= 2;
        if (currentAngle <= minAngle) {
          increasing = true; // reverse at the bottom
        }
      }

      if (ly < -deadzone) {
        lwing.write(currentAngle);
        rwing.write(currentAngle);
      } 

      else if (lx < -deadzone) {
        lwing.write(currentAngle);
        rwing.write(currentAngle);
      } 

      else if (lx > deadzone) {
        lwing.write(90); 
        rwing.write(90);
      } 
      else {
        lwing.write(90);
        rwing.write(90);
      }
    }
  }
}
