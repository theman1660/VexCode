/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Robotics                                         */
/*    Created:      Wed May 20 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LFM                  motor         11              
// RFM                  motor         1               
// LBM                  motor         13              
// RBM                  motor         12              
// Controller1          controller                    
// Lintake              motor         10              
// Rintake              motor         20              
// Vis                  vision        5               
// Rlift                motor         19              
// Llift                motor         9               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

void forwards(){
  LFM.spin(forward);
  wait(1, seconds);
}

int main() {
  vexcodeInit();
  Llift.setStopping(hold);
  Rlift.setStopping(hold);
  Llift.setVelocity(100,percent);
  Rlift.setVelocity(100,percent);
  Lintake.setVelocity(100,percent);
  Rintake.setVelocity(100,percent);
  
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
      Lintake.spin(forward);
      Rintake.spin(forward);
    }
    else if(Controller1.ButtonL2.pressing()){
      Lintake.spin(reverse);
      Rintake.spin(reverse);
    }
    else{
      Lintake.stop();
      Rintake.stop();
    }

  }
}
