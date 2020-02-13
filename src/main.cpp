#include "main.h"
okapi::Motor intake_left(2);
okapi::Motor intake_right(4);

bool runRedSmallZone = false;
bool runBlueSmallZone = false;
bool runOnePointAuton = false;

void on_left_button() {
  static bool pressed = false;
  pressed = !pressed;
  if (pressed) {
		runBlueSmallZone = false;
		runOnePointAuton = false;
		runRedSmallZone = true;
    pros::lcd::set_text(2, "Run Red Small Zone");

  } else {
    pros::lcd::clear_line(2);
  }
}

void on_center_button() {
  static bool pressed = false;
  pressed = !pressed;
  if (pressed) {
    pros::lcd::set_text(2, "Run 1 Point Auton");
		runOnePointAuton = true;
		runBlueSmallZone = false;
		runRedSmallZone = false;
  } else {
    pros::lcd::clear_line(2);
  }
}

void on_right_button() {
  static bool pressed = false;
  pressed = !pressed;
  if (pressed) {
    pros::lcd::set_text(2, "Run Blue Small Zone ");
		runBlueSmallZone = true;
		runRedSmallZone = false;
		runOnePointAuton = false;
  } else {
    pros::lcd::clear_line(2);
  }
}


//****************************|Initialize Function|*********************
//info: Brake shorts the motors, hold uses PID.
void initialize()
{
	pros::lcd::initialize();
	pros::lcd::register_btn0_cb(on_left_button);
	pros::lcd::register_btn2_cb(on_right_button);
	pros::lcd::register_btn1_cb(on_center_button);



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
	move_angler_up(500);

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

void outtake_stack()
{
	intake_left.moveRelative(-620, 200);
	intake_right.moveRelative(-620, 200);
}





const int NUM_HEIGHTS = 2;

const int height1 = 1000;
const int height2 = 1700;
const double kP = 0.004;
const double kI = 0.000001;
const double kD = 0.000082;

okapi::ControllerButton btnUp(okapi::ControllerDigital::L1);
okapi::ControllerButton btnDown(okapi::ControllerDigital::L2);
okapi::ControllerButton btnMedium(okapi::ControllerDigital::up);
auto liftControl = okapi::AsyncPosControllerBuilder()
		.withMotor(3)
		.build();
const int heights[NUM_HEIGHTS] = {height1, height2};

auto chassisauto = okapi::ChassisControllerBuilder()
		.withMotors({frontLeft, backLeft}, {frontRight, backRight})
		.withGains(
			 {0.001, 0.001, 0.00009}, // Distance controller gains 0.005, 0, 0.001
			 {0.0026, 0.0007, 0.0001}, // Turn controller gains .00075	 {0.00075, 0.0007, 0.00009}
			 {0.001, 0.001, 0.0001}  // Angle controller gains (helps drive straight)
		 )
		.withDimensions(AbstractMotor::gearset::green, {{4.125_in, 8.875_in}, okapi::imev5GreenTPR})//9.1
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
		      0.25,  //max velocity
		      2.0,  //max acceleration
		      10.0  //max jerk
		    })
		    .withOutput(myChassis)
		    .buildMotionProfileController();

