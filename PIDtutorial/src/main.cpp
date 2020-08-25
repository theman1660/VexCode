/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LFM                  motor         1               
// RFM                  motor         2               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

//variables
double kP = 0.0;
double kI = 0.0;
double kD = 0.0;

double turnkP = 0.0;
double turnkI = 0.0;
double turnkD = 0.0;

//Auton Setting
int desiredValue = 200;
int desiredTurnValue = 0;

int error; //SensorValue - DesiredValue : Position -> speed -> aceleration
int prevError = 0; //Position 20 msec ago
int derivative; // error - previousError : Speed
int totalError = 0;//totalError = totalError + Error 

int turnError; //SensorValue - DesiredValue : Position -> speed -> aceleration
int turnPrevError = 0; //Position 20 msec ago
int turnDerivative; // error - previousError : Speed
int turnTotalError = 0;//totalError = totalError + Error 

bool resetDriveSensors = false;


//PID Enable
bool DrivePID = false;

//tasks
int DriveTask() {
  while(DrivePID){
    if (resetDriveSensors) {
      resetDriveSensors = false;

      LFM.resetPosition();
      RFM.resetPosition();
    }

    //Gets Average Position
    int LFMPosition = LFM.position(degrees);
    int RFMPosition = RFM.position(degrees);

    int averagePosition = (LFMPosition + RFMPosition)/2;

    //Potential
    error = averagePosition - desiredValue;

    //Derivative
    derivative = error - prevError;
    
    //Intergral
    //Velocity -> Position -> Absement
    totalError += error;

    double lateralMotorPower = error * kP + derivative *kD + totalError * kI;

    //Turning Movement PID
    //////////////////////////////////////////////////////
    //Gets Average
    int turnDifference = LFMPosition - RFMPosition;

    turnError = turnDifference - desiredTurnValue;

    turnDerivative = turnError - turnPrevError;

    turnTotalError += turnError;

    double turnMotorPower = turnError * kP + derivative *kD + totalError * kI; 
    ///////////////////////////////////////////////////////

    LFM.spin(forward, lateralMotorPower + turnMotorPower, voltageUnits::volt);
    RFM.spin(forward, lateralMotorPower - turnMotorPower, voltageUnits::volt);

    //sets error
    prevError = error;
    turnPrevError = turnError;
    task::sleep(20);
  }
  return 1;
}

void autonomous(void) {
  task task1 = task(DriveTask);

  resetDriveSensors = true;
  desiredValue = 300;
  desiredTurnValue = 600;

  vex::task::sleep(1000);

  resetDriveSensors = true;
  desiredValue = -300;
  desiredTurnValue = 300;
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
