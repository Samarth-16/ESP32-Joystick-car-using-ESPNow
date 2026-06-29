\# ESP-NOW 4WD RC Car



An ESP32-powered, 4-wheel drive (4WD) RC car controlled wirelessly via \*\*ESP-NOW\*\* using a second ESP32 equipped with an analog joystick module.



\## 🚀 Features

\* \*\*Low Latency Control:\*\* Powered by the connectionless ESP-NOW protocol.

\* \*\*Proportional Speed:\*\* Motor speeds dynamically scale depending on how far the joystick is pushed.

\* \*\*Auto-Failsafe:\*\* The car automatically stops if wireless connection drops for more than 500ms.



\---



\## 🛠️ Components \& Hardware

\* 2 × ESP32 DevKit V1

\* 1 × Joystick Module

\* 1 × L298N Motor Driver

\* 4 × DC Gear Motors (4WD Chassis)

\* 1 × 7.4V Li-ion battery pack (or 2×18650 cells)

\* Jumper wires



\---



\## 🔌 Wiring Configurations



\### 1. Transmitter (Joystick Node)

| Joystick Pin | ESP32 Pin | Description |

| :--- | :--- | :--- |

| \*\*GND\*\* | GND | Ground |

| \*\*VCC\*\* | 3.3V | Power (Safe logic level for ESP32) |

| \*\*VRx\*\* | GPIO 34 | Analog X-axis |

| \*\*VRy\*\* | GPIO 35 | Analog Y-axis |

| \*\*SW\*\* | GPIO 27 | Digital Push Button |



\### 2. Receiver (Car Node)

| L298N Driver Pin | Connected To | Description |

| :--- | :--- | :--- |

| \*\*12V Terminal\*\* | Battery Positive (+) | Direct battery power |

| \*\*GND Terminal\*\* | Battery Ground (-) \*\*\&\*\* ESP32 GND | \*\*Crucial:\*\* Must share common ground |

| \*\*5V Terminal\*\* | ESP32 Vin Pin | Powers the ESP32 via the L298N internal regulator |

| \*\*IN1\*\* | ESP32 GPIO 25 | Left Motor Direction 1 |

| \*\*IN2\*\* | ESP32 GPIO 26 | Left Motor Direction 2 |

| \*\*IN3\*\* | ESP32 GPIO 32 | Right Motor Direction 1 |

| \*\*IN4\*\* | ESP32 GPIO 33 | Right Motor Direction 2 |

| \*\*ENA\*\* | ESP32 GPIO 14 | Left Motor Speed (PWM) |

| \*\*ENB\*\* | ESP32 GPIO 12 | Right Motor Speed (PWM) |



\---



\## ⚙️ How to Setup and Flash



\### Step 1: Find your Receiver MAC Address

1\. Open `Firmware/MAC\_Scanner/MAC\_Scanner.ino` in your Arduino IDE.

2\. Flash it to your \*\*Receiver ESP32\*\* (the one attached to the car).

3\. Open the Serial Monitor at `115200` baud rate and copy the printed MAC Address.



\### Step 2: Configure and Flash the Transmitter

1\. Open `Firmware/Transmitter/Transmitter.ino`.

2\. Locate the line: `uint8\_t receiverAddress\[] = {0xFC, 0xE8, 0xC0, 0x00, 0x00, 0x00};`

3\. Replace the bytes with your actual receiver MAC Address.

4\. Flash this code to your \*\*Transmitter ESP32\*\*.



\### Step 3: Flash the Receiver

1\. Open `Firmware/Receiver/Receiver.ino`.

2\. Flash this code directly to your \*\*Receiver ESP32\*\*.



\---



\## 🕹️ Car Controls Mapping



| Joystick Direction | Car Movement |

| :--- | :--- |

| \*\*Up\*\* | Forward (Variable Speed) |

| \*\*Down\*\* | Reverse (Variable Speed) |

| \*\*Left\*\* | Hard Left Turn (Variable Speed) |

| \*\*Right\*\* | Hard Right Turn (Variable Speed) |

| \*\*Center\*\* | Full Stop |



\---



\## ⚠️ Troubleshooting Tips

\* \*\*Car Moves Backward:\*\* If a motor turns backward when it should go forward, simply flip the output wires (`OUT1`/`OUT2` or `OUT3`/`OUT4`) directly on the L298N block terminals.

\* \*\*ESP32 Resetting Loop:\*\* Ensure your batteries are fully charged. When DC motors draw heavy startup currents, it can drop the logic voltage and cause the ESP32 to brown out.

