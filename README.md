# expts_grove_vision_ai_v2
Experiments using Grove Vision-AI version 2 and SEEED Sensecraft

**Table Of Contents**
* [Top](#expts_grove_vision_ai_v2 "Top")
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

  // within setup() routine

  Serial.begin(115200);   // Serial monitor
  delay(1000);

  // Start hardware UART1 for communicating with Vision AI
  Serial1.begin(921600, SERIAL_8N1, RX_PIN, TX_PIN);
  // Initialize SSCMA library with Vision AI using UART
  if (!AI.begin(&Serial1)) {
    Serial.println("Failed to initialize Vision AI V2 over UART!");
    while (1);
  }
  Serial.println("Vision AI V2 initialized successfully!");
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
