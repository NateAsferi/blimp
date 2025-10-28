#define lwing1_pin 12
const int deadzone = 20;  
const int minAngle = 0;   
const int maxAngle = 30;  
int currentAngle = 15;     
bool increasing = true;

unsigned long lastUpdate = 0;
const unsigned long flapSpeed = 5; 

void setup() {
  Serial.begin(115200);
  lwing.attach(lwing_pin);
  lwing.write(15);
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
      } 

      else if (lx < -deadzone) {
        lwing.write(currentAngle);
      } 

      else if (lx > deadzone) {
        lwing.write(15); 
      } 
      else {
        lwing.write(15);
      }
  }
}
