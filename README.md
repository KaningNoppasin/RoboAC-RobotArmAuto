# RoboAC-RobotArmAuto-Project
## Project Structure
```
/RoboAC-RobotArmAuto-Project
├── include
├── lib
├── src
│   └── main.cpp
├── platformio.ini
└── README.md
```
- ### Main Machine
  - **main.cpp**
    ```cpp
    #include <Arduino.h>
    #include "./main/main.ino"
    ```

## Configuration
- ### Arduino Mega
  - **platformio.ini**
    ```ini
    [env:megaatmega2560]
    platform = atmelavr
    board = megaatmega2560
    framework = arduino
    monitor_speed = 115200
    monitor_filters = time, log2file
    lib_deps =
    	waspinator/AccelStepper@^1.64
    ```