#include "vex.h"

using namespace vex;

competition Competition;


bool liftTaskEnable;
int lifttask() {
  while(liftTaskEnable){
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
    task::sleep(100);
  }
  return(1);
}
bool cameraTaskEnable;
int cameraTask() {
  Brain.Screen.render(true,true);
  while(cameraTaskEnable){
    Controller1.Screen.clearLine(1);
    Controller1.Screen.clearLine(2);
    Controller1.Screen.setCursor(1, 1);
    //Controller1.Screen.print(LFM.torque());
    //Controller1.Screen.print(LBM.torque());
    //Controller1.Screen.print(RFM.torque());
    //Controller1.Screen.print(RBM.torque());
    Controller1.Screen.print("LeftDis");
    Controller1.Screen.print(RangeL.distance(mm));
    Controller1.Screen.newLine();
    Controller1.Screen.print("RightDis");
    Controller1.Screen.print(RangeR.distance(mm));
    Controller1.Screen.newLine();
    Controller1.Screen.print(Gyro.yaw());

    Brain.Screen.setCursor(1,1);
    Brain.Screen.print(Gyro.heading(degrees));
    Brain.Screen.newLine();
    // Vision5.takeSnapshot(Vision5__REDBOX);
  /*if (Vision5.objectCount > 0) {
      if (Vision5.objects[1].centerX < 0){
        Brain.Screen.print("< 100");
      } 
      else if (Vision5.objects[0].centerX > 0){
        Brian.Screen.print("> 100");
      }
    }

    else {
      Brain.Screen.print("No Red Object");
    }*/
    task::sleep(150);
  }
  return(1);
}

void pre_auton(void) {
  vexcodeInit();
  Gyro.calibrate();
  waitUntil(Gyro.isCalibrating() == false);

  task task2 = task(lifttask);
  task task1 = task(cameraTask); 
  cameraTaskEnable = true;
  liftTaskEnable = true;
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

void liftout(int movementcount, bool stopmode) {
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

void turnrightto(int turnamount)
{
  drivevelocity(25);
  LFM.spin(reverse);
  RFM.spin(forward);
  LBM.spin(forward);
  RBM.spin(reverse);
  waitUntil((Gyro.heading(degrees) >= turnamount-20));
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

void turnleftto(int turnamount)
{
  drivevelocity(10);
  LFM.spin(forward);
  RFM.spin(reverse);
  LBM.spin(reverse);
  RBM.spin(forward);
  wait(300, msec);
  waitUntil((Gyro.yaw() <= turnamount));
  LFM.stop();
  RFM.stop();
  LBM.stop();
  RBM.stop();
  drivevelocity(25);
}

void autonomous() { 
  Gyro.calibrate();
  waitUntil(Gyro.isCalibrating() == false);
  drivevelocity(25);
  intakein(360,true);
  wait(500,msec);
  straferight(500 ,true);
  turnleftto(-45);
  driveforward(750, false);
  Lintake.spin(forward);
  Rintake.spin(reverse);
  wait(3000, msec);
  Lintake.stop();
  Rintake.stop();
  liftout(2000, true);
  intakein(1500, true);
  driveforward(-200, true);
}

void usercontrol(void) {
  Lintake.setPosition(0,degrees);
  Rintake.setPosition(0,degrees);
  Llift.setPosition(0,degrees);
  Rintake.setPosition(0,degrees);
  LFM.setPosition(0,degrees);
  RFM.setPosition(0,degrees);
  LBM.setPosition(0,degrees);
  RBM.setPosition(0,degrees);

  while (true) {
    LFM.setVelocity((Controller1.Axis3.position() + Controller1.Axis4.position() + Controller1.Axis1.position()),percent);
    LBM.setVelocity((Controller1.Axis3.position() - Controller1.Axis4.position() + Controller1.Axis1.position()),percent);
    RFM.setVelocity(((-Controller1.Axis3.position()) + Controller1.Axis4.position() + Controller1.Axis1.position()),percent);
    RBM.setVelocity(((-Controller1.Axis3.position()) - Controller1.Axis4.position() + Controller1.Axis1.position()),percent);

    LFM.spin(forward);
    RFM.spin(forward);
    LBM.spin(forward);
    RBM.spin(forward);
  }
  wait(20,msec);
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(100, msec);
  }
}
