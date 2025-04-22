# MiniProject: Exploring IoTempower Services and Commands

Click on **Commands** to explore available device drivers and commands.

---

## 1. RFID Reader (`rfid_x`)

- **Command Purpose**: Read RFID tags (e.g., for door access systems).
- **Example Commands**:
  ```bash
  mfrc522(reader);
  ```

  This example will report data of a supported RFID/tag in node_topic/reader and uid in node_topic/reader/uid (works on most NFC tags) as well as picc in node_topic/reader/uid.


- **Possible Use Case**: Use to identify users by their RFID cards.
- **Wiring**:
  Wemos
D1 Mini/    mfrc522/  
NodeMCU      -  rfid-rc522 board  
(esp32)  

    3V3      -  3.3V  
     D8 ( 5) -  sda  
     D7 (23) -  MOSI  
     D6 (19) -  MISO  
     D5 (18) -  SCK  
     D0 (26) -  RST  
      G      -  GND  
    N/C      -  IRQ (IRQ is not connected for use in IoTempower)  

---

## 2. PWM Control

- **Command Purpose**: Set PWM signal, e.g., to control brightness or motor speed.
- **Example Commands**:
  ```bash
  pwm(blue, ONBOARDLED, 2000);  
  ```
- **Possible Use Case**: Adjust LED brightness or motor power.
- **Wiring**:
  - PWM output pin connected to LED/motor via suitable transistor or driver.

---

## 3. Servo  

- **Command Purpose**: Control the angle of a servo motor.
- **Example Commands**:
  ```bash
  servo(m1, D4);
  ```
- **Possible Use Case**: Open a door, turn a camera.
- **Wiring**:
  - Signal → D3 (or other GPIO)  
  - Power → 5V (external power may be needed)  
  - GND → GND (shared ground with MCU)  

---

## 4. Ultra_sonic_distance (`hcsr04/rcwl-1601`)

- **Command Purpose**: Measure distance using ultrasonic sensor (e.g., RCWL-1601 or HC-SR04).
- **Example Commands**:
  ```bash
  hcsr04(distance, D5, D6).with_precision(10);
  ```
- **Possible Use Case**: Detect people approaching, trigger light or alarm.
- **Wiring**:
  - TRIG → D4  
  - ECHO → D5  
  - VCC → 5V  
  - GND → GND  

---

## 5. RGB LED (`rgbled_x`)

- **Command Purpose**: Control the color of an RGB LED.
- **Example Commands**:
  ```bash
  rgbled_x set 255 0 0  # Red
  rgbled_x set 0 255 0  # Green
  rgbled_x set 0 0 255  # Blue
  ```
- **Possible Use Case**: Visual feedback – red for alert, green for success, etc.
- **Wiring Hint**:
  - R → D1  
  - G → D2  
  - B → D3  
  - Use resistors for each color pin to limit current  

---
