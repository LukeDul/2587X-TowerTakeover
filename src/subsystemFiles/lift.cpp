#include "main.h"


//****************************|Helper Functions|****************************

void set_lift(int power)
{
  lift = power;
}

void stop_lift()
{
  lift = 0;
}

double liftPosition()
{
  return lift.get_position();
}

//****************************|Position Functions|****************************
//terminology: ml_ = move_lift_

void ml_down_position()
{
  while(liftPosition()>0){
    set_lift(-127);

    pros::delay(10);
  }
  stop_lift();
  angler_down();
}

void ml_low_score_position()
{
  double target_position  = 2700;

  if(liftPosition()<target_position)
  {
    move_angler(1600,12000);

    while(liftPosition()<target_position)
    {
      if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
        break;

      set_lift(127);

      pros::delay(10);
    }
  }

  else if(liftPosition()>target_position)
  {
    move_angler(1600,12000);

    while(liftPosition()>target_position)
    {
      if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
      {
        break;
      }

      set_lift(-127);

      pros::delay(10);
    }
  }
  stop_lift();
}

void ml_low_descore_position()
{
  double target_position  = 2400;

  if(liftPosition()<target_position)
  {
    move_angler(1600,12000);

    while(liftPosition()<target_position)
    {
      set_lift(127);
      pros::delay(10);

      if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
      {
        break;
      }
    }
  }

  else if(liftPosition()>target_position)
  {
    while(liftPosition()>target_position)
    {
      set_lift(-127);
      pros::delay(10);

      if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
        break;
    }
  }
  stop_lift();
}

void ml_medium_score_position()
{
  double target_position = 3200;
  move_angler(1800,12000);

  while(liftPosition()<target_position)
  {
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
      break;

    if(liftPosition()<target_position)
      set_lift(127);

    else if(liftPosition()>target_position)
      set_lift(-127);

    pros::delay(10);
  }
  stop_lift();
}

void ml_medium_descore_position()
{
  double target_position = 3000;

  if(liftPosition()<target_position)
  {
    move_angler(1800,12000);

    while(liftPosition()<target_position)
    {
      set_lift(127);

      if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
        break;

      pros::delay(10);
    }
  }

  else if(liftPosition()>target_position)
  {
    while(liftPosition()>target_position)
    {
      set_lift(-127);

      if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
        break;

      pros::delay(10);
    }
  }
  stop_lift();
}

//****************************|Lift Macros|****************************
// terminology: lm_ = lift_macro_

void lm_score_low_position()
{
  int target_position = 2300;

    while(liftPosition()>0)
    {
      set_lift(-80);

      intakeLeft.move_voltage(-6000);
      intakeRight.move_voltage(-6000);

      if(liftPosition() > 1800)
      {
        setDrive(-127,-127);
      }

      else
      {
        setDrive(0,0);
      }

      if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
        break;

      pros::delay(10);
    }
    angler_down();
    
    stop_lift();

    intakeLeft.move_voltage(0);
    intakeRight.move_voltage(0);
}


//****************************|Lift Operation Control|****************************

void lift_macros_fn(void* param)
{

  while(true)
  {
     bool isLiftMoving = false;

     if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && isLiftMoving == false)
     {
       isLiftMoving = true;
     }

     if(isLiftMoving)
     {
       ml_low_score_position();

       isLiftMoving = false;
     }

     if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) && isLiftMoving == false)
     {
       isLiftMoving = true;
     }

     if(isLiftMoving)
     {
       ml_down_position();

       isLiftMoving = false;
     }

     if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP) && isLiftMoving == false)
     {
       isLiftMoving = true;
     }

     if(isLiftMoving)
     {
       ml_medium_score_position();

       isLiftMoving = false;
     }

     if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) && isLiftMoving == false)
     {
       isLiftMoving = true;
     }

     if(isLiftMoving)
     {
       ml_low_descore_position();

       isLiftMoving = false;
     }

     if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) && isLiftMoving == false)
     {
       isLiftMoving = true;
     }

     if(isLiftMoving)
     {
       ml_medium_descore_position();

       isLiftMoving = false;
     }

     if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)  && isLiftMoving == false)
     {
       isLiftMoving = true;
     }

     if(isLiftMoving)
     {
       lm_score_low_position();

       isLiftMoving = false;
     }

    pros::delay(10);

   }
}
