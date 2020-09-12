/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\fletc                                            */
/*    Created:      Sat Sep 12 2020                                           */
/*    Description:  V5 project                                                */
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
// Gyro                 inertial      14              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

/////////////////
//  Variables  //
/////////////////

/////////////////
//    Task1    //
/////////////////

/////////////////
//  MainTask  //
/////////////////
int main() {
  vexcodeInit();
  Gyro.calibrate();
  while(true)
  {
    float rotationammount = Gyro.heading(degrees);
    float rotationammountnow = 0;

    float LFMF = -Controller1.Axis3.position() - Controller1.Axis1.position() - Controller1.Axis4.position();
    float RFMF = -Controller1.Axis3.position() + Controller1.Axis1.position() + Controller1.Axis4.position();
    float LBMF = Controller1.Axis3.position() + Controller1.Axis1.position() - Controller1.Axis4.position();
    float RBMF = Controller1.Axis3.position() - Controller1.Axis1.position() + Controller1.Axis4.position();

    LFM.setVelocity(LFMF,percent);
    RFM.setVelocity(RFMF,percent);
    LBM.setVelocity(LBMF,percent);
    RBM.setVelocity(RBMF,percent);

    if(Controller1.Axis3.position(percent) > 10)
    {
      rotationammountnow = rotationammount;

      while(rotationammount > rotationammountnow + 5) //more than so must turn left
      {
      LFM.setVelocity(LFMF,percent);
      RFM.setVelocity(RFMF-10,percent);
      LBM.setVelocity(LBMF,percent);
      RBM.setVelocity(RBMF-10,percent);
      }
      while(rotationammount < rotationammountnow + 5) //less than so must turn right
      {
      LFM.setVelocity(LFMF-10,percent);
      RFM.setVelocity(RFMF,percent);
      LBM.setVelocity(LBMF-10,percent);
      RBM.setVelocity(RBMF,percent);
      }

      LFM.spin(forward);
      RFM.spin(forward);
      LBM.spin(forward);
      RBM.spin(forward);
    }
  } 
}
