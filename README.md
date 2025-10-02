# expts_grove_vision_ai_v2
Experiments using Grove Vision-AI version 2 and SEEED Sensecraft

**Table Of Contents**
* [Top](#expts_grove_vision_ai_v2 "Top")
* [Module Ordering and Pinouts](#module-ordering-and-pinouts "Module Ordering and Pinouts")
  * [Vision-AI V2](#vision\-ai-v2 "Vision-AI V2")
  * [XIAO ESP32-C3](#xiao-esp32\-c3 "XIAO ESP32-C3")
  * [XIAO Connector On Vision-AI V2](#xiao-connector-on-vision-ai-v2 "XIAO Connector On Vision-AI V2")
  * [OV5647 Camera Module](#ov5647-camera-module "OV5647 Camera Module")
  * [Future Possibilities](#future-possibilities "Future Possibilities")
* [References](#references "References")
  * [Reset or Update Flash Memory](#reset-or-update-flash-memory "Reset or Update Flash Memory")
  * [Installing Seeed_Arduino_SSCMA Communication Library into Arduino IDE](#installing-seeed_arduino_sscma-communication-library-into-arduino-ide "Installing Seeed_Arduino_SSCMA Communication Library into Arduino IDE")
  * [Usage of Seeed_Arduino_SSCMA Library](#usage-of-seeed_arduino_sscma-library "Usage of Seeed_Arduino_SSCMA Library")
  * [AI Models](#ai-models "AI Models")
    * [SenseCraft](#sensecraft "SenseCraft")
    * [Edge Impulse](#edge-impulse "Edge Impulse")
    * [HimaxWiseEyePlus](#himaxwiseeyeplus "HimaxWiseEyePlus")
    * [Ultralytics](#ultralytics "Ultralytics")
* [Any Model Export - example Ultralytics - then through SenseCraft](#any-model-export-\--example-ultralytics-\--then-through-sensecraft "Any Model Export - example Ultralytics - then through SenseCraft")
  * [Export an Ultralytics Model](#export-an-ultralytics-model "Export an Ultralytics Model")
  * [Convert ONNX to int8_vela.tflite](#convert-onnx-to-int8_velatflite "Convert ONNX to int8_vela.tflite")
  * [Use SenseCraft AI to deploy the model](#use-sensecraft-ai-to-deploy-the-model "Use SenseCraft AI to deploy the model")
  * [Test and view results](#test-and-view-results "Test and view results")
  * [References](#references "References")
* [Experiment 01 - Face Following](#experiment-01-\--face-following "Experiment 01 - Face Following")
  * [Experiment 01 Introduction](#experiment-01-introduction "Experiment 01 Introduction")

## Module Ordering and Pinouts
[Top](#expts_grove_vision_ai_v2 "Top")<br>

### Vision-AI V2
[Top](#expts_grove_vision_ai_v2 "Top")<br>
The Vision-AI V2 module can be ordered here or at several other sources, either as just the module or as a Kit including camera and ESP32-C3.
- Vision-AI V2 only - https://www.seeedstudio.com/Grove-Vision-AI-Module-V2-p-5851.html
- Vision-AI V2 kit - https://www.seeedstudio.com/Grove-Vision-AI-V2-Kit-p-5852.html
- Himax chip datasheet - https://files.seeedstudio.com/wiki/grove-vision-ai-v2/HX6538_datasheet.pdf
- Vision-AI V2 schematic - https://files.seeedstudio.com/wiki/grove-vision-ai-v2/Grove_Vision_AI_Module_V2_Circuit_Diagram.pdf
- Vision-AI V2 layout - https://files.seeedstudio.com/wiki/grove-vision-ai-v2/Grove_Vision_AI_Module_V2_Layout.zip
- EXCELLENT LIST of detailed documents for Vision-AI-  https://forum.seeedstudio.com/t/a-collection-of-useful-links-for-those-developing-applications-for-grove-vision-ai-v2/280236

### XIAO ESP32-C3
[Top](#expts_grove_vision_ai_v2 "Top")<br>
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

### XIAO Connector On Vision-AI V2
[Top](#expts_grove_vision_ai_v2 "Top")<br>
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

### OV5647 Camera Module
[Top](#expts_grove_vision_ai_v2 "Top")<br>
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

### Future Possibilities
Future plans may include a display to show the image, maybe using the ESP32-2432S028R (Cheap Yellow Display or CYD) based on ESP32-D0WDQ6 controller instead of the XIAO ESP32-C3
- https://www.aliexpress.us/item/3256805697430313.html
- Would need to transfer image
  - maybe via I2C or UART
    - https://wiki.seeedstudio.com/grove_vision_ai_v2_rs485/
    - https://wiki.seeedstudio.com/grove_vision_ai_v2_at/
    - https://wiki.seeedstudio.com/grove_vision_ai_v2_at/#base64tojpeg
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

### Installing Seeed_Arduino_SSCMA Communication Library into Arduino IDE
[Top](#expts_grove_vision_ai_v2 "Top")<br>
Be aware that there are three things related to Seeed SenseCraft Model Assistant and referred to as SSCMA
1. https://github.com/Seeed-Studio/Seeed_Arduino_SSCMA - Seeed_Arduino_SSCMA - a library for use in Arduino IDE to assist in communicating with AI models running on a different hardware module - included in XIAO ESP32-C3 code
1. https://github.com/Seeed-Studio/SSCMA-Micro - SSCMA-Micro - a cross-platform machine learning inference framework - implements digital image processing, neural network inferencing, AT command interaction, and more - included in Vision-AI V2 code
1. https://wiki.seeedstudio.com/ModelAssistant_Introduce_Overview - Seeed SenseCraft (AI) Model Assistant - an open-source project focused on embedded AI including tools and a model zoo - on the web

I will use the Seeed_Arduino_SSCMA library on the XIAO ESP32-C3 to communicate with the Grove Vision-AI V2 which is using SSCMA-Micro. I will use Seeed SenseCraft (AI) Model Assistant to load my vision models onto the Vision-AI V2

https://github.com/Seeed-Studio/Seeed_Arduino_SSCMA says to download a zip file and add the library to your Arduino IDE by selecting **Sketch > Include Library > Add .ZIP Library**
- They don't explicitly say it but they expect you to click on the green **Code** button and choose **Download ZIP**
- Then you point the Arduino IDE to that ZIP file.

The Seeed_Arduino_SSCMA library is alternatively now available by searching in the Arduino IDE library manager:
  - Go to **Tools > Manage Libraries.**
  - Search for and install **Seeed_Arduino_SSCMA**
 
Look in https://github.com/Seeed-Studio/Seeed_Arduino_SSCMA/blob/main/src/Seeed_Arduino_SSCMA.h to see available options in class SSCMA.
- **SSCMA** methods start after **public:**.
  - Has initialization routines for I2C (TwoWire), SPI, or UART communication. UART baud rate is 921,600, I2C is either 100KHz or 400KHz.
- **AT**-style commands start near **CMD_AT_ID**
  - AT commands wiki - https://wiki.seeedstudio.com/grove_vision_ai_v2_at/
  - AT protocol documentation - https://github.com/Seeed-Studio/SSCMA-Micro/blob/1.0.x/docs/protocol/at_protocol.md

According to ChatGPT-5 the speed difference between I2C and UART with SSCMA (SenseCraft Smart Camera Middleware API) on the Grove Vision-AI V2 is significant.
- I2C speed
  - Runs at standard 100 kHz or fast 400 kHz bus speeds (configurable).
  - Effective throughput: ~20–30 KB/s max at 400 kHz.
  - Suitable for commands, control, and small inference results (like classification labels or bounding box data).
  - Not suitable for image streaming or large model data transfers — it will quickly bottleneck.
- UART speed
  - SSCMA UART defaults to 921600 baud (~ 0.92 Mbps).
  - Can sometimes be lowered (115200, 460800) if needed, but 921600 is recommended for tasks transfering vision data.
  - Effective throughput: ~90–100 KB/s real-world.
  - Good enough for sending inference results quickly and even compressed image chunks if needed.
  - Must use hardware UART (software serial usually insufficient).
  - Much faster and more reliable for continuous AI tasks compared to I²C.

### Usage of Seeed_Arduino_SSCMA Library
[Top](#expts_grove_vision_ai_v2 "Top")<br>
When called without parameters, the SSCMA::begin() function typically uses a default I2C interface, assuming the hardware is configured for it. The library is designed to work with Seeed Studio's hardware, and the no-parameter version of begin() provides a convenient way to initialize the communication interface for devices that use a standard I2C connection, such as the Grove Vision-AI V2.<br>
For example, when using the Grove Vision-AI V2, the begin() function with no arguments:
- Initializes the I2C communication protocol using the default Wire object.
- Uses the default I2C address (I2C_ADDRESS) to identify and communicate with the device.

In order to use with the XIAO ESP32-C3 hardware UART I started it this way:
```C
// Define pins for Seeed XIAO ESP32-C3
// GPIO20 = RX, GPIO21 = TX
#define RX_PIN 20     // D7 on XIAO ESP32-C3
#define TX_PIN 21     // D6 on XIAO ESP32-C3

  // Start hardware UART1 for Vision AI
  Serial1.begin(921600, SERIAL_8N1, RX_PIN, TX_PIN);
  // Initialize SSCMA library with Vision AI UART
  if (!AI.begin(&Serial1)) {
```

### AI Models
[Top](#expts_grove_vision_ai_v2 "Top")<br>
There are several ways to get a model into the Vision-AI V2 module; below are some of them I have found.

Be aware that there are three things related to Seeed SenseCraft Model Assistant and referred to as SSCMA
1. https://github.com/Seeed-Studio/Seeed_Arduino_SSCMA - Seeed_Arduino_SSCMA - a library for use in Arduino IDE to assist in communicating with AI models running on a different hardware module - included in XIAO ESP32-C3 code
1. https://github.com/Seeed-Studio/SSCMA-Micro - SSCMA-Micro - a cross-platform machine learning inference framework - implements digital image processing, neural network inferencing, AT command interaction, and more - included in Vision-AI V2 code
1. https://wiki.seeedstudio.com/ModelAssistant_Introduce_Overview - Seeed SenseCraft (AI) Model Assistant - an open-source project focused on embedded AI including tools and a model zoo - on the web

I will use the Seeed_Arduino_SSCMA library on the XIAO ESP32-C3 to communicate with the Grove Vision-AI V2 which is using SSCMA-Micro. I will use Seeed SenseCraft (AI) Model Assistant to load my vision models onto the Vision-AI V2

#### SenseCraft
[Top](#expts_grove_vision_ai_v2 "Top")<br>
SenseCraft - https://wiki.seeedstudio.com/sensecraft-ai/overview/
- SenseCraft has some SSCMA models available here (via json files) - https://github.com/Seeed-Studio/sscma-model-zoo

#### Edge Impulse
[Top](#expts_grove_vision_ai_v2 "Top")<br>
Edge Impulse - https://wiki.seeedstudio.com/edgeimpulse/
- https://studio.edgeimpulse.com/signup
- https://docs.edgeimpulse.com/hardware/boards/seeed-grove-vision-ai-module-v2-wise-eye-2

#### HimaxWiseEyePlus
[Top](#expts_grove_vision_ai_v2 "Top")<br>
HimaxWiseEyePlus - https://github.com/HimaxWiseEyePlus/Seeed_Grove_Vision_AI_Module_V2
- There is a model zoo here - https://github.com/HimaxWiseEyePlus/Seeed_Grove_Vision_AI_Module_V2/tree/main/model_zoo
- There is a way to debug models on the Vision-AI V1 - https://github.com/HimaxWiseEyePlus/Seeed_Grove_Vision_AI_Module_V2/tree/main/swd_debugging

#### Ultralytics
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

## Any Model Export - example Ultralytics - then through SenseCraft
[Top](#expts_grove_vision_ai_v2 "Top")<br>
Be aware that there are two things named Seeed SenseCraft Model Assistant and referred to as SSCMA
1. https://github.com/Seeed-Studio/Seeed_Arduino_SSCMA - a library for use in Arduino IDE to assist in communicating with AI models running on a different hardware module
1. https://wiki.seeedstudio.com/ModelAssistant_Introduce_Overview - Seeed SenseCraft (AI) Model Assistant - an open-source project focused on embedded AI including tools and a model zoo

In the Model Export section we will use tools from the SSCMA open-source project.

NOTE: Due to the size limitation, currently both XIAO ESP32S3 and Grove Vision-AI V2 only support int8 format models.

NOTE: here is the start of SEEED Studio docs on how to do this:
- https://wiki.seeedstudio.com/grove_vision_ai_v2_sscma/

NOTE: here is a SEEED Wiki document on how to do this
- https://github.com/Seeed-Studio/wiki-documents/blob/docusaurus-version/docs/Sensor/Grove/Grove_Sensors/AI-powered/Train-Deploy-AI-Model-Grove-Vision-AI.md

NOTE: here is a Hackster.io example of how to do this
- https://www.hackster.io/mjrobot/computer-vision-at-the-edge-with-grove-vision-ai-module-v2-0003c7

NOTE: this Youtube shows an example project to detect different birds: https://www.youtube.com/watch?v=zdrtL1XDRn0&list=PLmOy82pCgLFnYoYTYNyQQvGa9bUU7hC5K
- Shows how to export a trained model to SenseCraft
- Shows how to download the inference picture (third param = true on inference call)
- Lots of good practical info from an actual Vision-AI V2 project

To deploy an Ultralytics model to a Seeed Grove Vision-AI V2, we convert the model to the specific format required by the device's Himax WiseEye2 processor. The deployment process is managed by Seeed Studio's SenseCraft AI platform, which handles the flashing of the converted model onto the hardware. [1] [2] [3]

### Export an Ultralytics Model 
[Top](#expts_grove_vision_ai_v2 "Top")<br>
First, export a custom-trained or standard Ultralytics model (e.g., YOLOv8) to the ONNX format. This is done from the Python training environment or a notebook using the Ultralytics export function. [1] [4]
```
from ultralytics import YOLO

model = YOLO('yolov8n.pt')  # Load a trained model or use a custom trained model
model.export(format='onnx', opset=12) # Export the model to ONNX format
```

### Convert ONNX to int8_vela.tflite
[Top](#expts_grove_vision_ai_v2 "Top")<br>
Use the SenseCraft Model Assistant, a Google Colab-based tool provided by Seeed Studio, to convert an ONNX model to the specific format. 

1. Open the SenseCraft Model Assistant Colab notebook linked in the Seeed Studio Wiki. [8] [9] [10] [11] [12] [13] [14]
1. Follow the notebook's instructions to upload the exported ONNX model. 
1. The notebook will perform the necessary quantization and conversion steps, producing a file with the int8_vela.tflite extension. 
1. Download the converted  model file to your computer. [1]

NOTE: read these forum entries to get Python dependencies correct:
- https://forum.seeedstudio.com/t/grove-ai-vision-install-tensorflow-for-yolov5-swift-error/292556
- https://forum.seeedstudio.com/t/failed-to-setup-sscma-in-google-colab/280950/2

### Use SenseCraft AI to deploy the model 
[Top](#expts_grove_vision_ai_v2 "Top")<br>
With the converted model, we can now use the SenseCraft AI platform to flash it to the Vision-AI V2 device. 

1. Connect the Grove Vision-AI V2 to your computer using a USB-C cable. 
1. Navigate to the SenseCraft AI Model Assistant webpage in your browser. 
1. In the web interface, click on Device Workspace, then select Grove - Vision-AI V2. 
1. Click the Connect button and select the serial port for the Vision-AI V2 device from the pop-up window. 
1. After connecting, select the option to Upload Custom AI Model. 
1. You will be prompted to provide the model name, your  model file, and the list of labels used for your dataset. 
1. Click Send Model to begin the upload process. The flashing can take several minutes. [1] [5] [6] [7]  

### Test and view results 
[Top](#expts_grove_vision_ai_v2 "Top")<br>
Once the upload is complete, the SenseCraft web interface should automatically display the camera's live feed with your model's inference results overlaid on the video. [7]  

### References
[Top](#expts_grove_vision_ai_v2 "Top")<br>
- [1] https://wiki.seeedstudio.com/grove_vision_ai_v2_sscma/
- [2] https://docs.edgeimpulse.com/docs/edge-ai-hardware/mcu-+-ai-accelerators/himax-seeed-grove-vision-ai-module-v2-wise-eye-2
- [3] https://www.seeedstudio.com/blog/2020/11/02/the-things-indoor-gateway-gets-started-with-sensecap-sensor/
- [4] https://github.com/ultralytics/ultralytics/issues/6676
- [5] https://wiki.seeedstudio.com/Vision_AI_with_Customizable_Models/
- [6] https://docs.petoi.com/extensible-modules/advanced-development-and-application-of-ai-vision-modules/model-deployment
- [7] https://wiki.seeedstudio.com/sensecraft-ai/tutorials/sensecraft-ai-pretrained-models-for-grove-vision-ai-v2/
- [8] https://wiki.seeedstudio.com/tinyml_topic/
- [9] https://wiki.seeedstudio.com/tinyml_topic/#support-platforms
- [10] https://wiki.seeedstudio.com/ModelAssistant_Introduce_Overview/
- [11] https://github.com/Seeed-Studio/ModelAssistant
- [12] https://wiki.seeedstudio.com/ModelAssistant_Introduce_Quick_Start/
- [13] https://wiki.seeedstudio.com/ModelAssistant_Introduce_Installation/
- [14] https://wiki.seeedstudio.com/ModelAssistant_Tutorials_Export_Overview/

## Experiment 01 - Face Following
[Top](#expts_grove_vision_ai_v2 "Top")<br>
Follow Experiment 01 in detail here:
- https://github.com/Mark-MDO47/expts_grove_vision_ai_v2/blob/master/expt_01_FaceFollowing/README.md

### Experiment 01 Introduction
[Top](#expts_grove_vision_ai_v2 "Top")<br>
There is a demo project that does face following with a fan:
- https://wiki.seeedstudio.com/grove_vision_ai_v2_demo/ search for **Project I: Create a Face-Tracking Fan**

My first usage will be to add face following to my Skull Project https://github.com/Mark-MDO47/Skull-Project. We want to make the eyes follow the face detected by the Vision-AI V2.

The Skull Project uses eyes made from Adafruit HalloWing M4 Express. These use the SAMD51 processor (ATSAMD51G18).
- https://www.adafruit.com/product/4300
- http://ww1.microchip.com/downloads/en/DeviceDoc/60001507E.pdf

Because the Skull Project eyes are pretty busy just displaying the eyes, I don't want to interrupt them at random times with an I2C or UART message. Thus I plan to output the position information on two ESP32-C3 Analog channels, and the SAMD51 in the eyes can sample the information at any convenient time that doesn't interrupt its processing.

I just realized I was looking at the Analog-to-Digital capabilities (ADC for analog input) instead of the Digital-to-Analog capabilities. The XIAO ESP32-C3 only has D10 with DAC.

I will start by using the ESP32 LEDC library for analog output; that way I can use the same code for both analog outputs. I may need to implement filtering on the analog outputs so the SAMD51 can do reliable sensing.

I previously did LEDC analog outputs in my https://github.com/Mark-MDO47/DuelWithBanjos project. I didn't need any filtering with the LED outputs. We shall see... read more in the experiment 01 detail here:
- https://github.com/Mark-MDO47/expts_grove_vision_ai_v2/blob/master/expt_01_FaceFollowing/README.md
