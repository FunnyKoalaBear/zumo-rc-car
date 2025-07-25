# Arduino-Based Remote-Control Car with Curve Turning

This is a wireless remote-controlled tank-style robot built using:
- 2 Arduino Unos
- DFRobot Input Shield V2
- Zumo robot car chassis (with tracked wheels)  
- XBee Series 1 modules for wireless communication  

## Features
✅ Real-time wireless control  
✅ Curved turning (e.g. FR, BL)  
✅ Clean serial logging  
✅ Debounced input handling  
✅ Joystick-based speed control (V3)

---

## Version Overview

### ✅ V1 – Basic Movement
- **Remote** and **car** use basic digital input and serial transmission.
- Supports only single-button commands: Forward (`F`), Backward (`B`), Left (`L`), Right (`R`), Stop (`S`).
- No curved movement or speed control.

### ✅ V2 – Curved Turning Support
- **Remote:** `remote3.ino`  
- **Car:** `car2.ino`
- Adds curved direction support (e.g. `FR`, `BL`) by detecting multiple simultaneous button presses.
- Fixed speed for all directions.
- Simple and reliable with digital buttons.

### ✅ V3 – Speed & Turn Control with Joystick
- **Remote:** `remote3.2.ino`  
- **Car:** `car3.ino`
- Uses analog joystick input to determine both direction and speed.
- Smooth curved turns and dynamic speed control based on joystick pressure.
- Commands include analog speed/magnitude information.

---

## Code Structure

### Remote Controller (`remote3.ino` / `remote3.2.ino`)
- `remote3.ino`: V2 logic using 4 digital buttons  
- `remote3.2.ino`: V3 logic using analog joystick input  
- Sends command strings via XBee (e.g., `"F"`, `"FR"`, `"S"`, or more complex analog-based signals)  
- Debounces inputs and handles multiple button presses (V2)  
- Calculates direction and magnitude for analog input (V3)

### Car Controller (`car2.ino` / `car3.ino`)
- `car2.ino`: V2 logic to process fixed-speed movement and curved turns  
- `car3.ino`: V3 logic to process analog-based speed and direction  
- Receives string commands over XBee and controls motors via ZumoMotors library  
- Handles stopping, turning, curving, and speed regulation

---

## Future Work
- Add manual speed control fallback using a potentiometer  
- Integrate ultrasonic sensors for obstacle avoidance  
- Display control status and inputs on an OLED screen  

