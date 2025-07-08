# Arduino-Based Remote-Control Car with Curve Turning

This is a wireless remote-controlled tank-style robot built using:
- 2 Arduino Unos
- Zumo robot car chassis (with tracked wheels)
- 4-button digital remote (Forward, Back, Left, Right)
- XBee Series 1 modules for wireless communication

## Features
✅ Real-time wireless control  
✅ Curved turning (e.g. FR, BL)  
✅ Clean serial logging  
✅ Debounced input handling

## Code Structure

### Remote Controller (`/remote/remote_control.ino`)
- Reads 4 buttons as digital inputs with internal pull-ups
- Sends commands as strings over XBee serial when buttons are pressed
- Supports multiple simultaneous button presses for curved movement
- Sends `"S"` when no button is pressed to stop the car

### Car Controller (`/car/car_controller.ino`)
- Receives string commands over XBee serial
- Controls motors accordingly using the ZumoMotors library
- Handles forward, backward, left, right, curved turns, and stop commands


## Future Work
- Add speed control via potentiometer or joystick  
- Add obstacle detection using ultrasonic sensor  
- Add OLED display on the remote  
