#include <SoftwareSerial.h>
 
// Initialize SoftwareSerial on pins 2 (RX) and 3 (TX)
SoftwareSerial XBee(2, 3); // RX = 2, TX = 3
 
// Button pins: Forward, Back, Left, Right
const int buttonPins[4] = {4, 5, 6, 7};
 
// Respective command characters for each button
char buttonCodes[4] = {'F', 'B', 'L', 'R'};

String lastCommand = ""; 

void setup() {

  XBee.begin(9600); //starts software serial connection at 9600 baud
  Serial.begin(9600); 
 
  // Set button pins as input with internal pull-ups enabled
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);

    //Internal pull up set to HIGH since buttons are HIGH when not pressed 
  }

}
 
void loop() {

  String command = ""; 

  // Checking each button if its clicked 
  for (int i = 0; i < 4; i++) {
    bool current = digitalRead(buttonPins[i]);

    //dynamically adding characters to command based on buttons pressed
    if (digitalRead(buttonPins[i]) == LOW) {
      command += buttonCodes[i];
    }
  
  }
  
  //if no buttons are pressed, S is sent 
  if (command == "") {
    command = "S";
  }

  //sending new command 
  if (lastCommand != command) {
    XBee.println(command);
    Serial.print("Sent: ");
    Serial.println(command);
    
    lastCommand = command; 
  }
 
  delay(50); // Debounce and loop pacing

}
 