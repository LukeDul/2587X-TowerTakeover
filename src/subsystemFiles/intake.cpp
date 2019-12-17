#include "main.h"

//helper functions
void setIntake(int power){
  intakeRight.move_voltage(power);
	intakeLeft.move_voltage(power);
}

 //driver control functions
void setIntakeMotors()
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
