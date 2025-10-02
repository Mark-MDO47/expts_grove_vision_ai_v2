# Experiment 01 - Face Following
From https://github.com/Mark-MDO47/expts_grove_vision_ai_v2

**Table Of Contents**
* [Top](#experiment-01-\--face-following "Top")
* [Introduction](#introduction "Introduction")
  * [Low-Pass Filter for PWM Analog](#low\-pass-filter-for-pwm-analog "Low-Pass Filter for PWM Analog")
* [XIAO Connector On Vision-AI V2](#xiao-connector-on-vision\-ai-v2 "XIAO Connector On Vision-AI V2")

## Introduction
There is a demo project that does face following with a fan:
- https://wiki.seeedstudio.com/grove_vision_ai_v2_demo/ search for **Project I: Create a Face-Tracking Fan**

My first usage will be to add face following to my Skull Project https://github.com/Mark-MDO47/Skull-Project. We want to make the eyes follow the face detected by the Vision-AI V2.

The Skull Project uses eyes made from Adafruit HalloWing M4 Express. These use the SAMD51 processor (ATSAMD51G18).
- https://www.adafruit.com/product/4300
- http://ww1.microchip.com/downloads/en/DeviceDoc/60001507E.pdf

Because the Skull Project eyes are pretty busy just displaying the eyes, I don't want to interrupt them at random times with an I2C or UART message. Thus I plan to output the position information on two ESP32-C3 Analog channels, and the SAMD51 in the eyes can sample the information at any convenient time that doesn't interrupt its processing.

### Low-Pass Filter for PWM Analog
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

Got these from Google search
- Low Pass/High Pass Filter Calculator - https://www.digikey.com/en/resources/conversion-calculators/conversion-calculator-low-pass-and-high-pass-filter
- Time Constant Calculator - https://www.digikey.com/en/resources/conversion-calculators/conversion-calculator-time-constant

Using the above two calculators for a simple R/C filter, I think this will work
| Parameter | Value | Formula |
| --- | --- | --- |
| Resistance | 5K Ohm | N/A |
| Capacitance | 1 microFarad | N/A |
| Time Constant | 5 milliSec | TC = Resistance * Capacitance |
| Cutoff Frequency (-3dB) | 31.8 Hz | Fc = 1 / (2 * PI * Resistance * Capacitance) |

The Time Constant is such that after a change of one voltage value to another, 1 time constant later the value has moved 63% of the distance. At 5 time constants it is about 99% of the way there.

The Cutoff Frequency is at -3dB, which means that at that frequency and above the amplitude is reduce by 50% or more.

## XIAO Connector On Vision-AI V2
[Top](#experiment-01-\--face-following "Top")<br>
In trying to decide which pins to route to directly to the XIAO header and which to use externally, I found this helpful. Info gathered from:
- XIAO C3 pinout - https://files.seeedstudio.com/wiki/XIAO_WiFi/Resources/XIAO-ESP32C3-pinout_sheet.xlsx
- getting started with XIAO C3 - https://wiki.seeedstudio.com/XIAO_ESP32C3_Getting_Started/
- Vision-AI V2 schematic - https://files.seeedstudio.com/wiki/grove-vision-ai-v2/Grove_Vision_AI_Module_V2_Circuit_Diagram.pdf
- Himax chip datasheet - https://files.seeedstudio.com/wiki/grove-vision-ai-v2/HX6538_datasheet.pdf

In the following table the **My Use** column:
- V - connect through to Vision-AI V2
- E - connect to my Skull-Eyeball project (https://github.com/Mark-MDO47/Skull-Project)
- X - reserve for future use external to Vision-AI V2

| My Use | XIAO pin | XIAO usage | HX6538-A usage | HX Reset | HX pin |
| --- | --- | --- | --- | --- | --- |
| X | D0/A0 #1 | Dig/Ana | GP I/O FS PL AON 3.3V-OK  | On-Rst-Inp PL |  PA0 #18 |
| E | D1/A1 #2 | Dig/Ana | GP I/O FS PL 3.3V-OK | On-Rst-Inp PL | PB11 #46 |
| E | D2/A2 #3 | Dig/Ana | GP I/O FS PL 3.3V-OK | On-Rst-Inp PL | PB8 #94 |
| V | D3/A3 #4 | Dig/C3-NOT-Ana | On-Rst-LO I FS PH AON 3.3V-OK | N/A | RESETN #17 |
| X | D4/SDA #5 | Dig/IIC | GP/IIC-SDA I/O FS  | On-Rst-Inp PH | PA3 #24 |
| X | D5/SCL #6 | Dig/IIC | GP/IIC-SCL I/O FS | On-Rst-Inp PH | PA2 #23 |
| V | D6/TX #7 | Dig/UART | GP/UART-RX I/O FS PL 3.3V-OK | On-Rst-Inp PL | PB6 #92 |
| V | D7/RX #8 | Dig/UART | GP/UART-TX I/O FS PL 3.3V-OK | On-Rst-Inp PL | PB7 #93 |
| X | D8/SCK #9 | Dig/SPI | GP/SPI-SCLK I/O FS PL 3.3V-OK | On-Rst-Inp PL | PB4 #74 |
| X | D9/MISO #10 | Dig/SPI | GP/SPI-IN-D1 I/O FS PL 3.3V-OK | On-Rst-Inp PL | PB3 #73 |
| X | D10/MOSI/DAC #11 | Dig/SPI/DAC | GP/SPI-IN-D0 I/O FS PL 3.3V-OK | On-Rst-Inp PL | PB2 #72 |
| V | 3V3 #12 | Pwr | N/A Pwr Imax=600mA | N/A | N/A |
| V/E/X | GND #13 | Pwr | N/A Pwr | N/A | N/A |
| V | VUSB #14 | Pwr | N/A Pwr input either Vision USB or XIAO USB | N/A | N/A |

Notes: 
- Pin Types:
  - A =Analog, I =Input, O =Output, P =Power, G =Ground , FS =Fail S afe
- Reset States:
  - PH =Pull High, PL =Pull Low
- Pin Domains:
  - SIF =1.8V only, PIF =1.8V or AON =1.8V or 3.3V (always on)
-  GND:
  -  Instead of pulling ground from the pin on this connector, I plan to power via XIAO USB and distribute ground from there
