using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor LFM;
extern motor RFM;
extern motor LBM;
extern motor RBM;
extern motor Lintake;
extern motor Rintake;
extern motor Rlift;
extern motor Llift;
extern signature Vision5__BLUEBOX;
extern signature Vision5__SIG_2;
extern signature Vision5__REDBOX;
extern signature Vision5__SIG_4;
extern signature Vision5__SIG_5;
extern signature Vision5__SIG_6;
extern signature Vision5__SIG_7;
extern vision Vision5;
extern inertial Gyro;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );