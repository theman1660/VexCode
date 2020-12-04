// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LFM                  motor         20              
// RFM                  motor         9               
// LBM                  motor         19              
// RBM                  motor         10              
// Lintake              motor         15              
// Rintake              motor         8               
// Rlift                motor         5               
// Llift                motor         14              
// Vision5              vision        21              
// Gyro                 inertial      4               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LFM                  motor         20              
// RFM                  motor         9               
// LBM                  motor         19              
// RBM                  motor         10              
// Lintake              motor         15              
// Rintake              motor         8               
// Rlift                motor         5               
// Llift                motor         14              
// Vision5              vision        21              
// Gyro                 inertial      4               
// RangeR               sonar         C, D            
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:    main.cpp                                                     */
/*    Author:                                                        */
/*    Created:                                                       */
/*    Description:  code                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LFM                  motor         20               
// RFM                  motor         9              
// LBM                  motor         19              
// RBM                  motor         10              
// Lintake              motor         15              
// Rintake              motor         8               
// Rlift                motor         5               
// Llift                motor         14              
// Vision5              vision        21              
// Gyro                 inertial      4               
// RangeL               sonar         A, B            
// RangeR               sonar         C, D            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

//Task for Printing to brain screen


/*void draw_touch(void){
  Brain.Screen.setPenColor(red);
  Brain.Screen.drawCircle(Brain.Screen.xPosition(), Brain.Screen.yPosition(), 30);
}*/

// LEFT = 1
// RIGHT = 0
int autontype = 0;
bool cameraTaskEnable = false;
int cameraTask() {
  while(cameraTaskEnable){
    Brain.Screen.render(true, false);
    while(true){
      if(Brain.Screen.pressing() and autontype == 0){
        Brain.Screen.clearScreen();
        while(Brain.Screen.pressing()){
          if (Brain.Screen.xPosition() < 240){
            autontype = 1;  
            Brain.Screen.clearScreen();
            Brain.Screen.setPenColor(red);
            Brain.Screen.drawRectangle(0 , 0, 240, 272);
            Brain.Screen.setCursor(0, 0);
            Brain.Screen.print("Left");
            Controller1.Screen.print(autontype);
          }
          Brain.Screen.render();
          wait(1000,msec);
        }
      }
      else if(Brain.Screen.pressing() and autontype == 1){
        Brain.Screen.clearScreen();
        while(Brain.Screen.pressing()){
          if (Brain.Screen.xPosition() < 240){
            autontype = 0;  
            Brain.Screen.clearScreen();
            Brain.Screen.setPenColor(blue);
            Brain.Screen.drawRectangle(0 , 0, 240, 272);
          
            Brain.Screen.print("Right");
            Controller1.Screen.print(autontype);
          }
          Brain.Screen.render();
          wait(1000,msec);
        }
      }
    }
  }



  /*
  while(cameraTaskEnable){
    if(Brain.Screen.pressing() == true and autontype == 0){
      Brain.Screen.setCursor(0, 0);
      autontype = 1;
      Brain.Screen.clearScreen(red);
      Brain.Screen.print("Auton %d", autontype);
      wait(1000, msec);
    }
    else if(Brain.Screen.pressing() == true and autontype == 1){
      Brain.Screen.setCursor(0, 0);
      autontype = 0;
      Brain.Screen.clearScreen(blue);
      Brain.Screen.print("Auton %d", autontype);
      wait(1000, msec);
    }
    */
    //Controller1.Screen.print(LFM.torque());
    //Controller1.Screen.print(LBM.torque());
    //Controller1.Screen.print(RFM.torque());
    //Controller1.Screen.print(RBM.torque());
  Controller1.Screen.clearLine(1);
  Controller1.Screen.clearLine(2);
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("LTemp");
  Controller1.Screen.print(Lintake.temperature());
  Controller1.Screen.newLine();
  Controller1.Screen.print("RTemp");
  Controller1.Screen.print(Rintake.temperature());
  Controller1.Screen.newLine();
  Controller1.Screen.print("GyroHeading");
  Controller1.Screen.print(Gyro.heading());
  Brain.Screen.render();

  task::sleep(150);
  return(1);
}

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
  // Example: clearing encoders, setting servo positions, ...
  vexcodeInit();
  Gyro.calibrate();
  waitUntil(Gyro.isCalibrating() == false);
  Brain.Screen.print("GYRO good");
  task task1 = task(cameraTask);
  Llift.setStopping(coast);
  Rlift.setStopping(coast);
  Llift.setVelocity(100,percent);
  Rlift.setVelocity(100,percent);
  Lintake.setVelocity(100,percent);
  Rintake.setVelocity(100,percent);
}
//change % of drive motor velocity
void drivevelocity(int velo)
{
  LFM.setVelocity(velo,percent);
  RFM.setVelocity(velo,percent);
  LBM.setVelocity(velo,percent);
  RBM.setVelocity(velo,percent);
}

//Lift Functions
void liftout(int movementcount, bool stopmode) {
  Llift.spinFor(forward, movementcount, degrees, false);
  Rlift.spinFor(forward, movementcount, degrees, stopmode);
}

void intakein(int movementcount, bool stopmode){
  Lintake.spinFor(reverse, movementcount, degrees, false);
  Rintake.spinFor(reverse, movementcount, degrees, stopmode);
}

//Strafe Functions
void strafeleft(int movementcount, bool stopmode){
  LFM.spinFor(forward, movementcount, degrees, false);
  RFM.spinFor(reverse, movementcount, degrees, false);
  LBM.spinFor(forward, movementcount, degrees, false);
  RBM.spinFor(reverse, movementcount, degrees, stopmode);
}

