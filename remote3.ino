#include <SoftwareSerial.h>
 
// Initialize SoftwareSerial on pins 2 (RX) and 3 (TX)
SoftwareSerial XBee(2, 3); // RX = 2, TX = 3
 
// Button pins: Forward, left, right,  back
const int buttonPins[4] = {8, 9, 12, A1};
 
// Respective command characters for each button
char buttonCodes[4] = {'F', 'L', 'R', 'B'};

//initializing joystick buttons 
const int xJoy = 11;
const int yJoy = 10; 

//deadzone tuning to detect movement
const int lowThreshold = 505;
const int highThreshold = 545; 

//stores last command to check if new command is different 
String lastCommand = ""; 

//stores robo speed 
int xSpeed;
int ySpeed;

void setup() {

  XBee.begin(9600); //starts software serial connection at 9600 baud
  Serial.begin(9600); 
 
  // Set button pins as input with internal pull-ups enabled
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);

    //Internal pull up set to HIGH since buttons are HIGH when not pressed 
  }

  pinMode(xJoy, INPUT);
  pinMode(yJoy, INPUT);

}
 
void loop() {

  String command = ""; 

  //CODE FOR THE JOYSTICK 

  int xVal = analogRead(xJoy);
  int yVal = analogRead(yJoy);
  bool joystickActive = false;
  //if value analog value 505-545 it stops

  //forward y direction
  if (yVal < lowThreshold) {
    command += 'F';
    joystickActive = true;
    ySpeed = map(yVal, lowThreshold, 0, 0, 400);
  }

  //backward y direction
  if (yVal > highThreshold) {
    command += 'B';
    joystickActive = true;
    ySpeed = map(yVal, highThreshold, 1023, 0, -400);
  }

  //right x direction
  if (xVal > highThreshold) {
    command += 'L';
    joystickActive = true;
    xSpeed = map(xVal, lowThreshold, 0, 0, 300);
  }

  //left x direction
  if (xVal < lowThreshold) {
    command += 'R';
    joystickActive = true;
    xSpeed = map(xVal, highThreshold, 1023, 0, -300);
  }

  //buttons
  if (!joystickActive) {
    bool forwardPressed = false;
    bool backPressed = false;
    bool leftPressed = false;
    bool rightPressed = false;

    for (int i = 0; i < 4; i++) {
      bool isPressed = digitalRead(buttonPins[i]) == LOW;

      if (isPressed) {
        command += buttonCodes[i];

        if (buttonPins[i] == 8) forwardPressed = true;
        else if (buttonPins[i] == A1) backPressed = true;
        else if (buttonPins[i] == 9) leftPressed = true;
        else if (buttonPins[i] == 12) rightPressed = true;
      }
    }

    //Seting Y speed
    if (forwardPressed) ySpeed = 400;
    else if (backPressed) ySpeed = -400;

    //Seting X speed
    if (forwardPressed || backPressed) {
      if (digitalRead(9) == LOW) xSpeed = -200; // curve left
      else if (digitalRead(12) == LOW) xSpeed = 200; // curve right
    } 
    else {
      if (leftPressed) xSpeed = -400;
      else if (rightPressed) xSpeed = 400;
    }
  }

  if (command == "") {
    //delay(100);
    command = 'S';
    xSpeed = 0; 
    ySpeed = 0; 
  }

  //sending the command 
  String message = command + "|" + String(xSpeed) + "|" + String(ySpeed);
  XBee.println(message);
  Serial.println(message);
  lastCommand = command; 


  delay(50); // Debounce and loop pacing

}
 