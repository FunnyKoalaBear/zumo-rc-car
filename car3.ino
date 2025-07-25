#include <SoftwareSerial.h>
#include <ZumoMotors.h> // Library to control the motors 
 
SoftwareSerial XBee(2, 3); // RX = 2, TX = 3, recieving and transmitting pin
ZumoMotors motors; //initialises motor object
 
String input = ""; // Start in empty state
 
void setup() {
  XBee.begin(9600);
  Serial.begin(9600);
}
 
void loop() {
  // Checks for an incoming command
  if (XBee.available()) {
    char c = XBee.read();

    if (c == '\n') { //Checks for ending character on incoming command
      processCommand(input); //Function call after entire command is parsed 
      input = "";
    } else {
      input += c;
    }
  }
}

//the movement function  
void processCommand(String message) {

  //Storing index of the | seperator chracters in recieving message 
  //Ex recieving message: "FR|400|250\n" (Direction|xSpeed|ySpeed|\n)
  int sep1 = message.indexOf('|');
  int sep2 = message.indexOf('|', sep1 + 1);
  
  //indexof() returns -1 if character not found
  if (sep1 == -1 || sep2 == -1) {
    motors.setSpeeds(0, 0); //Stops on an invalid message 
    return;
  }
 
  //Extracting data from the recieved message
  String command = message.substring(0, sep1);
  int xSpeed = message.substring(sep1 + 1, sep2).toInt();
  int ySpeed = message.substring(sep2 + 1).toInt();
 
  //Stationary
  if (command == "S" || (xSpeed == 0 && ySpeed == 0)) {
    motors.setSpeeds(0, 0);
    return;
  }
  
  //Code logic for differential drive
  //Converting x,y speeds to left & right motor speed
  int leftSpeed = ySpeed + xSpeed; 
  int rightSpeed = ySpeed - xSpeed;

  //Constraints are set to the maximum and minimum speeds of the motors 
  leftSpeed = constrain(leftSpeed, -400, 400); 
  rightSpeed = constrain(rightSpeed, -400, 400);
 
  motors.setSpeeds(leftSpeed, rightSpeed); 
}