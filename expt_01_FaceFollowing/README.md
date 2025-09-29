# Experiment 01 - Face Following
From https://github.com/Mark-MDO47/expts_grove_vision_ai_v2

**Table Of Contents**
* [Top](#experiment-01-\--face-following "Top")
* [Introduction](#introduction "Introduction")

## Introduction
There is a demo project that does face following with a fan:
- https://wiki.seeedstudio.com/grove_vision_ai_v2_demo/ search for **Project I: Create a Face-Tracking Fan**

My first usage will be to add face following to my Skull Project https://github.com/Mark-MDO47/Skull-Project. We want to make the eyes follow the face detected by the Vision-AI V2.

The Skull Project uses eyes made from Adafruit HalloWing M4 Express. These use the SAMD51 processor (ATSAMD51G18).
- https://www.adafruit.com/product/4300
- http://ww1.microchip.com/downloads/en/DeviceDoc/60001507E.pdf

Because the Skull Project eyes are pretty busy just displaying the eyes, I don't want to interrupt them at random times with an I2C or UART message. Thus I plan to output the position information on two ESP32-C3 Analog channels, and the SAMD51 in the eyes can sample the information at any convenient time that doesn't interrupt its processing.

#### Low-Pass Filter for PWM Analog
[Top](#experiment-01-\--face-following "Top")<br>
I just realized I was looking at the Analog-to-Digital capabilities (ADC for analog input) instead of the Digital-to-Analog capabilities. The XIAO ESP32-C3 only has D10 with DAC.

I will start by using the ESP32 LEDC library for analog output; that way I can use the same code for both analog outputs. I may need to implement filtering on the analog outputs so the SAMD51 can do reliable sensing.

I previously did LEDC analog outputs in my https://github.com/Mark-MDO47/DuelWithBanjos project. I didn't need any filtering with the LED outputs.

I got the following references from https://diyelectromusic.com/2024/03/31/esp32-and-pwm **ESP32 and PWM**. Note: I think EDN used to mean Electronic Design News but As far as I can tell the website doesn't use that anymore.
There are a range of really useful and detailed tutorials on the filtering circuit aspects of PWM on EDN. Some examples worth taking a look at are:
- Three paths to a free DAC - https://www.edn.com/three-paths-to-a-free-dac/
- Double up on and ease the filtering requirements for PWMs - https://www.edn.com/double-up-on-and-ease-the-filtering-requirements-for-pwms/
- Combine two 8-bit outputs to make one 16-bit DAC - https://www.edn.com/combine-two-8-bit-outputs-to-make-one-16-bit-dac/
- A faster PWM-based DAC - https://www.edn.com/a-faster-pwm-based-dac/
- Cancel PWM DAC ripple with analog subtraction - https://www.edn.com/cancel-pwm-dac-ripple-with-analog-subtraction/
