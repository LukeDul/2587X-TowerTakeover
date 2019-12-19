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
{// remove drive forward at end of macro? switch speeds to voltage?

  setDrive(0, 0);

  ml_down_position();//remove?

  pros::delay(500);//remove?

  double intitial_position = 1600;
  double mid_position = 3000;
  double final_position = 4200;
  int initSpeed = 127;
  int midSpeed = 100;
  int finalSpeed = 35;

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

void release_macro()
{
  setDrive(0, 0);

  ml_down_position();

  double anglerFinal = 0;

  while(anglerPosition()>anglerFinal)
  {
    setIntake(-63);

    setDrive(-30, -30);

    set_angler(-127);

    pros::delay(10);
  }

  stop_angler();

  setIntake(0);

  setDrive(0,0);
}

//****************************|Angler Operation Control|****************************

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
