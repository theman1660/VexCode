// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LFM                  motor         15              
// RFM                  motor         2               
// LBM                  motor         13              
// RBM                  motor         12              
// Lintake              motor         10              
// Rintake              motor         20              
// Rlift                motor         19              
// Llift                motor         9               
// Vision5              vision        21              
// Gyro                 inertial      14               
// ---- END VEXCODE CONFIGURED DEVICES ----
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
// LFM                  motor         15              
// RFM                  motor         2               
// LBM                  motor         13              
// RBM                  motor         12              
// Lintake              motor         10              
// Rintake              motor         20              
// Rlift                motor         19              
// Llift                motor         9               
// Vision5              vision        21              
// Gyro                 inertial      14              
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
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  vexcodeInit();
  Llift.setStopping(brake);
  Rlift.setStopping(brake);
  Llift.setVelocity(100,percent);
  Rlift.setVelocity(100,percent);
  Lintake.setVelocity(100,percent);
  Rintake.setVelocity(100,percent);
}

void drivevelocity(int velo)
{
  LFM.setVelocity(velo,percent);
  RFM.setVelocity(velo,percent);
  LBM.setVelocity(velo,percent);
  RBM.setVelocity(velo,percent);
}

void liftup(int movementcount, bool stopmode) {
  Llift.spinFor(forward, movementcount, degrees, false);
  Rlift.spinFor(forward, movementcount, degrees, stopmode);
}

void intakein(int movementcount, bool stopmode){
  Lintake.spinFor(reverse, movementcount, degrees, false);
  Rintake.spinFor(reverse, movementcount, degrees, stopmode);
}

void strafeleft(int movementcount, bool stopmode){
  LFM.spinFor(reverse, movementcount, degrees, false);
  RFM.spinFor(forward, movementcount, degrees, false);
  LBM.spinFor(reverse, movementcount, degrees, false);
  RBM.spinFor(forward, movementcount, degrees, stopmode);
}

void straferight(int movementcount, bool stopmode){
  LFM.spinFor(reverse, movementcount, degrees, false);
  RFM.spinFor(forward, movementcount, degrees, false);
  LBM.spinFor(reverse, movementcount, degrees, false);
  RBM.spinFor(forward, movementcount, degrees, stopmode);
}

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

void turnto(int turnamount)
{
  drivevelocity(25);
  LFM.spin(reverse);
  RFM.spin(forward);
  LBM.spin(forward);
  RBM.spin(reverse);
  waitUntil((Gyro.heading(degrees) >= turnamount));
  LFM.stop();
  RFM.stop();
  LBM.stop();
  RBM.stop();
  drivevelocity(10);
  wait(1000,msec);
  LFM.spin(reverse);
  RFM.spin(forward);
  LBM.spin(forward);
  RBM.spin(reverse);
  waitUntil((Gyro.heading(degrees) >= turnamount));
  LFM.stop();
  RFM.stop();
  LBM.stop();
  RBM.stop();
}

bool cameraTaskEnable = false;
int cameraTask() {
  Brain.Screen.render(true,true);
  while(cameraTaskEnable){
    Controller1.Screen.clearLine(1);
    Controller1.Screen.clearLine(2);
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print(LFM.torque());
    Controller1.Screen.print(LBM.torque());
    Controller1.Screen.newLine();
    Controller1.Screen.print(RFM.torque());
    Controller1.Screen.print(RBM.torque());
    /*Controller1.Screen.print(Gyro.heading(degrees));
    Controller1.Screen.newLine();
    Vision5.takeSnapshot(Vision5__REDBOX);
    if (Vision5.objectCount > 0) {
      if (Vision5.objects[1].centerX < 0){
        Controller1.Screen.print("< 100");
      }
      else if (Vision5.objects[0].centerX > 0){
        Controller1.Screen.print("> 100");
      }
    }

    else {
      Controller1.Screen.print("No Red Object");
    }*/
    task::sleep(150);
  }
  return(1);
}

void autonomous() { 
  task task1 = task(cameraTask); 
  cameraTaskEnable = true;
  
  drivevelocity(25);
  
  driveforward(2000, true);
//  turnto(135);
//  driveforward(2000, true);



  //Acutrate turning conversions

  /*float moveammount = 100; // in cm
  const float CIRCUMFERENCE = 31.919; //in cm
  float distanceholo = moveammount * 1.41; //
  float conversionammount = distanceholo / CIRCUMFERENCE * 360;
  driveforward(conversionammount, true);
  wait(2,msec);
  drivereverse(conversionammount, true); */
  
  //Original time based auton

  /*Lintake.spin(reverse);
  Rintake.spin(reverse);
  wait(2000,msec);
  Lintake.stop();
  Rintake.stop();
  wait(200,msec);
  rightstrafetime = 1600;
  straferight();
  wait(200,msec);
  turnlefttime = 700;
  turnleft();
  wait(200,msec);
  Lintake.spin(reverse);
  Rintake.spin(reverse);
  LFM.setVelocity(40,percent);
  RFM.setVelocity(40,percent);
  LBM.setVelocity(40,percent);
  RBM.setVelocity(40,percent);
  LFM.spin(reverse);
  LBM.spin(forward);
  RFM.spin(reverse);
  RBM.spin(forward);
  wait(1300,msec);
  Llift.spin(forward);
  Rlift.spin(forward);
  wait(700,msec);
  RFM.stop();
  RBM.stop(); 
  LFM.stop();
  LBM.stop();
  wait(500,msec);
  Lintake.stop();
  Rintake.stop();
  wait(1000,msec);
  Llift.stop();
  Rlift.stop(); */
}

void usercontrol(void) {
  cameraTaskEnable = true;
  Lintake.setPosition(0,degrees);
  Rintake.setPosition(0,degrees);
  Llift.setPosition(0,degrees);
  Rintake.setPosition(0,degrees);
  LFM.setPosition(0,degrees);
  RFM.setPosition(0,degrees);
  LBM.setPosition(0,degrees);
  RBM.setPosition(0,degrees);

  while (true) {
    float LFMF = -Controller1.Axis3.position() - Controller1.Axis1.position() - Controller1.Axis4.position();
    float RFMF = -Controller1.Axis3.position() + Controller1.Axis1.position() + Controller1.Axis4.position();
    float LBMF = Controller1.Axis3.position() + Controller1.Axis1.position() - Controller1.Axis4.position();
    float RBMF = Controller1.Axis3.position() - Controller1.Axis1.position() + Controller1.Axis4.position();
    
    LFM.setVelocity(LFMF,percent);
    RFM.setVelocity(RFMF,percent);
    LBM.setVelocity(LBMF,percent);
    RBM.setVelocity(RBMF,percent);
    LFM.spin(forward);
    RFM.spin(forward);
    LBM.spin(forward);
    RBM.spin(forward);

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

  Gyro.calibrate();

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
