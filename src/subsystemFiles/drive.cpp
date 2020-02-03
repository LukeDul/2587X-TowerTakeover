#include "main.h"

//****************************|Helper Functions|********************************
void setDrive(int left, int right)
{
  driveLeftBack   = left;
  driveLeftFront  = left;
  driveRightBack  = right;
  driveRightFront = right;
}

void resetDriveEncoders()
{
  driveLeftBack.tare_position();
  driveLeftFront.tare_position();
  driveRightBack.tare_position();
  driveRightFront.tare_position();
}

double avgDriveEncoderValue()
{
  return (fabs(driveLeftFront.get_position())+
         fabs(driveLeftBack.get_position())+
         fabs(driveRightFront.get_position())+
         fabs(driveRightBack.get_position())) / 4;
}

double avgRightDrive()
{
  return (fabs(driveRightFront.get_position())+fabs(driveRightBack.get_position()))/2;
}

double avgLeftDrive()
{
  return (fabs(driveLeftFront.get_position())+fabs(driveLeftBack.get_position()))/2;
}

double currDriveValue()
{
  return (driveLeftFront.get_position()+
         driveLeftBack.get_position()+
         driveRightFront.get_position()+
         driveRightBack.get_position()) / 4;
}

//****************************|Auton Functions|*********************************



void translate(int units, int voltage)
{
  //define direction based on units provided
  int direction = abs(units)/units; // either 1 or -1
   //reset motor encoders
   resetDriveEncoders();
   //drive forward until units are reached
   while(avgDriveEncoderValue()<abs(units)) {
     setDrive(voltage * direction, voltage * direction);
     pros::delay(10);
   }
   //brief brake
   setDrive(-10, -10);
   pros::delay(50);//edit

   //set drive back to neutral
   setDrive(0, 0);
}

void right_translate(int units, int voltage)
{
  int direction = abs(units)/units;

  driveLeftBack.set_brake_mode		(pros::E_MOTOR_BRAKE_BRAKE);
  driveLeftFront.set_brake_mode		(pros::E_MOTOR_BRAKE_BRAKE);

  resetDriveEncoders();

  while(avgRightDrive()<abs(units))
  {
    setDrive(0, voltage * direction);

    pros::delay(10);
  }

  setDrive(0, -10);

  pros::delay(50);

  setDrive(0, 0);

  driveLeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  driveLeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void left_translate(int units, int voltage)
{
  int direction = abs(units)/units;

  driveRightBack.set_brake_mode		(pros::E_MOTOR_BRAKE_BRAKE);
	driveRightFront.set_brake_mode	(pros::E_MOTOR_BRAKE_BRAKE);

  resetDriveEncoders();

  while(avgLeftDrive()<abs(units))
  {
    setDrive(voltage * direction, 0);
    pros::delay(10);
  }

  setDrive(-10, 0);

  pros::delay(50);

  setDrive(0, 0);

  driveRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  driveRightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}


//****************************|Auton Functions|*********************************

void driveControl()
{
  int leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int rightJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

  if(abs(leftJoystick)<10)
    leftJoystick = 0;

  if(abs(rightJoystick)<10)
    rightJoystick = 0;

  setDrive(leftJoystick, rightJoystick);
}
