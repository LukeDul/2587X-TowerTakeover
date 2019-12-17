#include "main.h"
//bro yus
//****************************|Initialize Function|*********************
//info: Brake shorts the motors, hold uses PID.

void initialize()
{
	pros::lcd::initialize();
	//pros::delay(2000);//gyro delay
	pros::Task lift_macros (lift_macros_fn, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "LiftMacros");

	driveRightFront.set_brake_mode	(pros::E_MOTOR_BRAKE_COAST);
	driveRightBack.set_brake_mode		(pros::E_MOTOR_BRAKE_COAST);
	driveLeftFront.set_brake_mode		(pros::E_MOTOR_BRAKE_COAST);
	driveLeftBack.set_brake_mode		(pros::E_MOTOR_BRAKE_COAST);
	intakeRight.set_brake_mode			(pros::E_MOTOR_BRAKE_HOLD);
	intakeLeft.set_brake_mode				(pros::E_MOTOR_BRAKE_HOLD);
	angler.set_brake_mode						(pros::E_MOTOR_BRAKE_HOLD);
	lift.set_brake_mode							(pros::E_MOTOR_BRAKE_HOLD);
}

//****************************|Disabled Function|*************************

void disabled() {}

//****************************|Competition Initialize Function|***********

void competition_initialize() {}

//****************************|Auton Helper Functions|*********************

//deploys intake and tray
void tray_intake_deploy()//preload cannot be in front of robot
{//delays could be less
	setIntake(-12000);

	pros::delay(1000);

	setIntake(0);

	pros::delay(1000);
}

//deploys anti-tips
void antitip_deploy()//will not work if against wall
{//delays could be less
	move_angler_up(1000);

	pros::delay(800);

	move_angler_down(0);
}

//****************************|Auton Functions|****************************

//scores one cube in any zone
void one_point()
{//delays could be less
	tray_intake_deploy();

	translate(300, -127);

	pros::delay(500);

	translate(1000, 127);

	pros::delay(1000);

	antitip_deploy();
}

void blue_small_zone()
{
tray_intake_deploy();

 //intake 4 cubes
 setIntake(12000);

 translate(1500, 40);

 pros::delay(2000);

 translate(1200, 40);

 setIntake(0);

 // //drive back to wall

 translate(2700, -60);

 translate(1000, 40);

 left_translate(600, -40);

	translate(600, -40);

	left_translate(600, -40);

// drive forward
//left side turn to align with goal blue_small_zone
// turn intake on
// drive forward an intake cube
// pause
// drive forward and stack
// drive back and release stack

}

void blue_big_zone(){

}

void red_small_zone(){

}

void red_big_zone(){

}

//****************************|Auton Main|****************************
//Auton options:
//blue_small_zone();
//blue_big_zone();
//red_small_zone();
//red_big_zone
//one_point();

void autonomous()
{
	one_point();
}

//****************************|Operation Control|****************************

void opcontrol()
{
	driveLeftBack.set_brake_mode		(pros::E_MOTOR_BRAKE_BRAKE);
	driveLeftFront.set_brake_mode		(pros::E_MOTOR_BRAKE_BRAKE);
	driveRightBack.set_brake_mode		(pros::E_MOTOR_BRAKE_BRAKE);
	driveRightFront.set_brake_mode	(pros::E_MOTOR_BRAKE_BRAKE);
	intakeLeft.set_brake_mode				(pros::E_MOTOR_BRAKE_BRAKE);
	intakeRight.set_brake_mode			(pros::E_MOTOR_BRAKE_BRAKE);

	while(true)
	{
		setDriveMotors();
		setIntakeMotors();
		anglerControl();
		pros::lcd::print(0, "Angler val: %f", anglerPosition());
		pros::lcd::print(1, "Lift val: %f", liftPosition());
		pros::delay(10);
	}
}
