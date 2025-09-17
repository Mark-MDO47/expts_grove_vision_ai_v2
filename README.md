# expts_grove_vision_ai_v2
Experiments using Grove Vision-AI version 2 and SEEED Sensecraft

**Table Of Contents**
* [Top](#expts_grove_vision_ai_v2 "Top")
* [Module Ordering](#module-ordering "Module Ordering")
* [References](#references "References")
  * [Reset or Update Flash Memory](#reset-or-update-flash-memory "Reset or Update Flash Memory")
  * [Installing SSCMA Library](#installing-sscma-library "Installing SSCMA Library")
  * [Usage of SSCMA Library](#usage-of-sscma-library "Usage of SSCMA Library")
  * [AI Models](#ai-models "AI Models")
* [Face Following](#face-following "Face Following")

## Module Ordering
[Top](#expts_grove_vision_ai_v2 "Top")<br>
The Vision-AI V2 module can be ordered here or at several other sources. Not sure why the following two links have different prices.
- https://www.seeedstudio.com/Grove-Sensors-Grove-Vision-Al-Camera-2141.html
- https://www.seeedstudio.com/Grove-Vision-AI-Module-V2-p-5851.html

I plan to connect the Vision-AI V2 to a XIAO ESP32-C3 because it is small, capable, and I have some in my parts bin.
- https://www.seeedstudio.com/Seeed-Studio-XIAO-ESP32C3-Pre-Soldered-p-6331.html
- https://files.seeedstudio.com/wiki/Seeed-Studio-XIAO-ESP32/esp32-c3_datasheet.pdf
- https://files.seeedstudio.com/wiki/XIAO_WiFi/Resources/XIAO-ESP32C3-pinout_sheet.xlsx

Having an ESP32 with WiFi involved will allow me to use my Universal Remote - https://github.com/Mark-MDO47/UniRemote

Future plans may include a display to show the image, maybe using the ESP32-2432S028R (Cheap Yellow Display or CYD) based on ESP32-D0WDQ6 controller instead of the XIAO ESP32-C3
- https://www.aliexpress.us/item/3256805697430313.html
- Would need to transfer image
  - maybe via I2C
  - maybe once again hijack the micro-SSD to use its SPI; this time from both sides

## References
[Top](#expts_grove_vision_ai_v2 "Top")<br>
Documentation for using Vision-AI V2
- https://wiki.seeedstudio.com/grove_vision_ai_v2/
- https://wiki.seeedstudio.com/sensecraft-ai/tutorials/sensecraft-ai-pretrained-models-for-grove-vision-ai-v2/#tech-support--product-discussion
- https://www.seeedstudio.com/blog/2025/01/16/introducing-sensecraft-ai-beginner-friendly-web-based-no-code-platform-for-ai-applications/#:~:text=We've%20gone%20beyond%20just,ensuring%20a%20beginner%2Dfriendly%20experience.
  - https://www.youtube.com/watch?v=U-zRrm3-jXs
  - start this about 17:00 to see ESP32-S3-Sense demo including GPIO output
  - around 42:00 they connect an AI V2 to Arduino Uno via UART
- https://sensecraft.seeed.cc/ai/view-model/60782-person-detection-swift-yolo?tab=public
- https://github.com/HimaxWiseEyePlus/Seeed_Grove_Vision_AI_Module_V2/tree/main
- https://wiki.seeedstudio.com/No-code-Edge-AI-Tool/

### Reset or Update Flash Memory
[Top](#expts_grove_vision_ai_v2 "Top")<br>
https://wiki.seeedstudio.com/grove_vision_ai_v2/ search for **Boot / Reset / Flashed Driver** or **Bootloader Recovery Tool Manual**

### Installing SSCMA Library
[Top](#expts_grove_vision_ai_v2 "Top")<br>
Seeed SenseCraft Model Assistant (SSCMA) is described in https://wiki.seeedstudio.com/ModelAssistant_Introduce_Overview/<br>
I will use this library to communicate with the Grove Vision-AI V2. 

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

### Usage of SSCMA Library
[Top](#expts_grove_vision_ai_v2 "Top")<br>
When called without parameters, the SSCMA::begin() function typically uses a default I2C interface, assuming the hardware is configured for it. The library is designed to work with Seeed Studio's hardware, and the no-parameter version of begin() provides a convenient way to initialize the communication interface for devices that use a standard I2C connection, such as the Grove Vision-AI V2.<br>
For example, when using the Grove Vision-AI V2, the begin() function with no arguments:
- Initializes the I2C communication protocol using the default Wire object.
- Uses the default I2C address (I2C_ADDRESS) to identify and communicate with the device.


### AI Models
[Top](#expts_grove_vision_ai_v2 "Top")<br>
There are several ways to get a model into the Vision-AI V2 module; below are some of them I have found

#### SenseCraft
[Top](#expts_grove_vision_ai_v2 "Top")<br>
SenseCraft - https://wiki.seeedstudio.com/sensecraft-ai/overview/
- SenseCraft has some SSCMA models available here (via json files) - https://github.com/Seeed-Studio/sscma-model-zoo

#### Edge Impulse
[Top](#expts_grove_vision_ai_v2 "Top")<br>
Edge Impulse - https://wiki.seeedstudio.com/edgeimpulse/
- https://studio.edgeimpulse.com/signup

#### HimaxWiseEyePlus
[Top](#expts_grove_vision_ai_v2 "Top")<br>
HimaxWiseEyePlus - https://github.com/HimaxWiseEyePlus/Seeed_Grove_Vision_AI_Module_V2
- There is a model zoo here - https://github.com/HimaxWiseEyePlus/Seeed_Grove_Vision_AI_Module_V2/tree/main/model_zoo
- There is a way to debug models on the Vision-AI V1 - https://github.com/HimaxWiseEyePlus/Seeed_Grove_Vision_AI_Module_V2/tree/main/swd_debugging

### Ultralytics
[Top](#expts_grove_vision_ai_v2 "Top")<br>
Ultralytics seems to concentrate on vision models.
- Seems to allow moving trained models to different formats for implementation on inexpensive hardware.
- They also have a cool Ultralytics AP that allows you to run it on your smart phone (either type).
- Ultralytics is especially interesting to me since I can download the training software and (slowly) train on my own equipment.
  - I am not anxious to (for instance) upload photos or voice captures of my family to the internet.

Here are some entries to the Ultralytics world:
- https://www.ultralytics.com/
- https://github.com/ultralytics
- https://github.com/ultralytics/ultralytics
- https://hub.ultralytics.com/home - free-level account available
- https://www.youtube.com/watch?v=hHyHmOtmEgs&list=PL1FZnkj4ad1PFJTjW4mWpHZhzgJinkNV0&index=46 - this person tracking seems ideally suited to what I have in mind

### Any model export (e.g. Ultralytics) then through SenseCraft
[Top](#expts_grove_vision_ai_v2 "Top")<br>
NOTE: Due to the size limitation, currently both XIAO ESP32S3 and Grove Vision AI V2 only support int8 format models.

To deploy an Ultralytics model to a Seeed Grove Vision AI V2, you must convert the model to the specific  format required by the device's Himax WiseEye2 processor. The deployment process is managed by Seeed Studio's SenseCraft AI platform, which handles the flashing of the converted model onto the hardware. [1, 2, 3, 4]

#### Export your Ultralytics model 
[Top](#expts_grove_vision_ai_v2 "Top")<br>
First, export your custom-trained or standard Ultralytics model (e.g., YOLOv8) to the ONNX format. This is done from your Python training environment or notebook using the Ultralytics export function. [5, 6]
```
from ultralytics import YOLO

# Load a trained model
model = YOLO('yolov8n.pt')  # or use your own custom trained model

# Export the model to ONNX format
model.export(format='onnx', opset=12) 
```
#### Convert ONNX to int8_vela.tflite
[Top](#expts_grove_vision_ai_v2 "Top")<br>
Use the SenseCraft Model Assistant, a Google Colab-based tool provided by Seeed Studio, to convert your ONNX model to the specific  format. 

1. Open the SenseCraft Model Assistant Colab notebook linked in the Seeed Studio Wiki. 
1. Follow the notebook's instructions to upload your exported ONNX model. 
1. The notebook will perform the necessary quantization and conversion steps, producing a file with the int8_vela.tflite extension. 
1. Download the converted  model file to your computer. [1, 5]

#### Use SenseCraft AI to deploy the model 
[Top](#expts_grove_vision_ai_v2 "Top")<br>
With the converted model, you can now use the SenseCraft AI platform to flash it to your device. 

1. Connect your Grove Vision AI V2 to your computer using a USB-C cable. 
1. Navigate to the SenseCraft AI Model Assistant webpage in your browser. 
1. In the web interface, click on Device Workspace, then select Grove - Vision AI V2. 
1. Click the Connect button and select the serial port for your device from the pop-up window. 
1. After connecting, select the option to Upload Custom AI Model. 
1. You will be prompted to provide the model name, your  model file, and the list of labels used for your dataset. 
1. Click Send Model to begin the upload process. The flashing can take several minutes. [3, 7, 8, 9]  

#### Test and view results 
[Top](#expts_grove_vision_ai_v2 "Top")<br>
Once the upload is complete, the SenseCraft web interface should automatically display the camera's live feed with your model's inference results overlaid on the video. [9]  

#### References
[Top](#expts_grove_vision_ai_v2 "Top")<br>
- [1] https://wiki.seeedstudio.com/grove_vision_ai_v2_sscma/
- [2] https://docs.edgeimpulse.com/docs/edge-ai-hardware/mcu-+-ai-accelerators/himax-seeed-grove-vision-ai-module-v2-wise-eye-2
- [3] https://wiki.seeedstudio.com/grove_vision_ai_v2_sscma/
- [4] https://www.seeedstudio.com/blog/2020/11/02/the-things-indoor-gateway-gets-started-with-sensecap-sensor/
- [5] https://wiki.seeedstudio.com/grove_vision_ai_v2_sscma/
- [6] https://github.com/ultralytics/ultralytics/issues/6676
- [7] https://wiki.seeedstudio.com/Vision_AI_with_Customizable_Models/
- [8] https://docs.petoi.com/extensible-modules/advanced-development-and-application-of-ai-vision-modules/model-deployment
- [9] https://wiki.seeedstudio.com/sensecraft-ai/tutorials/sensecraft-ai-pretrained-models-for-grove-vision-ai-v2/

## Face Following
[Top](#expts_grove_vision_ai_v2 "Top")<br>
There is a demo project that does face following with a fan:
- https://wiki.seeedstudio.com/grove_vision_ai_v2_demo/ search for **Project I: Create a Face-Tracking Fan**

My first usage will be to add face following to my Skull Project https://github.com/Mark-MDO47/Skull-Project. We want to make the eyes follow the face detected by the Vision-AI V2.

The Skull Project uses eyes made from Adafruit HalloWing M4 Express. These use the SAMD51 processor (ATSAMD51G18).
- https://www.adafruit.com/product/4300
- http://ww1.microchip.com/downloads/en/DeviceDoc/60001507E.pdf

Because the Skull Project eyes are pretty busy just displaying the eyes, I don't want to interrupt them at random times with an I2C or UART message. Thus I plan to output the position information on two ESP32-C3 Analog channels, and the SAMD51 in the eyes can sample the information at any convenient time that doesn't interrupt its processing.
