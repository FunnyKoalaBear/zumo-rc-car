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
- `/remote/`: code for the handheld button remote
- `/car/`: code for the car controller (receives and acts on commands)

## Future Work
- Add speed control via potentiometer or joystick  
- Add obstacle detection using ultrasonic sensor  
- Add OLED display on the remote  