void deploy_small_side(){
  angler.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	lift = -4;

	fast->generatePath({
		{0_ft, 0_ft, 0_deg},
		{1_ft, 0_ft, 0_deg}},
		"Push Cube"
	);

	fast->setTarget("Push Cube");
	fast->waitUntilSettled();


	fast->generatePath({
		{0_ft, 0_ft, 0_deg},
		{0.75_ft, 0_ft, 0_deg}},
		"align on wall"
	);

	fast->setTarget("align on wall",1);
	fast->waitUntilSettled();

	intake_left.moveVoltage(-12000);
	intake_right.moveVoltage(-12000);
	pros::delay(300);
	intake_left.moveVoltage(0);
	intake_right.moveVoltage(0);
	pros::delay(400);
	antitip_deploy();
}
void programmingSkills()
{
  deploy_small_side();

  slow->generatePath({
		{0_ft, 0_ft, 0_deg},
		{3.25_ft, 0_ft, 0_deg}},
		"Cube Line 1"
	);

	intake_left.moveVoltage(12000);
	intake_right.moveVoltage(12000);

	lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	slow->setTarget("Cube Line");
	slow->waitUntilSettled();

  chassisauto->turnAngle(15_deg);
  chassisauto->waitUntilSettled();

  fast->generatePath({
  	{0_ft, 0_ft, 0_deg},
  	{2_ft, 0_ft, 0_deg}},
		"Intake Cube 6"
  );

  fast->setTarget("Intake Cube 6");
  fast->waitUntilSettled();

  chassisauto->turnAngle(-15_deg);
  chassisauto->waitUntilSettled();

  slow->generatePath({
    {0_ft, 0_ft, 0_deg},
    {3_ft, 0_ft, 0_deg}},
    "Cube Line 2"
  );

  slow->setTarget("Cube Line 2");
  slow->waitUntilSettled();
  intake_left.moveVoltage(0);
  intake_right.moveVoltage(0);

  chassisauto->turnAngle(45_deg);
  chassisauto->waitUntilSettled();

  fast->generatePath({
  	{0_ft, 0_ft, 0_deg},
  	{1.25_ft, 0_ft, 0_deg}},
		"Drive to Blue"
  );

  fast->setTarget("Drive to Blue");
  fast->waitUntilSettled();

  stack_macro();
  pros::delay(500);
  release_macro();

  chassisauto->turnAngle(135_deg);
  chassisauto->waitUntilSettled();

  fast->generatePath({
  	{0_ft, 0_ft, 0_deg},
  	{2.25_ft, 0_ft, 0_deg}},
		"Drive to Second Cube Line"
  );

  fast->setTarget("Drive to Second Cube Line");
  fast->waitUntilSettled();

  chassisauto->turnAngle(90_deg);
  chassisauto->waitUntilSettled();

  intake_left.moveVoltage(12000);
  intake_right.moveVoltage(12000);

  slow->generatePath({
  	{0_ft, 0_ft, 0_deg},
  	{3_ft, 0_ft, 0_deg}},
		"Intake 2nd Line Part 1"
  );

  slow->setTarget("Intake 2nd Line Part 1");
  slow->waitUntilSettled();

  fast->generatePath({
    {0_ft, 0_ft, 0_deg},
    {2_ft, 0_ft, 0_deg}},
    "Drive to 2nd Line part 2"
  );

  fast->setTarget("Drive to 2nd Line part 2");
  fast->waitUntilSettled();

  slow->generatePath({
  	{0_ft, 0_ft, 0_deg},
  	{2_ft, 0_ft, 0_deg}},
		"Intake 2nd Line Part 2"
  );

  slow->setTarget("Intake 2nd Line Part 2");
  slow->waitUntilSettled();

  intake_left.moveVoltage(0);
  intake_right.moveVoltage(0);

  chassisauto->turnAngle(90_deg);
  chassisauto->waitUntilSettled();

  fast->generatePath({
    {0_ft, 0_ft, 0_deg},
    {2_ft, 0_ft, 0_deg}},
    "Drive to Tower One"
  );

  fast->setTarget("Drive to Tower One");
  fast->waitUntilSettled();

  liftControl->setTarget(1800);
  pros::delay(150);
  setIntake(-127);
  pros::delay(200);
  setIntake(0);

  //outtake into tower one
  intake_left.moveRelative(-620, 200);
	intake_right.moveRelative(-620, 200);

  liftControl->setTarget(0);

  chassisauto->turnAngle(-135_deg);
  chassisauto->waitUntilSettled();

  fast->generatePath({
    {0_ft, 0_ft, 0_deg},
    {2_ft, 0_ft, 0_deg}},
    "Drive to Tower 2"
  );

  fast->setTarget("Drive to Tower 2");
  fast->waitUntilSettled();

  liftControl->setTarget(1800);
  pros::delay(150);
  setIntake(-127);
  pros::delay(200);
  setIntake(0);

  //outtake into tower one
  intake_left.moveRelative(-620, 200);
	intake_right.moveRelative(-620, 200);

  liftControl->setTarget(0);

  chassisauto->turnAngle(90_deg);
  chassisauto->waitUntilSettled();

  fast->generatePath({
    {0_ft, 0_ft, 0_deg},
    {3_ft, 0_ft, 0_deg}},
    "Drive to Tower 3"
  );

  fast->setTarget("Drive to Tower 3");
  fast->waitUntilSettled();


  liftControl->setTarget(1800);
  pros::delay(150);
  setIntake(-127);
  pros::delay(200);
  setIntake(0);

  //outtake into tower one
  intake_left.moveRelative(-620, 200);
	intake_right.moveRelative(-620, 200);

  liftControl->setTarget(0);













}

