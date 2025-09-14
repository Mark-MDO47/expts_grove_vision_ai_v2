# expts_grove_vision_ai_v2
Experiments using Grove Vision AI version 2 and SEEED Sensecraft

**Table Of Contents**
* [Top](#expts_grove_vision_ai_v2 "Top")
* [Module Ordering](#module-ordering "Module Ordering")
* [References](#references "References")
* [Installing SSCMA Library](#installing-sscma-library "Installing SSCMA Library")
* [AI Models](#ai-models "AI Models")

## Module Ordering
[Top](#expts_grove_vision_ai_v2 "Top")<br>
The Vision-AI V2 module can be ordered here or at several other sources. Not sure why the following two links have different prices.
- https://www.seeedstudio.com/Grove-Sensors-Grove-Vision-Al-Camera-2141.html
- https://www.seeedstudio.com/Grove-Vision-AI-Module-V2-p-5851.html


## References
[Top](#expts_grove_vision_ai_v2 "Top")<br>
These are to save pointers to documentation.

Documentation for using Vision-AI V2
- https://wiki.seeedstudio.com/grove_vision_ai_v2/
- https://wiki.seeedstudio.com/sensecraft-ai/tutorials/sensecraft-ai-pretrained-models-for-grove-vision-ai-v2/#tech-support--product-discussion
- https://www.seeedstudio.com/blog/2025/01/16/introducing-sensecraft-ai-beginner-friendly-web-based-no-code-platform-for-ai-applications/#:~:text=We've%20gone%20beyond%20just,ensuring%20a%20beginner%2Dfriendly%20experience.
  - https://www.youtube.com/watch?v=U-zRrm3-jXs
  - start this about 17:00 to see ESP32-S3-Sense demo including GPIO output
  - around 42:00 they connect an AI V2 to UART to Arduino Uno
- https://sensecraft.seeed.cc/ai/view-model/60782-person-detection-swift-yolo?tab=public
- https://github.com/HimaxWiseEyePlus/Seeed_Grove_Vision_AI_Module_V2/tree/main
- https://wiki.seeedstudio.com/No-code-Edge-AI-Tool/

## Installing SSCMA Library
[Top](#expts_grove_vision_ai_v2 "Top")<br>
Seeed SenseCraft Model Assistant (SSCMA) is described in https://wiki.seeedstudio.com/ModelAssistant_Introduce_Overview/<br>
I will use this library to communicate with the Grove Vision AI V2. 

https://github.com/Seeed-Studio/Seeed_Arduino_SSCMA says to download a zip file and add the library to your Arduino IDE by selecting **Sketch > Include Library > Add .ZIP Library**
- They don't explicitly say it but they expect you to click on the green **Code** button and choose **Download ZIP**
- Then you point the Arduino IDE to that ZIP file.

The SSCMA library is alternatively now available by searching in the Arduino IDE library manager:
  - Go to **Tools > Manage Libraries.**
  - Search for and install **Seeed_Arduino_SSCMA**
 
Look in https://github.com/Seeed-Studio/Seeed_Arduino_SSCMA/blob/main/src/Seeed_Arduino_SSCMA.h to see available options in class SSCMA.
- **SSCMA** methods start after **public:**.
  - Has initialization routines for I2C (TwoWire), SPI, or UART communication. UART baud rate is 921,600.
- **AT**-style commands start near **CMD_AT_ID**

## AI Models
[Top](#expts_grove_vision_ai_v2 "Top")<br>
There are two supported ways to get a model into the Vision-AI V2 module
- SenseCraft - https://wiki.seeedstudio.com/sensecraft-ai/overview/
- Edge Impulse - https://wiki.seeedstudio.com/edgeimpulse/
  - https://studio.edgeimpulse.com/signup

SenseCraft has some SSCMA models available here (via json files) - https://github.com/Seeed-Studio/sscma-model-zoo
