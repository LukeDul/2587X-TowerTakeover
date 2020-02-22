#include "main.h"

//****************************|Helper Functions|********************************
void setIntake(int power){
  intakeRight = power;
	intakeLeft = power;
}


//****************************|Operation Control Function|********************************
void intakeControl()
{

  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
  {
    setIntake(127);
    set_lift(-8);
  }
  else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
  {
    setIntake(-127);
  }else
  {
    setIntake(0);

  }
  if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)&&controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
  {
    setIntake(-100);
  }

}
