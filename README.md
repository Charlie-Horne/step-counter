## Overview

This project uses an embedded system to record a user's steps and estime the distance travelled by the user. This step counter uses a STM32C071 nucleo development board and an expansion board for the hardware of the project. The program is scheduled by a round-robin kernal with interupts. The program records and displays a users step count while holding a device, and includes a range of features including:
- step counter
- distance walked counter
- The ability to track and change a step goal
- Change units steps and distance are displayed in

The project utilises an OLED display and joystick to provide this functionality, as well as an IMU to detect the acceleration of the users steps.


## Table of Contents

- [Overview](#overview)
- [Table of Contents](#table-of-contents)
- [Scheduler](#scheduler)
- [Modularisation](#modularisation)
    - [Peripheral Modularisation](#peripheral-modularisation)
    - [Scheduler Modularisation](#scheduler-modularisation)
    - [Display Modularisation](#display-modularisation)
- [Peripherals](#peripherals)
- [Step Detection](#step-detection)


## Scheduler
The scheduler used in this project implemented a round robin kernal with interupts. The scheduler is designed to run individual functions rather than entire modules. This was implemented to reduce load on the cpu. On startup/reset, the app.c module defines the frequency for each function to run at, initalises each module required, adds the required functions to the kernals task list, and calls a kernal execute task in a while(1) loop from the kernal.c module. This system choose to seperate the fundamental logic of the schedular to the task list for readability. This schedular was depenent on interupts, and used HAL_GetTick() to keep time.


## Modularisation 
The general intent with modularisation in this code was to have a module for each task. This included seperate modules for each peripheral, a module for displays, a module for the state machine, a module for pacing, and a module for calculations. Due to complexity of this system, some modules do not follow this seperation exactly, as further modularity was appropriate to simplify the complexity of the system. The full modularisation of the project can be seen in the dependency graph below. For simplicity, this graph does not display dependencies on HAL, or standard C libraries.

![Dependency Graph](/dependency_graph.png "Dependency Graph")

#### Peripheral Modularisation
Seperate moduels were created to handle each peripheral. This included the buttons, leds, joystick, buzzer, and potentiometer. The joystick and and potentiometer modules were dependent on the adc module, which was required to read the analouge inputs as digital signals by the microcontroller. The buzzer functioned in a similar way, requiring pwm to be initialised; however, this was never seperated into different modules as the buzzer was the only peripheral using pwm.

#### Scheduler Modularisation
The scheduling for this project was seperated into an 'app' and 'kernal' modules. This was done to improve readability, ease of use when adding more functions to the scheduler. The app module was used to initilise the functions that needed to be scheduled. This would initilise the required functions, and define the frequency they should run at. The kernal module was used to handle the scheduling logic. The kernal scheduler function would be called in the app module. 

#### Display Modularisation
To simplfy the process of displaying multaple screens, this module was split into seven seperate modules. These were 'state', 'display', and five modules containing individual screens displays (display_steps, display_distance, display_goal, display_testmode, display_setgoal). The decision to split the 'display' and 'state' was due to the very seperate roles these modules performed. 
The 'state' module was used to develop the finite state machine which determined which screen was displayed. This module focused on interpreting the inputs from the joystick and SW2 button to decide what screen the user wanted to move to. A enum would be returned by the state module for each of the display screens. 
The 'display' module was focused dedicated to initalising and updating the screen. The 'display' module reads the screen enum from the state module, and would update a switch case. This allowed the module to update the information the screen would display, and update the screen. The switch case used to upadte the display would call a function from different screen display modules.
Each screen to be displayed was in a seperate module. This improved the readability of the code and made it easier to make changes to each individual screen. The five screen display modules used were display_steps, display_distance, display_goal, display_testmode, display_setgoal.


## Peripherals
The joystick and potentiometer interface with the microcontroller through an ADC using HAL. This initialises and updates the horizontal joystick movement, vertical joystick movement, and potentiometer reading. The joysticks are setup so that both the direction and displacement can be read using functions 'JOYSTICK_get_direction(char* axis)' and 'JOYSTICK_get_displacement(char* axis)'. The direction of the axis is returned as an enum of 'JOYSTICK_UP', 'JOYSTICK_DOWN', 'JOYSTICK_LEFT', 'JOYSTICK_RIGHT', and 'JOYSTICK_REST'. A deadzone has been implemented so that movements on the joystick feel more consistent to the user. The joystick displacement is returned as a value from 0-100. This value is non-directional, with 0 being the center of the joystick when at rest, and 100 being the maximum tilt of the joystick. The potentiometer uses the 'POT_get_step_goal()' function to return the current value of the potentiometer, converted to a step goal. This reads the raw value of the potentiometer, and returns a scaled integer between 500 and 15000. 

The buttons were configured to detect four main buttons (SW1, SW2, SW3, SW4) as well as the joystick click. Three different button states were able to be monitored. These were:

- Single Press
- Double Press
- Long Press

This single press was used to detect a single press. This was largly used to enable/disable the serial port using SW1, and canceling a goal change with the joystick. This detected when a singular press and release was detected without the button being held down.
The double press was used to enter and exit testmode. This detected when two seperate button presses occured in quick succession. If the time between the two presses was too long, the timer would be reset.
The long press detection was used to enter into the set goal mode and confirm a new goal using a long press with the joystick. This sistuation would only be true when the joystick was held down continually for over one second. 


## Step Detection
To detect steps, this project uses an inertial measurement unit (IMU) to detect acceleration vectors generated by the movement of the board. To achieve consistent step detection, this project:

- Fetches the acceleration vector from the IMU
- Removes noise from this signal using a low pass filter
- Detects peaks in the filtered signal

The microcontroller is configured to use the SPI peripheral to communicate with the IMU. This is done in the 'imu_driver' file. This file holds functions to initialise the IMU, update the x, y, and z direction accelerations, calculate the magnitude of the directions. Noise filtering and peak detection are handled in the 'peak_detection' file. Filtering is handled using a low pass filter. The implementation of this uses an FIR averaging filter. This filter uses a circular buffer with a window size of 16 to average the signal of the magnitude. Applying the filter after the magnitude was calculated allowed for a faster function, as the filter was only required once rather than three times per value. 

This code uses a max threshold and hysteresis to detect steps. After graphing the output of the magnitude, an appropriate threshold of 40000 was determined. To remove false step inputs such as one step being counted as multiple, a cooldown period of 250ms was implemented where no steps could be detected. This process proved highly accurate with different walking speeds, testing both light and heavy steps. The figure below show the response and threshold for both heavy and light steps. 
