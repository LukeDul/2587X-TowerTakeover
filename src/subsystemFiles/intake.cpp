#include "main.h"

//****************************|Helper Functions|********************************
void setIntake(int power){
  intakeRight.move_voltage(power);
	intakeLeft.move_voltage(power);
}

//****************************|Operation Control Function|********************************
void intakeControl()
{
  int intakePower = 127*(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)-controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1));

  int intakeSlow = 60*(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)-controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1));

  if((liftPosition()>2600 && liftPosition() < 2900) || liftPosition() > 3100)
  {
    setIntake(intakeSlow);
  }

  else
  {
    setIntake(intakePower);
  }

}
