#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LFM = motor(PORT11, ratio18_1, true);
motor RFM = motor(PORT1, ratio18_1, false);
motor LBM = motor(PORT13, ratio18_1, false);
motor RBM = motor(PORT12, ratio18_1, true);
controller Controller1 = controller(primary);
motor Lintake = motor(PORT10, ratio18_1, false);
motor Rintake = motor(PORT20, ratio18_1, true);
/*vex-vision-config:begin*/
vision Vis = vision (PORT5, 50);
/*vex-vision-config:end*/
motor Rlift = motor(PORT19, ratio18_1, false);
motor Llift = motor(PORT9, ratio18_1, true);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}