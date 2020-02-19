#include "main.h"

//****************************|Helper Functions|****************************

void set_angler(int power)
{// switch to voltage
  angler = power;
}

void stop_angler()
{
  angler.move_voltage(0);//0.0
}

double anglerPosition()
{
  return angler.get_position();
}

void angler_down()
{
  int target_position = 0;

  while(anglerPosition()>target_position)
  {
    set_angler(-127);

    pros::delay(10);
  }
  stop_angler();
}

//****************************|Custom Movement Functions|***************

void move_angler_up(int target_position)
{
  intakeLeft.set_brake_mode				(pros::E_MOTOR_BRAKE_COAST);
  intakeRight.set_brake_mode			(pros::E_MOTOR_BRAKE_COAST);
  while (anglerPosition()<target_position)
  {
    set_angler(127);

    pros::delay(10);
  }
  stop_angler();
}

void move_angler_down(int target_position)
{
  while (anglerPosition()>target_position)
  {
    set_angler(-127);
    pros::delay(10);
  }
  stop_angler();
}

void move_angler(int target_position, int voltage)
{
  if(anglerPosition()<target_position)
  {
    while (anglerPosition()<target_position)
    {
      angler.move_voltage(voltage);

        pros::delay(10);
      }
    }

    else if(anglerPosition()>anglerPosition())
    {
      while (anglerPosition()>target_position)
      {
        angler.move_voltage(-voltage);

        pros::delay(10);
      }
    }
  stop_angler();
}

//****************************|Macro Functions|****************************

void stack_macro()
{


  double intitial_position = 1600;
  double mid_position = 3000;
  double final_position = 3900;
  double final_finalposition = 4100;
  int initSpeed = 127;
  int midSpeed = 100;
  int finalSpeed = 45;
  int finalfinalSpeed = 35;

  while(anglerPosition()<final_finalposition)
  {

    if(anglerPosition()<intitial_position)
    {
      set_angler(initSpeed);
    }

    else if(anglerPosition()<mid_position)
    {
      set_angler(midSpeed);
    }

    else if(anglerPosition()<final_position)
    {
      set_angler(finalSpeed);
    }
    else
    {
      set_angler(finalfinalSpeed);
    }


    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
    {
      move_angler(0, 4000);
      break;
    }

    pros::delay(10);
  }
  stop_angler();

  setDrive(20, 20);

  pros::delay(500);

  setDrive(0,0);
}

void release_macro()
{
  setDrive(0, 0);

  // ml_down_position();

  double anglerFinal = 0;

  while(anglerPosition()>anglerFinal)
  {
    setIntake(-127);

    setDrive(-30, -30);

    set_angler(-127);

    pros::delay(10);
  }

  stop_angler();

  setIntake(0);

  setDrive(0,0);
}
void five_cube_stack(){
    double intitial_position = 1600;
    double mid_position = 3000;
    double final_position = 4200;
    int initSpeed = 127;
    int midSpeed = 127;
    int finalSpeed = 60;

    while(anglerPosition()<final_position)
    {

      if(anglerPosition()<intitial_position)
      {
        set_angler(initSpeed);
      }

      else if(anglerPosition()<mid_position)
      {
        set_angler(midSpeed);
      }

      else
      {
        set_angler(finalSpeed);
      }

      if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
      {
        move_angler(0, 4000);
        break;
      }

      pros::delay(10);
    }
    stop_angler();

    setDrive(20, 20);

    pros::delay(500);

    setDrive(0,0);
}
void auton_release(){

  double anglerFinal = 3000;

  while(anglerPosition()>anglerFinal)
  {
    setIntake(-127);

    setDrive(-100, -100);

    set_angler(-127);

    pros::delay(10);
  }

  stop_angler();

  setIntake(0);

  setDrive(0,0);
}

void prog_release(){

  double anglerFinal = 3000;

  while(anglerPosition()>anglerFinal)
  {
    setIntake(-60);

    setDrive(-30, -30);

    set_angler(-127);

    pros::delay(10);
  }

  stop_angler();

  setIntake(0);

  setDrive(0,0);
}
//****************************|Angler Operation Control|****************************
//pros::E_CONTROLLER_DIGITAL_X up
//pros::E_CONTROLLER_DIGITAL_B down

void anglerControl()
{
  bool isTrayMoving = false;

  if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X) && isTrayMoving == false)
  {
    isTrayMoving = true;
  }

  if(isTrayMoving)
  {
    stack_macro();

    isTrayMoving = false;
  }

  if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_B) && isTrayMoving == false)
  {
    isTrayMoving = true;
  }

  if(isTrayMoving)
  {
    release_macro();

    isTrayMoving = false;
  }
}
