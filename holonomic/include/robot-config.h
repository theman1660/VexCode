using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern motor LFM;
extern motor RFM;
extern motor LBM;
extern motor RBM;
extern controller Controller1;
extern motor Lintake;
extern motor Rintake;
extern signature Vis__SIG_1;
extern signature Vis__SIG_2;
extern signature Vis__SIG_3;
extern signature Vis__SIG_4;
extern signature Vis__SIG_5;
extern signature Vis__SIG_6;
extern signature Vis__SIG_7;
extern vision Vis;
extern motor Rlift;
extern motor Llift;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );