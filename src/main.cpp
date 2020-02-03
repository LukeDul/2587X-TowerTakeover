#include "main.h"

//****************************|Initialize Function|*********************
//info: Brake shorts the motors, hold uses PID.

void initialize()
{
	pros::lcd::initialize();


}

//****************************|Disabled Function|*************************

void disabled() {}

//****************************|Competition Initialize Function|***********

void competition_initialize() {}

//****************************|Auton Helper Functions|*********************

//deploys intake and tray


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
//	tray_intake_deploy();

	translate(300, -127);

	pros::delay(500);

	translate(1000, 127);

	pros::delay(1000);

	antitip_deploy();
}

void outtake_stack()
{
	intake.moveRelative(90,50);
	stack_macro();
	release_macro();
}

auto chassisauto = okapi::ChassisControllerBuilder()
		.withMotors({frontLeft, backLeft}, {frontRight, backRight}) // left motor is 1, right motor is 2 (reversed)
		.withGains(
			 {0.001, 0.001, 0.00009}, // Distance controller gains 0.005, 0, 0.001
			 {0.00075, 0.001, 0.00009}, // Turn controller gains
			 {0.001, 0.001, 0.0001}  // Angle controller gains (helps drive straight)
		 )
		.withDimensions(AbstractMotor::gearset::green, {{4.125_in, 9.1_in}, okapi::imev5GreenTPR})
		.withOdometry() // use the same scales as the chassis (above)
		.withMaxVelocity(200)
		.buildOdometry(); // build an odometry chassis

auto myChassis =
  okapi::ChassisControllerBuilder()
    .withMotors({frontLeft, backLeft}, {frontRight, backRight})
    .withDimensions(okapi::AbstractMotor::gearset::green, {{4.125_in, 13.21875_in}, okapi::imev5GreenTPR})
    .build();

		auto fast =
		  AsyncMotionProfileControllerBuilder()
		    .withLimits({
		      1.1,  //max velocity
		      2.5,  //max acceleration
		      10.0  //max jerk
		    })
		    .withOutput(myChassis)
		    .buildMotionProfileController();

		auto slow =
		  AsyncMotionProfileControllerBuilder()
		    .withLimits({
		      0.3,  //max velocity
		      2.0,  //max acceleration
		      10.0  //max jerk
		    })
		    .withOutput(myChassis)
		    .buildMotionProfileController();

void robot_deploy()
{
	myChassis->moveDistance(0.5_ft);
	setIntake(-200);
	myChassis->moveDistance(-0.5_ft);
	setIntake(0);
}

void blue_big_zone(){

}

void red_small_zone(){

	slow->generatePath({
	  {0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
	  {4_ft, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
	  "Cube Line"
	);

	setIntake(127);
	lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	slow->setTarget("Cube Line");
	slow->waitUntilSettled();

	fast->generatePath({
		{0_ft, 0_ft, 0_deg},
		{3.1_ft, 0_ft, 0_deg}},
		"Goal Align Pt 1"
	);
	fast->setTarget("Goal Align Pt 1", 1);
	fast->waitUntilSettled();

	chassisauto->turnAngle(136_deg);

	fast->generatePath({
		{0_ft, 0_ft, 0_deg},
		{0.7_ft, 0_ft, 0_deg}},
		"Goal Align Pt 2"
	);
	fast->setTarget("Goal Align Pt 2");
	fast->waitUntilSettled();

	intake.moveRelative(90,50);
	stack_macro();
	release_macro();


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
	robot_deploy();
	red_small_zone();
}
//****************************|Operation Control|****************************


const int NUM_HEIGHTS = 2;

const int height1 = 1000;
const int height2 = 1700;
const double kP = 0.004;
const double kI = 0.000001;
const double kD = 0.000082;

okapi::ControllerButton btnUp(okapi::ControllerDigital::L1);
okapi::ControllerButton btnDown(okapi::ControllerDigital::L2);
auto liftControl = okapi::AsyncPosControllerBuilder()
		.withMotor(-3)
			.withGains({kP, kI, kD})
		.build();
const int heights[NUM_HEIGHTS] = {height1, height2};

//****************************|Operation Control|****************************

void opcontrol()
{
	driveLeftBack.set_brake_mode		(pros::E_MOTOR_BRAKE_BRAKE);
	driveLeftFront.set_brake_mode		(pros::E_MOTOR_BRAKE_BRAKE);
	driveRightBack.set_brake_mode		(pros::E_MOTOR_BRAKE_BRAKE);
	driveRightFront.set_brake_mode	(pros::E_MOTOR_BRAKE_BRAKE);
	intakeLeft.set_brake_mode				(pros::E_MOTOR_BRAKE_HOLD);
	intakeRight.set_brake_mode			(pros::E_MOTOR_BRAKE_HOLD);

	while(true)
	{
	 lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	if (btnUp.changedToPressed()) {
			liftControl->setTarget(1700);
		} else if (btnDown.changedToPressed() ){
			liftControl->setTarget(0);
		}

		driveControl();

		intakeControl();

		anglerControl();

		pros::lcd::print(0, "Angler val: %f", anglerPosition());
		pros::lcd::print(1, "Lift val: %f", liftPosition());

		pros::delay(10);
	}
}
