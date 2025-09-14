# expts_grove_vision_ai_v2
Experiments using Grove Vision AI version 2 and SEEED Sensecraft

**Table Of Contents**
* [Top](#expts_grove_vision_ai_v2 "Top")
* [References](#references "References")
* [Installing SSCMA Library](#installing-sscma-library "Installing SSCMA Library")

## References
[Top](#expts_grove_vision_ai_v2 "Top")<br>
These are to save pointers to documentation.

The Vision-AI V2 module itself. Not sure why these have different prices.
- https://www.seeedstudio.com/Grove-Sensors-Grove-Vision-Al-Camera-2141.html
- https://www.seeedstudio.com/Grove-Vision-AI-Module-V2-p-5851.html

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
https://github.com/Seeed-Studio/Seeed_Arduino_SSCMA says to download a zip file and add the library to your Arduino IDE by selecting **Sketch > Include Library > Add .ZIP Library**
- This seems out of date. I cannot find a *.zip file using the pointer.
- Also the SSCMA library is now available by searching in the library manager
  - Go to **Tools > Manage Libraries.**
  - Search for and install **Seeed_Arduino_SSCMA**
