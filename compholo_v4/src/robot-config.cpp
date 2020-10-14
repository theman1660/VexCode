#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LFM = motor(PORT15, ratio18_1, false);
motor RFM = motor(PORT2, ratio18_1, false);
motor LBM = motor(PORT13, ratio18_1, false);
motor RBM = motor(PORT12, ratio18_1, false);
motor Lintake = motor(PORT10, ratio18_1, false);
motor Rintake = motor(PORT20, ratio18_1, true);
motor Rlift = motor(PORT19, ratio18_1, false);
motor Llift = motor(PORT9, ratio18_1, true);
/*vex-vision-config:begin*/
signature Vision5__BLUEBOX = signature (1, -2369, -1203, -1786, 6143, 10751, 8446, 2.5, 0);
signature Vision5__REDBOX = signature (3, 7233, 10591, 8912, -729, 309, -210, 2, 0);
vision Vision5 = vision (PORT21, 50, Vision5__BLUEBOX, Vision5__REDBOX);
/*vex-vision-config:end*/
inertial Gyro = inertial(PORT14);
sonar RangeL = sonar(Brain.ThreeWirePort.A);
sonar RangeR = sonar(Brain.ThreeWirePort.C);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}