#include <Wire.h>
#include <ADXL345.h>
#define PRIMARY_CLICK 12
#define SECONDARY_CLICK 13

// Switch to Serial.Print for debugging purposes
#define SERIAL_FUNCTION Serial.write

ADXL345 adxl;

void setup() {
  // put your setup code here, to run once:
  pinMode(PRIMARY_CLICK, INPUT);
  pinMode(SECONDARY_CLICK, INPUT);
  Serial.begin(9600);
  adxl.powerOn();

  //set activity/ inactivity thresholds (0-255)
  adxl.setActivityThreshold(75); //62.5mg per increment§
  adxl.setInactivityThreshold(75); //62.5mg per increment
  adxl.setTimeInactivity(10); // how many seconds of no activity is inactive?

  //look of activity movement on this axes - 1 == on; 0 == off
  adxl.setActivityX(1);
  adxl.setActivityY(1);
  adxl.setActivityZ(1);

  //look of inactivity movement on this axes - 1 == on; 0 == off
  adxl.setInactivityX(1);
  adxl.setInactivityY(1);
  adxl.setInactivityZ(1);
}

int roll = 0.00, pitch = 0.00; //Roll & Pitch are the angles which rotate by the axis X and y 
int x, y, z;
bool prim_clicked, sec_clicked;
bool p_prim_clicked = 0, p_sec_clicked = 0;

void loop() {
  adxl.readXYZ(&x, &y, &z);

  double x_Buff = float(x);
  double y_Buff = float(y);  
  double z_Buff = float(z);
  roll = atan2(y_Buff , z_Buff) * 57.3;
  pitch = atan2((-x_Buff), sqrt(y_Buff * y_Buff + z_Buff * z_Buff)) * 57.3;

  prim_clicked = digitalRead(PRIMARY_CLICK);
  
  if (prim_clicked != p_prim_clicked && p_prim_clicked == 1) {
    SERIAL_FUNCTION(1);
  } else {
    SERIAL_FUNCTION(0);
  }

  sec_clicked = digitalRead(SECONDARY_CLICK);
  if (sec_clicked != p_sec_clicked && p_sec_clicked == 1) {
    SERIAL_FUNCTION(1);
  } else {
    SERIAL_FUNCTION(0);
  }

  p_prim_clicked = prim_clicked;
  p_sec_clicked = sec_clicked;
  
  SERIAL_FUNCTION(highByte(roll));
  SERIAL_FUNCTION(lowByte(roll));
  SERIAL_FUNCTION(highByte(pitch));
  SERIAL_FUNCTION(lowByte(pitch));
  SERIAL_FUNCTION('\n');
  delay(1);
}
