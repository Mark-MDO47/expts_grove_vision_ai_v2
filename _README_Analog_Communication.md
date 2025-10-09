# README - Analog Communication
In these experiments I will communicate location data from an XAIO ESP32-C3 to two @ Adafruit HalloWing M4 Express (my Skull Project).

**Table Of Contents**
* [Top](#readme-\--analog-communication "Top")
* [Useful Documentation](#useful-documentation "Useful Documentation")
* [Low-Pass Filter for ESP32-C3 PWM Analog](#low\-pass-filter-for-esp32\-c3-pwm-analog "Low-Pass Filter for ESP32-C3 PWM Analog")
  * [ESP32-C3 does not have Analog Outputs](#esp32\-c3-does-not-have-analog-outputs "ESP32-C3 does not have Analog Outputs")
  * [Parameters for a good Low Pass Filter](#parameters-for-a-good-low-pass-filter "Parameters for a good Low Pass Filter")
  * [PWM Frequency and Signal Accuracy](#pwm-frequency-and-signal-accuracy "PWM Frequency and Signal Accuracy")
  * [HalloWing M4 Express Display and Frequency and Resolution](#hallowing-m4-express-display-and-frequency-and-resolution "HalloWing M4 Express Display and Frequency and Resolution")
  * [HalloWing M4 Express SAMD51 Reads the Analog Signal](#hallowing-m4-express-samd51-reads-the-analog-signal "HalloWing M4 Express SAMD51 Reads the Analog Signal")
  * [HalloWing M4 Express Pins to Use](#hallowing-m4-express-pins-to-use "HalloWing M4 Express Pins to Use")
  * [HalloWing M4 Express AREF](#hallowing-m4-express-aref "HalloWing M4 Express AREF")

## Useful Documentation
[Top](#readme-\--analog-communication "Top")<br>
The XIAO ESP32-C3 is small, capable, and I have some in my parts bin. Also it works with the "XIAO connector" on the Vision-AI V2.
- XIAO ESP32-C3 "soldered" - https://www.seeedstudio.com/Seeed-Studio-XIAO-ESP32C3-Pre-Soldered-p-6331.html
- XIAO ESP32-C3 "tape & reel" - https://www.seeedstudio.com/Seeed-Studio-XIAO-ESP32C3-Tape-Reel-p-6471.html
- Espressif C3 chip datasheet - https://files.seeedstudio.com/wiki/Seeed-Studio-XIAO-ESP32/esp32-c3_datasheet.pdf
- XIAO C3 pinout - https://files.seeedstudio.com/wiki/XIAO_WiFi/Resources/XIAO-ESP32C3-pinout_sheet.xlsx
- XIAO C3 schematic - https://files.seeedstudio.com/wiki/XIAO_WiFi/Resources/Seeeduino-XIAO-ESP32C3-SCH.pdf

The Skull Project uses eyes made from Adafruit HalloWing M4 Express. These use the SAMD51 processor (ATSAMD51J19).
- https://www.adafruit.com/product/4300
- http://ww1.microchip.com/downloads/en/DeviceDoc/60001507E.pdf

Because the Skull Project eyes are pretty busy just displaying the eyes, I don't want to interrupt them at random times with an I2C or UART message. Thus I plan to output the position information on two ESP32-C3 Analog channels, and the SAMD51 in the eyes can sample the information at any convenient time that doesn't interrupt its processing.

## Low-Pass Filter for ESP32-C3 PWM Analog
[Top](#readme-\--analog-communication "Top")<br>

### ESP32-C3 does not have Analog Outputs
[Top](#readme-\--analog-communication "Top")<br>
Surprise (to me) - The ESP32-C3 does not have analog outputs. It uses PWM to approximate analog outputs.
- I realized I was looking at the Analog-to-Digital capabilities (ADC for analog input) instead of the Digital-to-Analog capabilities. The XIAO ESP32-C3 only has D10 with DAC.
- I will start by using the ESP32 LEDC library for analog output; that way I can use the same code for both analog outputs. I may need to implement filtering on the analog outputs so the SAMD51 can do reliable sensing.
- I previously did LEDC analog outputs in my https://github.com/Mark-MDO47/DuelWithBanjos project. I didn't need any filtering with the LED outputs.

### Parameters for a good Low Pass Filter
[Top](#readme-\--analog-communication "Top")<br>
Got these from Google search
- Low Pass/High Pass Filter Calculator - https://www.digikey.com/en/resources/conversion-calculators/conversion-calculator-low-pass-and-high-pass-filter
- Time Constant Calculator - https://www.digikey.com/en/resources/conversion-calculators/conversion-calculator-time-constant

Using the above two calculators for a simple R/C filter, I think this will work (using realistic component values)
| Parameter | Value | Formula |
| --- | --- | --- |
| Resistance | 4.6 K Ohm | N/A |
| Capacitance | 1 microFarad | N/A |
| Time Constant | 4.6 milliSec | TC = Resistance * Capacitance |
| Cutoff Frequency (-3dB) | 28.9 Hz | Fc = 1 / (2 * PI * Resistance * Capacitance) |

The Time Constant is such that after a change of one voltage value to another, 1 time constant later the value has moved 63% of the distance. At 5 time constants it is about 99% of the way there.

The Cutoff Frequency is at -3dB, which means that at that frequency and above the amplitude is reduce by 50% or more.

My goal in using the PWM is twofold:
- enough "analog" capability to have 4 times the resolution as pixels in each direction
- within the above constraint, use the highest frequency PWM so that much extraneous energy is removed by the low-pass filter

Here are some Oscilloscope captures of an experimental setup of the XIAO ESP32-C3 PWM Analog Output with Low Pass Filter as defined above.

| Photo | Photo |
| --- | --- |
| 100% Rise<br><img src="https://github.com/Mark-MDO47/expts_grove_vision_ai_v2/blob/master/resources/images/LowPass_100pctRise.jpg" width="400" alt="XIAO ESP32-C3 PWM Analog Output with Low Pass Filter - 100% Rise"> | 100% Fall<br><img src="https://github.com/Mark-MDO47/expts_grove_vision_ai_v2/blob/master/resources/images/LowPass_100pctFall.jpg" width="400" alt="XIAO ESP32-C3 PWM Analog Output with Low Pass Filter - 100% Fall"> |
| 25% Rise<br><img src="https://github.com/Mark-MDO47/expts_grove_vision_ai_v2/blob/master/resources/images/LowPass_25pctRise.jpg" width="400" alt="XIAO ESP32-C3 PWM Analog Output with Low Pass Filter - 25% Rise"> | Experimental Setup<br><img src="https://github.com/Mark-MDO47/expts_grove_vision_ai_v2/blob/master/resources/images/LowPass_ExptSetup.jpg" width="400" alt="XIAO ESP32-C3 PWM Analog Output with Low Pass Filter - Experimental Setup"> |

### PWM Frequency and Signal Accuracy
[Top](#readme-\--analog-communication "Top")<br>
Did a little more Google search

The Xiao ESP32-C3's PWM frequencies are flexible, with the LEDC peripheral supporting a wide range, from as low as 10Hz up to 40MHz. However, practical use often involves higher frequencies at lower resolutions for better stability and accuracy, with frequencies above ~300kHz often yielding less accurate outputs. 

**Frequency Range & Factors**
- Theoretical Maximum: The ESP32-C3's LEDC peripheral can generate PWM signals up to 40MHz, derived from an 80MHz clock source.
- Practical Limits: While the 40MHz theoretical maximum exists, achieving this level of performance requires a small bit depth and may lead to instability.
- Resolution vs. Frequency: A higher PWM frequency generally requires a lower resolution (fewer possible duty cycle steps). For example, if a counter has 10-bit resolution (1024 steps), the maximum frequency would be 40MHz / 1024 or approximately 38kHz.
- Stability: For applications requiring high precision or audio quality, frequencies are often set lower to ensure good output accuracy.

**Supported Range of LED PWM Frequency and Duty Resolutions**
The LED PWM Controller is designed primarily to drive LEDs. It provides a large flexibility of PWM duty cycle settings. For instance, the PWM frequency of 5 kHz can have the **theoretical** maximum duty resolution of 13 bits. This means that the duty can be set anywhere from 0 to 100% with a resolution of ~ 0.012% (2 ** 13 = 8192 discrete levels of the LED intensity).
- **practical experience with XIAO ESP32-C3** - I can attach to LEDC library with 5 kHz at up to 12 bits resolution, but it will not attach at 13 bits.

### HalloWing M4 Express Display and Frequency and Resolution
[Top](#readme-\--analog-communication "Top")<br>
The HalloWing M4 Express has a 1.54" 240x240 full color IPS TFT.

My goals are
- At least 4*240 = 960 discrete levels of analog signal. Less than 1024 (nearest higher power of 2).
- Use highest practical PWM frequency that supports this so that low-pass filter removes most of the extraneous energy.

Since 5 kHz seems like a practical upper limit on PWM frequency for stability and that provides 4096 discrete levels, I will use 5 kHz frequency.

### HalloWing M4 Express SAMD51 Reads the Analog Signal
[Top](#readme-\--analog-communication "Top")<br>
Information from SAM_D5x_E5x_DataSheet_60001507E.pdf - http://ww1.microchip.com/downloads/en/DeviceDoc/60001507E.pdf

Dual 12-bit, 1 MSPS Analog-to-Digital Converter (ADC) with up to 16 channels each:
–	Differential and single-ended input
–	Automatic offset and gain error compensation
–	Oversampling and decimation in hardware to support 13-bit, 14-bit, 15-bit, or 16-bit resolution

45. ADC – Analog-to-Digital Converter
45.1 Overview
The Analog-to-Digital Converter (ADC) converts analog signals to digital values. The ADC has up to 12-bit resolution, and is capable of a sampling rate of up to 1MSPS. The input selection is flexible, and both differential and single-ended measurements can be performed. In addition, several internal signal inputs are available. The ADC can provide both signed and unsigned results.

ADC measurements can be started by either application software or an incoming event from another peripheral in the device. ADC measurements can be started with predictable timing, and without software intervention.
Both internal and external reference voltages can be used.

An integrated temperature sensor is available for use with the ADC. The bandgap voltage, as well as the scaled I/O and core voltages, can also be measured by the ADC.

The ADC has a compare function for accurate monitoring of user-defined thresholds, with minimum software intervention required.

The ADC can be configured for 8-, 10- or 12-bit results. ADC conversion results are provided left- or right-adjusted, which eases calculation when the result is represented as a signed value.

It is possible to use DMA to move ADC results directly to memory or peripherals when conversions are done.

The SAM D5x/E5x has two ADC instances, ADC0 and ADC1. The two inputs can be sampled simultaneously, as each ADC includes sample and hold circuits.

Note: When the Peripheral Touch Controller (PTC) is enabled, ADC0 is serving the PTC exclusively. In this case, ADC0 cannot be used by the user application.
- Fortunately, the PTC is not used for touch sensing with the Hallowing M4 eyes software; it uses normal digital input with timing for touch sensing.
- The Skull Project software is found here in directory mdo_m4_skull_project (forked from Adafruit)
  - https://github.com/Mark-MDO47/mdo_m4_eyes
- the bulk of my mods is in mdo_skull_project.cpp

### HalloWing M4 Express Pins to Use
[Top](#readme-\--analog-communication "Top")<br>
Near the on/off switch there are touch pads labeled A2 through A5. I will use A3 and A4, but connect through the header.
- https://learn.adafruit.com/adafruit-hallowing-m4/pinouts

A2 is used for a touch control, the so-called "boop" button that causes the eyes to cross.
- The code does some early measurements to find a threshold + 10% margin for the pin without a touch
- readBoop() sets A2 HIGH (pulls some electrons from the pin) then measures how long for it to refill.
- If a finger is touching, there was more capacitance so more electrons needed to refill -> takes longer

```C
// don't overthink the following line; it just makes a constant int identifying A2
GLOBAL_VAR int8_t  boopPin             GLOBAL_INIT(A2);

static inline uint16_t readBoop(void) {
  uint16_t counter = 0;
  pinMode(boopPin, OUTPUT);
  digitalWrite(boopPin, HIGH);
  pinMode(boopPin, INPUT);
  while(digitalRead(boopPin) && (++counter < 1000));
  return counter;
}
```

A3 through A5 are available for use; I will use A3 and A4.

This leaves A5 available if I want to do something with blinking (blinkPin).

### HalloWing M4 Express AREF
[Top](#readme-\--analog-communication "Top")<br>
On the HalloWing M4 Express, the AREF is not hard-jumpered to the internal 3.3V, so the external AREF pin can be used.

Normal analogRead() will use the internal 3.3V. I power them through the USB port so this is probably good enough, but we will see.

To use the ARef pin for a non-3.3V analog reference, the code to use is analogReference(AR_EXTERNAL) (it's AR_EXTERNAL not EXTERNAL)
- see note in https://learn.adafruit.com/adafruit-hallowing-m4?view=all
