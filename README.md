Obstacle Avoiding Robot Car using Arduino, Ultrasonic Sensor and Servo

Project Overview
This project implements an autonomous obstacle-avoiding robot car using an Arduino, HC-SR04 ultrasonic sensor, servo motor, and L298N motor driver. The robot continuously scans its surroundings by sweeping the ultrasonic sensor across multiple angles using a servo motor. Based on the distance measurements obtained, it dynamically decides whether to move forward or perform an avoidance maneuver. The project demonstrates real-time sensing, motor control, and decision-based navigation, making it suitable as a foundational robotics or embedded systems project.

System Working
The servo motor sweeps the ultrasonic sensor across predefined angles.
Distance measurements are collected and stored in an array.
The system checks if any detected object is within a threshold distance of 30 cm.
If an obstacle is detected:
  The robot moves backward and turns to avoid collision.
If no obstacle is detected:
  The robot moves forward at full speed.
Motors are controlled independently using PWM for speed regulation.

Components Used
Arduino Uno
HC-SR04 Ultrasonic Sensor
Servo Motor (SG90 or equivalent)
L298N Motor Driver
2 DC Motors
Robot Chassis
Jumper Wires
External Power Supply / Battery Pack

Pin Configuration
| Component | Arduino Pin |
| --------- | ----------- |
| Trig      | 13          |
| Echo      | 12          |

| Component | Arduino Pin |
| --------- | ----------- |
| Signal    | 11          |

L298N Motor Driver
| Motor | Enable Pin | Control Pins     |
| ----- | ---------- | ---------------- |
| Left  | 6          | IN1 = 7, IN2 = 5 |
| Right | 3          | IN3 = 4, IN4 = 2 |

The ultrasonic sensor scans the environment at the following angles:
60°, 70°, 80°, 90°, 100°, 110°, 120°
This provides a wide forward field of view for obstacle detection.

Key Features:
Servo-based ultrasonic scanning
Real-time distance measurement
Independent motor control
PWM-based speed regulation
Obstacle detection within 30 cm
Motor diagnostic test during startup

Motor Test Routine
On startup, a motor test routine is executed:
  Each motor runs forward, stops, then runs in reverse
  Ensures correct wiring and motor orientation before autonomous operation
Distance Measurement Logic
  Distance is calculated using ultrasonic time-of-flight
  Speed of sound assumed as 343 m/s
  Distance output is in millimeters
  Timeout handling returns a default maximum value of 4000 mm

Setup Instructions
Hardware Setup
  Assemble the robot chassis
  Connect motors to the L298N motor driver
  Mount the ultrasonic sensor securely on the servo motor
  Verify all pin connections as per the configuration table
Software Setup
  Install the Arduino IDE
  Ensure the Servo library is available
  Upload the provided Arduino sketch to the board
Execution
  Power on the system
  Observe the motor test sequence
  The robot will begin autonomous navigation

Possible Enhancements
Implement PID control for smoother motion
Use weighted distance-based decision making instead of a fixed threshold
Add Bluetooth or Wi-Fi for remote control
Integrate additional sensors such as IR or line sensors
Log sensor data for performance analysis

Learning Outcomes
Embedded C and Arduino programming
PWM motor control using L298N
Sensor integration and calibration
Real-time decision-making in robotics
Hardware-software debugging

Author

Raj
B.Tech Student