void straferight(int movementcount, bool stopmode){
  LFM.spinFor(reverse, movementcount, degrees, false);
  RFM.spinFor(forward, movementcount, degrees, false);
  LBM.spinFor(reverse, movementcount, degrees, false);
  RBM.spinFor(forward, movementcount, degrees, stopmode);
}

//Turn / Drive functions
void turnleft(int movementcount, bool stopmode){
  LFM.spinFor(forward, movementcount, degrees, false);
  RFM.spinFor(reverse, movementcount, degrees, false);
  LBM.spinFor(reverse, movementcount, degrees, false);
  RBM.spinFor(forward, movementcount, degrees, stopmode);
}

void turnright(int movementcount, bool stopmode){
  LFM.spinFor(reverse, movementcount, degrees, false);
  RFM.spinFor(forward, movementcount, degrees, false);
  LBM.spinFor(forward, movementcount, degrees, false);
  RBM.spinFor(reverse, movementcount, degrees, stopmode);
}

void driveforward(int movementcount, bool stopmode){
  LFM.spinFor(reverse, movementcount, degrees, false);
  RFM.spinFor(reverse, movementcount, degrees, false);
  LBM.spinFor(forward, movementcount, degrees, false);
  RBM.spinFor(forward, movementcount, degrees, stopmode);
}

//Gyro Functions
void turnleftto(int turnamount){
  int leftturn = 360 - turnamount;
  drivevelocity(25);
  LFM.spin(forward);
  RFM.spin(reverse);
  LBM.spin(reverse);
  RBM.spin(forward);
  wait(200,msec);
  waitUntil((Gyro.heading(degrees) <= leftturn+15));
  LFM.stop();
  RFM.stop();
  LBM.stop();
  RBM.stop();
  drivevelocity(10);
  wait(500,msec);
  LFM.spin(forward);
  RFM.spin(reverse);
  LBM.spin(reverse);
  RBM.spin(forward);
  waitUntil((Gyro.heading(degrees) <= leftturn));
  LFM.stop();
  RFM.stop();
  LBM.stop();
  RBM.stop();
}
void turnrightto(int turnamountright){
  drivevelocity(25);
  LFM.spin(reverse);
  RFM.spin(forward);
  LBM.spin(forward);
  RBM.spin(reverse);
  wait(200,msec);
  waitUntil((Gyro.heading(degrees) >= turnamountright-15));
  LFM.stop();
  RFM.stop();
  LBM.stop();
  RBM.stop();
  drivevelocity(10);
  wait(500,msec);
  LFM.spin(reverse);
  RFM.spin(forward);
  LBM.spin(forward);
  RBM.spin(reverse);
  waitUntil((Gyro.heading(degrees) >= turnamountright));
  LFM.stop();
  RFM.stop();
  LBM.stop();
  RBM.stop();
}

//Autonomous
void autonomous() {
  //LEFT = 1
  //RIGHT = 0
  Gyro.setHeading(0, degrees);
  drivevelocity(50);
  intakein(360, false);
  driveforward(-400, true);
  wait(250, msec);
  //INVERTED
  strafeleft( -375, true);
  wait(250, msec);
  //INVERTED
  turnleftto(0);
  drivevelocity(50);
  wait(250, msec);
  driveforward(400, true);
  liftout(1200, true);
  intakein(-500, false);
  driveforward(-400, true);
  //second goal
  //INVERTED
  straferight(-650, true);
  //INVERTED
  turnleftto(45);
  drivevelocity(50);
  wait(250, msec);
  intakein(1800, false);
  driveforward(1200, true);
  liftout(2000, true);
  driveforward(-750, false);
  intakein(-1000, true);
}

//Main Drive
void usercontrol(void) {
  //resets encoders
  Lintake.setPosition(0,degrees);
  Rintake.setPosition(0,degrees);
  Llift.setPosition(0,degrees);
  Rintake.setPosition(0,degrees);
  LFM.setPosition(0,degrees);
  RFM.setPosition(0,degrees);
  LBM.setPosition(0,degrees);
  RBM.setPosition(0,degrees);
  drivevelocity(100);

  while (true) {
    //Drive code
    LFM.setVelocity((-Controller1.Axis3.position() - Controller1.Axis1.position() - Controller1.Axis4.position()),percent);
    RFM.setVelocity((-Controller1.Axis3.position() + Controller1.Axis1.position() + Controller1.Axis4.position()),percent);
    LBM.setVelocity((Controller1.Axis3.position() + Controller1.Axis1.position() - Controller1.Axis4.position()),percent);
    RBM.setVelocity((Controller1.Axis3.position() - Controller1.Axis1.position() + Controller1.Axis4.position()),percent);

    LFM.spin(forward);
    RFM.spin(forward);
    LBM.spin(forward);
    RBM.spin(forward);

    //lift Code
    if (Controller1.ButtonR1.pressing()){
      Llift.spin(forward);
      Rlift.spin(forward);
    }
    else if(Controller1.ButtonR2.pressing()){
      Llift.spin(reverse);
      Rlift.spin(reverse);
    }
    else{
      Llift.stop();
      Rlift.stop();
    }

    //Intake Code
    if (Controller1.ButtonL1.pressing()){
      Lintake.spin(reverse);
      Rintake.spin(reverse);
    }
    else if(Controller1.ButtonL2.pressing()){
      Lintake.spin(forward);
      Rintake.spin(forward);
    }
    else{
      Lintake.stop();
      Rintake.stop();
    }
  }
  wait(20,msec);
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
