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
const int deadzone = 50;

//stores last command to check if new command is different 
String lastCommand = ""; 
bool joystickActive = false;

//stores robo speed 
int xSpeed;
int ySpeed;
const int maxSpeed = 400;

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
  int xVal = -1 * (analogRead(xJoy) - 512);  // range approx -512 to +511
  int yVal = -1 * (analogRead(yJoy) - 512);  // range approx -512 to +511
  

  //calculating curve angle and curve radius 
  float magnitude = sqrt(
    (long)xVal * (long)xVal + 
    (long)yVal * (long)yVal
  );

  float angle = atan2(yVal, xVal);  // angle in radians (-pi to +pi)

  //if input is below deadzone then car is stationary 
  if ( abs(xVal) < deadzone && abs(yVal) < deadzone) {
      command = "S";  // stop
      xSpeed = 0;
      ySpeed = 0;
      joystickActive = false;
  } 
  else {
      joystickActive = true;
      float speedRatio = magnitude / 512.0;
      float speed = speedRatio * maxSpeed;
      float angle = atan2(yVal, xVal);

      ySpeed = magnitude * sin(angle);  
      xSpeed = magnitude * cos(angle);  

      // Assign direction based on angle
      //CHANGE pi/16 to pi/16 LAATER FOR R F B L 
      if (angle >= -PI/16 && angle < PI/16) {
          command = "R";
          //ySpeed = 0;
      }else if (angle >= PI/16 && angle < 3*PI/16)
          command = "FR";
      else if (angle >= 3*PI/16 && angle < 5*PI/16) {
          command = "F";
          //xSpeed = 0;
      } else if (angle >= 5*PI/16 && angle < 7*PI/16)
          command = "FL";
      else if (angle >= 7*PI/16 || angle < -7*PI/16) {
          command = "L";
          //ySpeed = 0;
      } else if (angle >= -7*PI/16 && angle < -5*PI/16) {
          command = "BL";
      } else if (angle >= -5*PI/16 && angle < -3*PI/16) {
          command = "B";
          //xSpeed = 0;
      } else if (angle >= -3*PI/16 && angle < -PI/16) {
          command = "BR";
      }
  }
  
  //buttons code 
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

  //sending the command 
  String message = command + "|" + String(xSpeed) + "|" + String(ySpeed);
  XBee.println(message);
  Serial.println(message);
  lastCommand = command; 

  delay(50); // Debounce and loop pacing

}
 