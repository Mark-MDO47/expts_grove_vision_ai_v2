# README - Analog Communication
In these experiments I will communicate location data from an XAIO ESP32-C3 to two @ Adafruit HalloWing M4 Express (my Skull Project).

**Table Of Contents**
* [Top](#readme-\--analog-communication "Top")
* [Useful Documentation](#useful-documentation "Useful Documentation")
* [Low-Pass Filter for PWM Analog](#low\-pass-filter-for-pwm-analog "Low-Pass Filter for PWM Analog")

## Useful Documentation
[Top](#readme-\--analog-communication "Top")<br>
The XIAO ESP32-C3 is small, capable, and I have some in my parts bin. Also it works with the "XIAO connector" on the Vision-AI V2.
- XIAO ESP32-C3 "soldered" - https://www.seeedstudio.com/Seeed-Studio-XIAO-ESP32C3-Pre-Soldered-p-6331.html
- XIAO ESP32-C3 "tape & reel" - https://www.seeedstudio.com/Seeed-Studio-XIAO-ESP32C3-Tape-Reel-p-6471.html
- Espressif C3 chip datasheet - https://files.seeedstudio.com/wiki/Seeed-Studio-XIAO-ESP32/esp32-c3_datasheet.pdf
- XIAO C3 pinout - https://files.seeedstudio.com/wiki/XIAO_WiFi/Resources/XIAO-ESP32C3-pinout_sheet.xlsx
- XIAO C3 schematic - https://files.seeedstudio.com/wiki/XIAO_WiFi/Resources/Seeeduino-XIAO-ESP32C3-SCH.pdf

The Skull Project uses eyes made from Adafruit HalloWing M4 Express. These use the SAMD51 processor (ATSAMD51G18).
- https://www.adafruit.com/product/4300
- http://ww1.microchip.com/downloads/en/DeviceDoc/60001507E.pdf

Because the Skull Project eyes are pretty busy just displaying the eyes, I don't want to interrupt them at random times with an I2C or UART message. Thus I plan to output the position information on two ESP32-C3 Analog channels, and the SAMD51 in the eyes can sample the information at any convenient time that doesn't interrupt its processing.

## Low-Pass Filter for PWM Analog
[Top](#readme-\--analog-communication "Top")<br>
Surprise (to me) - The ESP32-C3 does not have analog outputs. It uses PWM to approximate analog outputs.
- I just realized I was looking at the Analog-to-Digital capabilities (ADC for analog input) instead of the Digital-to-Analog capabilities. The XIAO ESP32-C3 only has D10 with DAC.
- I will start by using the ESP32 LEDC library for analog output; that way I can use the same code for both analog outputs. I may need to implement filtering on the analog outputs so the SAMD51 can do reliable sensing.
- I previously did LEDC analog outputs in my https://github.com/Mark-MDO47/DuelWithBanjos project. I didn't need any filtering with the LED outputs.

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

My goal in using the PWM is twofold:
- enough "analog" capability to have 4 times the resolution as pixels in each direction
- within the above constraint, use the highest frequency PWM so that much extraneous energy is removed by the low-pass filter
