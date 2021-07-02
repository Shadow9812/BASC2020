#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
#include <webots/PositionSensor.hpp>
#include <webots/Gyro.hpp>

using namespace webots;

//// Pamuditha variables //////////////
double angle = 0.0, gyroThresh = 0.5, gyroThresh2=0.0;
bool inclined=0, top=0, rampTurned=0, direction=0;
//////////////////////////////////////

Robot *robot = new Robot();
const int timeStep = (int)robot->getBasicTimeStep();

Motor *l_motor = robot->getMotor("left_motor");
Motor *r_motor = robot->getMotor("right_motor");

PositionSensor *l_enc = robot->getPositionSensor("left_encoder");
PositionSensor *r_enc = robot->getPositionSensor("right_encoder");

DistanceSensor *l3 = robot->getDistanceSensor("l3");
DistanceSensor *l2 = robot->getDistanceSensor("l2");
DistanceSensor *l1 = robot->getDistanceSensor("l1");
DistanceSensor *l0 = robot->getDistanceSensor("l0");
DistanceSensor *r0 = robot->getDistanceSensor("r0");
DistanceSensor *r1 = robot->getDistanceSensor("r1");
DistanceSensor *r2 = robot->getDistanceSensor("r2");
DistanceSensor *r3 = robot->getDistanceSensor("r3");

DistanceSensor *lc = robot->getDistanceSensor("l_corner");
DistanceSensor *rc = robot->getDistanceSensor("r_corner");

DistanceSensor *lft = robot->getDistanceSensor("left_front_tof");
DistanceSensor *lbt = robot->getDistanceSensor("left_back_tof");
DistanceSensor *rft = robot->getDistanceSensor("right_front_tof");
DistanceSensor *rbt = robot->getDistanceSensor("right_back_tof");
DistanceSensor *ct = robot->getDistanceSensor("center_tof");

Gyro *gyro = robot->getGyro("gyro");

void initialize_devices(){
  l_motor->setPosition(INFINITY);
  r_motor->setPosition(-INFINITY);
  l_motor->setVelocity(0.0);
  r_motor->setVelocity(0.0);
  
  l_enc->enable(timeStep);
  r_enc->enable(timeStep);
  
  l3->enable(timeStep);
  l2->enable(timeStep);
  l1->enable(timeStep);
  l0->enable(timeStep);
  r0->enable(timeStep);
  r1->enable(timeStep);
  r2->enable(timeStep);
  r3->enable(timeStep);
  
  lc->enable(timeStep);
  rc->enable(timeStep);
  
  lft->enable(timeStep);
  lbt->enable(timeStep);
  rft->enable(timeStep);
  rbt->enable(timeStep);
  ct->enable(timeStep);
  
  gyro->enable(timeStep);
}

void disable_devices(){
  l_enc->disable();
  r_enc->disable();
  
  l3->disable();
  l2->disable();
  l1->disable();
  l0->disable();
  r0->disable();
  r1->disable();
  r2->disable();
  r3->disable();
  
  lc->disable();
  rc->disable();
  
  lft->disable();
  lbt->disable();
  rft->disable();
  rbt->disable();
  ct->disable();
  
  gyro->disable();
}

void stopRobot(){
  l_motor->setVelocity(0.0);
  r_motor->setVelocity(0.0);
}

void delay(int d){
  while (d--){
    robot->step(timeStep);
  }
}

void moveDistance(double dist){
  double encPos = r_enc->getValue() + l_enc->getValue();
  l_motor->setVelocity(5.0);
  r_motor->setVelocity(5.0);
  while (r_enc->getValue() + l_enc->getValue() - encPos < dist){
    robot->step(timeStep);
  }
  stopRobot();
  return;
}

void turnLeft(){
  double encPos = r_enc->getValue();
  l_motor->setVelocity(-5.0);
  r_motor->setVelocity(5.0);
  while (r_enc->getValue() - encPos < 3.5){
    robot->step(timeStep);
  }
  stopRobot();
  return;
}

void turnRight(){
  double encPos = l_enc->getValue();
  r_motor->setVelocity(-5.0);
  l_motor->setVelocity(5.0);
  while (l_enc->getValue() - encPos < 3.5){
    robot->step(timeStep);
  }
  stopRobot();
  return;
}

void lineFollow(){}

void wallFollow(){}

//////////////////////////////////////////////// PAMUDITHA & YOMALI ///////////////////////////////////////////////////////
void readGyro(){
   double gyroOut = -gyro->getValues()[0];
   if (gyroOut > gyroThresh2 || gyroOut < -gyroThresh2) {angle += gyroOut; }
   if ((not top) && (not inclined) && (angle>0.1)) inclined=true;
   else if ((not top) && (inclined) && (angle>-3.0 && angle<0.1)) {inclined=false; top=true;}
   else if ((top) && not(inclined) && (angle<-3.0)) inclined=true;
   else if ((top) && (inclined) && (angle>-3.0 && angle<0.1)) {inclined=false; top=false;}
}

bool isRampEdge(){
  if (ct->getValue() < 200) return true;
  double gyroOut = -gyro->getValues()[0];
  if (gyroOut > gyroThresh || gyroOut < -gyroThresh) return true;
   return false;
}

void rampNavigation(bool direction){
  readGyro();
  std::cout << angle << " inclined:" << inclined << " top:" << top << std::endl;
  if (not isRampEdge()){
    if ((lc->getValue() < 900) && (rc->getValue() < 900)) {
      if (not rampTurned) {
        std::cout << "HELLO" << std::endl;
        moveDistance(6.0);
        if (direction) turnLeft();
        else turnRight();
        rampTurned = true;
      }
      else moveDistance(0.5);
    }
    else moveDistance(0.5);
  }
  else moveDistance(0.5);
  //std::cout << "Hello" << std::endl;
}

// Left and Right turn encoder values are different ---CHECK

int count=0, i=0;
bool readings[50];

void pillarCount(bool direction){
  if (direction) {
    if (lft->getValue()<900) readings[i]=true;
    i++;
  }
  else {
    if (rft->getValue()<900) readings[i]=true;
    i++;
  }
}

bool evaluatePillars(){
  for (int i=0; i<49; i++){
    if (((not readings[i]) && readings[i+1]) || (readings[i] && (not readings[i+1]))) count++;
  }
  if (count==4) return true;
  else return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////

void rampPathCorrection(){}

void escapeGates(){}

int main(int argc, char **argv) {

  initialize_devices();
  
  while (robot->step(timeStep) != -1) {
    //rampNavigation(direction);
    if (direction && (lc->getValue()<900)) {std::cout << i << ' ' << evaluatePillars() << std::endl; break;}
    else if (rc->getValue()<900) {std::cout << i << ' ' << evaluatePillars() << std::endl; break;}
    else {pillarCount(direction); moveDistance(0.5);}
  };
  
  disable_devices();

  delete robot;
  return 0;
}
