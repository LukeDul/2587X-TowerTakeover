#include "main.h"

//****************************|Helper Functions|********************************
void setIntake(int power){
  intakeRight = power;
	intakeLeft = power;
}


//****************************|Operation Control Function|********************************
void intakeControl()
{
  int intakePower = 127*(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)-controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1));

  int intakeSlow = 60*(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)-controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1));


   setIntake(intakePower);

}
