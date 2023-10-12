# Arduino Infrared Remote Control Project

![Project Image or GIF](https://i.ibb.co/T4884Q6/IR-Remote-Diagram-bb.png)

## Table of Contents
- [Description](#description)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Modes](#modes)
- [Notes](#Notes)
- [License](#license)

## Description
This Arduino project allows you to control various functions using an infrared remote control. It features multiple modes, including volume control, garage door opener, music and light show, and a piano remote.

## Features
- Infrared remote control functionality.
- Four different modes to perform various actions.
- Modular code structure for easy maintenance and customization.
- Mode-specific functionality and commands.

## Hardware Requirements
- Arduino board (compatible with the libraries used).
- Infrared receiver module.
- Infrared remote control.
- Additional hardware as required by your specific project (e.g., LEDs, buzzer,current limiting resistor).

## Software Requirements
- Arduino IDE.
- IRremote library.
- NewTone library.
- [musicConfig.h](musicConfig.h) - Contains note pitches, song melody, and duration.
- [command.h](command.h) - Contains remote-specific commands.
- [pinSetup.h](pinSetup.h) - Defines the pin setup for your project.

## Installation
1. Clone this repository to your local machine.
2. Open the Arduino IDE.
3. Load the project's main Arduino sketch.
4. Upload the sketch to your Arduino board.

## Usage
- Connect the required hardware components to your Arduino board.
- Power up the system and point the infrared remote control towards the receiver.
- Use the remote to navigate between different modes and perform actions based on your project's functionalities.

## Modes
1. **Volume Control**: Control the volume of an audio system.
2. **Garage Door Opener**: Open and close a garage door.
3. **Music and Light Show**: Enjoy a synchronized music and light show.
4. **Piano Remote**: Play musical notes with the remote control.

## Notes
Remember that infrared remotes, differs in infrared signal sending. Make sure to know the value of each buttons on your remote and configure this on the file [command.h](command.h)

## License
This project is open-source and available under the [MIT License](LICENSE).
