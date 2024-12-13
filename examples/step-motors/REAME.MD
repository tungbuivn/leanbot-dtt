 # Stepper Motor Control Project
 
 ## Project Overview
 This project involves controlling a stepper motor using an A4988 driver with an Arduino. The code is designed to manage the motor's acceleration, constant speed, and deceleration phases for precise control.
 
 ## Code Explanation
 The `runMotor` function is responsible for executing the motor's steps while managing the timing based on acceleration and speed settings.
 
 ## Key Components
 - **StepperMotor Class**: Manages motor state and behavior.
 - **runMotor Function**: Controls the timing of motor steps during different phases (acceleration, constant speed, deceleration).
 - **Timing Logic**: Adjusts the delay between steps based on the current phase of motor operation.
 
 ## Usage Instructions
 To use this code:
 - Ensure you have the necessary hardware connections for the A4988 driver and the stepper motor.
 - Upload the code to your Arduino board.
 - Monitor the Serial output for timing information and motor status.
 
 ## Conclusion
 This document provides an overview of the stepper motor control project, explaining the key components and their functionality. The timing logic ensures smooth operation of the motor through various phases.## Using Wokwi for Simulation
 Wokwi is an online simulator for Arduino projects. To use Wokwi with this project, follow these steps:
 
 1. **Open Wokwi**: Go to the [Wokwi website](https://wokwi.com).
 2. **Create a New Project**: Click on "Create New Project" and select "Arduino" as the board type.
 3. **Upload Your Code**: Copy the code from your `main.cpp` file and paste it into the Wokwi code editor.
 4. **Add Components**: Use the Wokwi components panel to add the A4988 driver and stepper motor to your project. Connect them according to your hardware setup.
 5. **Run the Simulation**: Click the "Start Simulation" button to see the motor in action. You can monitor the Serial output in the Wokwi console.
 
 This allows you to test and visualize your stepper motor control without needing physical hardware.

 ## Generating the Speed Table
 To create the `speed.h` file from the `generate_speed_table.js` script, follow these steps:
 
 1. **Navigate to the Script Location**: Open a terminal or command prompt and navigate to the directory where `generate_speed_table.js` is located:
 
 2. **Run the Script**: Execute the script using Node.js:
 
 3. **Check for Output**: After running the script, check the `src` directory for the newly created `speed.h` file.
 
 This file contains the speed table data used by the stepper motor control code.