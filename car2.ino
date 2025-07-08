#include <SoftwareSerial.h>
#include <ZumoMotors.h>  // Library to control the motors 
 
SoftwareSerial XBee(2, 3); // RX = 2, TX = 3, recieving and transmitting pins 
ZumoMotors motors; 
 
String currentCommand = "S"; // Start in stop state
 
void setup() {

  Serial.begin(9600);
  XBee.begin(9600);

}
 
void loop() {

  // Check for an incoming command
  if (XBee.available()) {
    String incoming = "";
    
    while (XBee.available()) {

      char c = XBee.read();
      if (c == '\n') break; 
      incoming += c; 

    }

    if (incoming.length() > 0) {
      currentCommand = incoming; 
      Serial.print("Recieved: ");
      Serial.println(currentCommand);
    }

  }

 
  // Executing the current command for movement
  if (currentCommand == "F")       motors.setSpeeds(150, 150); //going forward
  else if (currentCommand == "B")  motors.setSpeeds(-150, -150); //backward
  else if (currentCommand == "L")  motors.setSpeeds(-150, 150); //left
  else if (currentCommand == "R")  motors.setSpeeds(150, -150); //right
  else if (currentCommand == "FR") motors.setSpeeds(150, 100); //curve right
  else if (currentCommand == "FL") motors.setSpeeds(100, 150); //curve left 
  else if (currentCommand == "BR") motors.setSpeeds(-150, -100); //back right  
  else if (currentCommand == "BL") motors.setSpeeds(-100, -150); //back left 
  else if (currentCommand == "S")  motors.setSpeeds(0, 0); //stop 
  else motors.setSpeeds(0, 0); //default stop 
 
  delay(20); // smoothener 
  
}
 