# Arduino Uno Obstacle Avoidance Car

## Overview
This project is an Arduino Uno-based robotic car that uses an HC-SR04 ultrasonic sensor to detect obstacles and automatically navigates around them using four geared DC motors controlled by an L298N motor driver.

## Features
- Obstacle detection using ultrasonic sensor
- Automatic movement: forward, reverse, turn
- Four-wheel drive with geared motors
- Simple avoidance logic
- Serial output for debugging

## Hardware Requirements
- Arduino Uno
- HC-SR04 Ultrasonic Sensor
- L298N Motor Driver Module
- 4x DC Geared Motors
- Jumper wires
- Chassis and wheels
- Power supply (battery pack for motors and Arduino)

## Pin Connections
| Component         | Arduino Pin |
|-------------------|-------------|
| Motor IN1         | 2           |
| Motor IN2         | 3           |
| Motor IN3         | 4           |
| Motor IN4         | 5           |
| Motor ENA (PWM)   | 9           |
| Motor ENB (PWM)   | 10          |
| Ultrasonic TRIG   | 6           |
| Ultrasonic ECHO   | 7           |

## How It Works
1. The car moves forward by default.
2. The ultrasonic sensor continuously measures the distance to obstacles ahead.
3. If an obstacle is detected within 20 cm, the car stops, reverses, turns right, and then resumes forward movement.
4. All actions are logged to the Serial Monitor for debugging.

## Setup Instructions
1. Assemble the car chassis and mount the motors and wheels.
2. Connect the motors to the L298N motor driver as per the pin table above.
3. Connect the L298N motor driver to the Arduino Uno.
4. Connect the HC-SR04 ultrasonic sensor to the Arduino Uno.
5. Power the Arduino and motor driver (use separate power sources if needed).
6. Upload the `ultrasonic_car.ino` code to your Arduino Uno using the Arduino IDE.
7. Open the Serial Monitor at 9600 baud to view distance readings and debug info.

## Code File
- `ultrasonic_car.ino`: Main Arduino sketch for obstacle avoidance logic.

## Testing & Debugging
- Place the car in an open area and observe its movement.
- Place obstacles in front of the car to test avoidance behavior.
- Use the Serial Monitor to check sensor readings and motor actions.
- Adjust the `OBSTACLE_DIST` value in the code for different sensitivity.

## Troubleshooting
- If the car does not move, check motor wiring and power supply.
- If the sensor always reads 0, check TRIG/ECHO connections.
- If the car does not avoid obstacles, verify the sensor orientation and code upload.

## Customization
- Change motor speed by adjusting PWM values in the code.
- Modify avoidance logic for different behaviors (e.g., random turns).
- Add more sensors for advanced navigation.

## License
This project is open source and free to use for educational and personal purposes.