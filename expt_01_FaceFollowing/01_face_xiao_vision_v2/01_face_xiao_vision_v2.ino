// 01_face_xiao_vision_v2 2025
// Author: https://github.com/Mark-MDO47/
// Repo:   https://github.com/Mark-MDO47/expts_grove_vision_ai_v2
//

/*
MIT License

Copyright (c) 2025 Mark-MDO47

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*

This code runs in the XIAO ESP32-C3 attached to the Grove Vision AI V2
  https://www.seeedstudio.com/Grove-Vision-AI-Module-V2-p-5851.html
  https://www.seeedstudio.com/Seeed-Studio-XIAO-ESP32C3-Tape-Reel-p-6471.html

See this for description.
  https://wiki.seeedstudio.com/grove_vision_ai_v2/

The goal is to add face following to my Skull Project https://github.com/Mark-MDO47/Skull-Project.
We want to make the eyes follow the face detected by the Vision-AI V2.

The Skull Project uses eyes made from Adafruit HalloWing M4 Express. These use the SAMD51 processor (ATSAMD51G18).
  https://www.adafruit.com/product/4300
  http://ww1.microchip.com/downloads/en/DeviceDoc/60001507E.pdf

Because the Skull Project eyes are pretty busy just displaying the eyes, I don't want to interrupt them at random
  times with an I2C or UART message. Thus I plan to output the position information on two ESP32-C3 Analog channels,
  and the SAMD51 in the eyes can sample the information at any convenient time that doesn't interrupt its processing.

CONNECTIONS:
In the following table the My Use column:
    V - connect through to Vision AI V2
    E - connect to my Skull-Eyeball project (https://github.com/Mark-MDO47/Skull-Project)
    X - reserve for future use external to Vision AI V2

My Use	XIAO pin
X	      D0/A0 #1
E	      D1/A1 #2
E	      D2/A2 #3
V	      D3/A3 #4
X	      D4/SDA #5
X	      D5/SCL #6
V	      D6/TX #7
V	      D7/RX #8
X	      D8/SCK #9
X	      D9/MISO #10
X	      D10/MOSI #11
V	      3V3 #12
V/E/X	  GND #13
V      	VUSB #14

COMPILATION WARNINGS:
#include-ing Seeed_Arduino_SSCMA.h produces various warnings about deprecated coding, but seems to compile OK.

*/

#include <Seeed_Arduino_SSCMA.h>

SSCMA AI;

// Define pins for Seeed XIAO ESP32-C3
// GPIO20 = RX, GPIO21 = TX
#define RX_PIN 20     // D7 on XIAO ESP32-C3
#define TX_PIN 21     // D6 on XIAO ESP32-C3

// GPIO3 = analog for horizontal
// GPIO4 = analog for vertical
#define ANA_H_PIN 3   // A1 on XIAO ESP32-C3
#define ANA_V_PIN 4   // A2 on XIAO ESP32-C3

void setup() {
  Serial.begin(115200);   // Serial monitor
  delay(1000);
  Serial.println("Starting Grove Vision AI V2 test (UART)...");

  // Start hardware UART1 for Vision AI
  Serial1.begin(921600, SERIAL_8N1, RX_PIN, TX_PIN);

  // Initialize SSCMA library with Vision AI UART
  if (!AI.begin(&Serial1)) {
    Serial.println("Failed to initialize Vision AI V2 over UART!");
    while (1);
  }
  Serial.println("Vision AI V2 initialized successfully!");
}

void loop() {
  // Run inference (model slot 1, no image output)
  if (!AI.invoke(1, false, false)) {
    // Print detected bounding boxes
    for (auto &box : AI.boxes()) {
      Serial.printf("Target=%d Score=%.2f X=%d Y=%d W=%d H=%d\n",
                    box.target, box.score,
                    box.x, box.y, box.w, box.h);
    }
  } else {
    Serial.println("No result from Vision AI");
  }
  delay(500);
}