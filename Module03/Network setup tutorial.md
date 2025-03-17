# Simple IoT Network Setup with MQTT

This is a step-by-step tutorial to set up an IoT network on a router running MQTT. This guide assumes you have the necessary hardware (router, IoT devices, etc.) and software installed.

## Step 1: Install MQTT Broker on the Router

1. **Access Router's Admin Interface**  
   Open a web browser and enter the router's IP address (e.g., `192.168.1.1`). Log in using your admin credentials.

2. **Install MQTT Broker**  
   Depending on the router's capabilities, install an MQTT broker like **Mosquitto** (many routers with custom firmware like OpenWRT or DD-WRT support it).
   - If using OpenWRT, you can install Mosquitto via the command line:
     ```bash
     opkg update
     opkg install mosquitto
     ```
   - For other routers, check your router’s documentation for installing MQTT brokers or using a pre-configured firmware that supports it.

## Step 2: Configure MQTT Broker

1. **Configure Mosquitto**  
   After installing Mosquitto, edit the configuration file to allow remote connections.
   - For Mosquitto, the default config file is usually located at `/etc/mosquitto/mosquitto.conf`.
   - Ensure that the broker allows remote connections by adding or modifying the following lines:
     ```bash
     listener 1883
     allow_anonymous true
     ```
     - **Port 1883** is the default for non-secure MQTT connections.
     - `allow_anonymous true` allows devices to connect without authentication (you may choose to enable authentication for added security).

2. **Restart Mosquitto**  
   After saving the configuration file, restart Mosquitto to apply changes:
   ```bash
   /etc/init.d/mosquitto restart

## Step 3: Set Up IoT Devices
   **Connect IoT Devices to WiFi**
   - Make sure each IoT deviceis connected to your router’s WiFi network.

   **Configure MQTT Client on IoT Devices**
   - On each IoT device, configure the MQTT client to point to your router’s IP address (i.e., the IP of the machine running the MQTT broker).

## Step 4: Test MQTT Communication
   **Use MQTT Client Software**
   - On your PC or another device, install an MQTT client (such as MQTT.fx or Mosquitto client).

   **Subscribe to Topics**
   - Connect the MQTT client to your router’s IP address and port 1883.

   **Subscribe to topics such as home/temperature to see messages from your IoT devices.**
   - Publish Messages
   - Test by publishing messages to a topic from your MQTT client (e.g., publish a message to home/lights).

   **Check IoT Device Response**
   - Your IoT devices should receive and act upon the published message. For example, if you publish a message to turn on a light, your device should respond accordingly.