void blue_small_zone()
{
  deploy_small_side();

	slow->generatePath({
		{0_ft, 0_ft, 0_deg},
		{3.1_ft, 0_ft, 0_deg}},
		"Cube Line"
	);

	intake_left.moveVoltage(12000);
	intake_right.moveVoltage(12000);

	lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	slow->setTarget("Cube Line");
	slow->waitUntilSettled();

	fast->generatePath({
		{0_ft, 0_ft, 0_deg},
		{1.6_ft, 0_ft, 0_deg}},
		"Goal Align Pt 1"
	);
	fast->setTarget("Goal Align Pt 1", 1);
	fast->waitUntilSettled();

	lift = 0;

	chassisauto->turnAngle(-143_deg);
	chassisauto->waitUntilSettled();

	intake_left.moveVoltage(0);
	intake_right.moveVoltage(0);

	fast->generatePath({
		{0_ft, 0_ft, 0_deg},
		{1.15_ft, 0_ft, 0_deg}},//0.75
		"Goal Align Pt 2"
	);

	fast->setTarget("Goal Align Pt 2");
	fast->waitUntilSettled();

	outtake_stack();

	pros::delay(150);

	five_cube_stack();

	auton_release();
}

void red_small_zone(){
deploy_small_side();

	slow->generatePath({
	  {0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
	  {3.1_ft, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forwardx
	  "Cube Line"
	);

	intake_left.moveVoltage(12000);
	intake_right.moveVoltage(12000);

	lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	slow->setTarget("Cube Line");
	slow->waitUntilSettled();

	fast->generatePath({
		{0_ft, 0_ft, 0_deg},
		{2_ft, 0_ft, 0_deg}},
		"Goal Align Pt 1"
	);
	fast->setTarget("Goal Align Pt 1", 1);
	fast->waitUntilSettled();

	lift = 0;

	chassisauto->turnAngle(147_deg);
	chassisauto->waitUntilSettled();

	intake_left.moveVoltage(0);
	intake_right.moveVoltage(0);

	fast->generatePath({
		{0_ft, 0_ft, 0_deg},
		{1_ft, 0_ft, 0_deg}},//0.75
		"Goal Align Pt 2"
	);

	fast->setTarget("Goal Align Pt 2");
	fast->waitUntilSettled();

	outtake_stack();

	pros::delay(150);

	five_cube_stack();

	auton_release();
}

void red_big_zone(){

}

void blue_big_zone(){

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
	// if(runRedSmallZone == true){
	// 	red_small_zone();
	// }else if (runBlueSmallZone == true){
	// 	blue_small_zone();
	// }else if(runOnePointAuton == true){
	// 	one_point();
	// }

	//blue_small_zone();
	red_small_zone();
//	one_point();
}
//****************************|Operation Control|****************************




//****************************|Operation Control|****************************

void opcontrol()
{
	lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	set_angler(0);
	driveLeftBack.set_brake_mode		(pros::E_MOTOR_BRAKE_HOLD);
	driveLeftFront.set_brake_mode		(pros::E_MOTOR_BRAKE_HOLD);
	driveRightBack.set_brake_mode		(pros::E_MOTOR_BRAKE_HOLD);
	driveRightFront.set_brake_mode	(pros::E_MOTOR_BRAKE_HOLD);
	angler.set_brake_mode						(pros::E_MOTOR_BRAKE_HOLD);
	intakeLeft.set_brake_mode				(pros::E_MOTOR_BRAKE_HOLD);
	intakeRight.set_brake_mode			(pros::E_MOTOR_BRAKE_HOLD);

	while(true)
	{
		driveControl();

		intakeControl();

		anglerControl();

		lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	 if (btnUp.changedToPressed()) {
			 liftControl->setTarget(1800);
			 pros::delay(150);
			 setIntake(-127);
			 pros::delay(200);
		 }
		  else if (btnDown.changedToPressed() ){
			 ml_down_position();

		 }

		pros::lcd::print(0, "Angler val: %f", anglerPosition());
		pros::lcd::print(1, "Lift val: %f", liftPosition());

		pros::delay(10);
	}
}
