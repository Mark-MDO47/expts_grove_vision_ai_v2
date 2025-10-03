# README - Hardware
This contains information about the new AI Vision sytem being added to the Skull Project.

For information about the Skull Project and its Adafruit HalloWing M4 Express using the ATSAMD51 MCU
- https://github.com/Mark-MDO47/Skull-Project

**Table Of Contents**
* [Top](#readme-\--hardware "Top")
* [Vision-AI V2](#vision\-ai-v2 "Vision-AI V2")
* [XIAO ESP32-C3](#xiao-esp32\-c3 "XIAO ESP32-C3")
* [OV5647 Camera Module](#ov5647-camera-module "OV5647 Camera Module")
* [XIAO Connector On Vision-AI V2](#xiao-connector-on-vision\-ai-v2 "XIAO Connector On Vision-AI V2")
* [Future Possibilities](#future-possibilities "Future Possibilities")

## Vision-AI V2
[Top](#readme-\--hardware "Top")<br>
The Vision-AI V2 module can be ordered here or at several other sources, either as just the module or as a Kit including camera and ESP32-C3.
- Vision-AI V2 only - https://www.seeedstudio.com/Grove-Vision-AI-Module-V2-p-5851.html
- Vision-AI V2 kit - https://www.seeedstudio.com/Grove-Vision-AI-V2-Kit-p-5852.html
- Himax chip datasheet - https://files.seeedstudio.com/wiki/grove-vision-ai-v2/HX6538_datasheet.pdf
- Vision-AI V2 schematic - https://files.seeedstudio.com/wiki/grove-vision-ai-v2/Grove_Vision_AI_Module_V2_Circuit_Diagram.pdf
- Vision-AI V2 layout - https://files.seeedstudio.com/wiki/grove-vision-ai-v2/Grove_Vision_AI_Module_V2_Layout.zip
- EXCELLENT LIST of detailed documents for Vision-AI-  https://forum.seeedstudio.com/t/a-collection-of-useful-links-for-those-developing-applications-for-grove-vision-ai-v2/280236

## XIAO ESP32-C3
[Top](#readme-\--hardware "Top")<br>
I plan to connect the Vision-AI V2 to a XIAO ESP32-C3 because it is small, capable, and I have some in my parts bin. Also, the XIAO ESP32-C3 is used in the Vision-AI V2 Kit above.
- XIAO ESP32-C3 "soldered" - https://www.seeedstudio.com/Seeed-Studio-XIAO-ESP32C3-Pre-Soldered-p-6331.html
- XIAO ESP32-C3 "tape & reel" - https://www.seeedstudio.com/Seeed-Studio-XIAO-ESP32C3-Tape-Reel-p-6471.html
- XIAO ESP32-C3 WiFi 2.4GHz antenna - https://www.seeedstudio.com/2-4GHz-FPC-Antenna-2-9dBi-for-XIAO-ESP32C3-p-6439.html
- getting started with XIAO C3 - https://wiki.seeedstudio.com/XIAO_ESP32C3_Getting_Started/
  - includes a list of "strapping pins" that we won't use: GPIOs 2, 8 and 9 - same as **D0**, D8 and D9 (strange???)
  - includes hints on connecting a 3.7V lithium battery
- Which GPIOs to use and notes on strapping pins - https://pcbartists.com/design/embedded/esp32-c3-gpio-notes-strapping-pins/
- First Look - definitely worth a read - https://sigmdel.ca/michel/ha/xiao/xiao_esp32c3_intro_en.html
- Espressif C3 chip datasheet - https://files.seeedstudio.com/wiki/Seeed-Studio-XIAO-ESP32/esp32-c3_datasheet.pdf
- XIAO C3 pinout - https://files.seeedstudio.com/wiki/XIAO_WiFi/Resources/XIAO-ESP32C3-pinout_sheet.xlsx
- XIAO C3 schematic - https://files.seeedstudio.com/wiki/XIAO_WiFi/Resources/Seeeduino-XIAO-ESP32C3-SCH.pdf

Having an ESP32 with WiFi available will allow me to use my Universal Remote - https://github.com/Mark-MDO47/UniRemote

## OV5647 Camera Module
[Top](#readme-\--hardware "Top")<br>
The OV5647 camera module is also available separately with different fisheye lense configurations; several are shown here. I have the ones from Amazon; both -62 and -160/95deg work with Vision-AI V2.
- OV5647-62 module - https://www.seeedstudio.com/OV5647-69-1-FOV-Camera-module-for-Raspberry-Pi-3B-4B-p-5484.html
- OV5647-160 module - https://www.seeedstudio.com/OV5647-160-FOV-IR-Camera-module-for-Raspberry-Pi-3B-4B-p-5485.html
- OV5647-62 module - https://www.amazon.com/dp/B012V1HEP4?th=1
- OV5647-160 (various) - https://www.amazon.com/dp/B0D3X1VJCC?th=1
- OV5647-62 module datasheet - https://files.seeedstudio.com/wiki/OV5647_Series_Camera_Module/OV5647-62.pdf
- OV5647-160 module datasheet - https://files.seeedstudio.com/wiki/OV5647_Series_Camera_Module/OV5647-160_FOV_IR_Camera_module.pdf
- OV5647 chip spec - https://github.com/SeeedDocument/Raspberry_Pi_Camera_Module/raw/master/res/ov5647_full.pdf
- NOTE: camera connection via cable - several images in SEEED documentation show cable orientation WRONG - connect as per the GIF
  - Blue strip visible when inserting in connector
  - https://files.seeedstudio.com/wiki/grove-vision-ai-v2/9.gif

## XIAO Connector On Vision-AI V2
[Top](#readme-\--hardware "Top")<br>
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
- GND:
  - Instead of pulling ground from the pin on this connector, I plan to power via XIAO USB and distribute ground from there

## Future Possibilities
[Top](#readme-\--hardware "Top")<br>
Future plans may include a display to show the image, maybe using the ESP32-2432S028R (Cheap Yellow Display or CYD) based on ESP32-D0WDQ6 controller instead of the XIAO ESP32-C3
- https://www.aliexpress.us/item/3256805697430313.html
- Would need to transfer image
  - maybe via I2C or UART
    - https://wiki.seeedstudio.com/grove_vision_ai_v2_rs485/
    - https://wiki.seeedstudio.com/grove_vision_ai_v2_at/
    - https://wiki.seeedstudio.com/grove_vision_ai_v2_at/#base64tojpeg
  - maybe once again hijack the micro-SSD to use its SPI; this time from both sides

