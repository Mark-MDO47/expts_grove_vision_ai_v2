# Experiment 01 - Face Following
From https://github.com/Mark-MDO47/expts_grove_vision_ai_v2

<img src="https://github.com/Mark-MDO47/Skull-Project/blob/master/resources/images/TwoSkullsTwoHats_1024.jpg" width="800" alt="Two 2-eye Skulls and Control Boxes, one with Viking hat and one with Pirate hat">

**Table Of Contents**
* [Top](#experiment-01-\--face-following "Top")
* [Introduction](#introduction "Introduction")

## Introduction
There is a demo project that does face following with a fan:
- https://wiki.seeedstudio.com/grove_vision_ai_v2_demo/ search for **Project I: Create a Face-Tracking Fan**

My first usage will be to add face following to my Skull Project https://github.com/Mark-MDO47/Skull-Project. We want to make the eyes follow the face detected by the Vision-AI V2.

The Skull Project uses eyes made from Adafruit HalloWing M4 Express. These use the SAMD51 processor (ATSAMD51J19).
- https://www.adafruit.com/product/4300
- http://ww1.microchip.com/downloads/en/DeviceDoc/60001507E.pdf

Because the Skull Project eyes are pretty busy just displaying the eyes, I don't want to interrupt them at random times with an I2C or UART message. Thus I plan to output the position information on two ESP32-C3 Analog channels, and the SAMD51 in the eyes can sample the information at any convenient time that doesn't interrupt its processing.

