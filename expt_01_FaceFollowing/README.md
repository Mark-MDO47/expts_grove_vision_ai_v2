# Experiment 01 - Face Following
From https://github.com/Mark-MDO47/expts_grove_vision_ai_v2

<img src="https://github.com/Mark-MDO47/Skull-Project/blob/master/resources/images/TwoSkullsTwoHats_1024.jpg" width="800" alt="Two 2-eye Skulls and Control Boxes, one with Viking hat and one with Pirate hat">

**Table Of Contents**
* [Top](#experiment-01-\--face-following "Top")
* [Introduction](#introduction "Introduction")
* [Did Nobody Mention there would be Problems with Analog Signals?](#did-nobody-mention-there-would-be-problems-with-analog-signals "Did Nobody Mention there would be Problems with Analog Signals?")

## Introduction
[Top](#experiment-01-\--face-following "Top")<br>
There is a demo project that does face following with a fan:
- https://wiki.seeedstudio.com/grove_vision_ai_v2_demo/ search for **Project I: Create a Face-Tracking Fan**

My first usage will be to add face following to my Skull Project https://github.com/Mark-MDO47/Skull-Project. We want to make the eyes follow the face detected by the Vision-AI V2.

The Skull Project uses eyes made from Adafruit HalloWing M4 Express. These use the SAMD51 processor (ATSAMD51J19).
- https://www.adafruit.com/product/4300
- http://ww1.microchip.com/downloads/en/DeviceDoc/60001507E.pdf

Because the Skull Project eyes are pretty busy just displaying the eyes, I don't want to interrupt them at random times with an I2C or UART message. Thus I plan to output the position information on two ESP32-C3 Analog channels, and the SAMD51 in the eyes can sample the information at any convenient time that doesn't interrupt its processing.

## Did Nobody Mention there would be Problems with Analog Signals?
[Top](#experiment-01-\--face-following "Top")<br>
Of course it is not that easy. For details of how I came up with my plan, see the following
- https://github.com/Mark-MDO47/expts_grove_vision_ai_v2/blob/master/_README_Analog_Communication.md

The result of all that is:
- XIAO ESP32-C3 attached to Vision-AI V2 will report data for one face detection as analog voltages on XIAO pins A2 and A2
  - Will use ESP32 LEDC PWM library running at 5 kHz feeding into a low-pass R-C filter
    - Approximately 8192 discrete levels of analog voltage (13 bits)
    - Filter Cutoff Frequency (-3dB)	31.8 Hz
    - Filter Time Constant	5 milliSec
- Analog signals will go to both HalloWing M4 Express on pins A3 and A4
  - The ATSAMD51 will sample the analog signals periodically, without interruption to its processing
  - The HalloWing M4 Express has a 1.54" display 240x240 full color IPS TFT
  - Thus there will be approximately 32 discrete levels of analog voltage for each pixel in each direction
  - That is a little overkill, but the key factor is 5 kHz which provides stability for the analog voltages
