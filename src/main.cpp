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

void outtake_nine_stack()
{
	intake_left.moveRelative(-600, 200);
	intake_right.moveRelative(-600, 200);
  pros::delay(700);
  intake_left.moveRelative(300, 200);
  intake_right.moveRelative(300, 200);


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

    auto towerturns = okapi::ChassisControllerBuilder()
    		.withMotors({frontLeft, backLeft}, {frontRight, backRight})
    		.withGains(
    			 {0.001, 0.001, 0.00009}, // Distance controller gains 0.005, 0, 0.001
    			 {0.0026, 0.0007, 0.0001}, // Turn controller gains .00075	 {0.00075, 0.0007, 0.00009}
    			 {0.001, 0.001, 0.0001}  // Angle controller gains (helps drive straight)
    		 )
    		.withDimensions(AbstractMotor::gearset::green, {{4.125_in, 8.875_in}, okapi::imev5GreenTPR})//9.1
    		.withOdometry() // use the same scales as the chassis (above)
    		.withMaxVelocity(50)
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
        auto tenstack =
    		  AsyncMotionProfileControllerBuilder()
    		    .withLimits({
    		      0.35,  //max velocity
    		      2.0,  //max acceleration
    		      10.0  //max jerk
    		    })
    		    .withOutput(myChassis)
    		    .buildMotionProfileController();

  void lift_low(){
    liftControl->setTarget(1800);
    pros::delay(100);
    setIntake(-127);
    pros::delay(150);
    setIntake(0);
  }
void lift_down(){
  liftControl->setTarget(0);
}

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

void tower(){
 lift_low();
 pros::delay(2000);

 intake_left.moveVoltage(-11000);
 intake_right.moveVoltage(-11000);
 pros::delay(500);
 intake_left.moveVoltage(0);
 intake_right.moveVoltage(0);
 lift_down();

}

void tower2(){
 lift_low();
 pros::delay(2000);

 tenstack->generatePath({
 		{0_ft, 0_ft, 0_deg},
 		{1_ft, 0_ft, 0_deg}},
 		"bruh"
 	);


   tenstack->setTarget("bruh");
   tenstack->waitUntilSettled();

 intake_left.moveVoltage(-5000);
 intake_right.moveVoltage(-5000);
 tenstack->setTarget("bruh",1);
 tenstack->waitUntilSettled();
 intake_left.moveVoltage(0);
 intake_right.moveVoltage(0);


}





//***************************************************************************************************
void programmingSkillz()
{


  intakeLeft.set_brake_mode				(pros::E_MOTOR_BRAKE_HOLD);
  intakeRight.set_brake_mode			(pros::E_MOTOR_BRAKE_HOLD);
  angler.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);


  lift = -4;

  slow->generatePath({
    {0_ft, 0_ft, 0_deg},
    {1_ft, 0_ft, 0_deg}},
    "Push Cube"
  );

  slow->setTarget("Push Cube");
  slow->waitUntilSettled();
  antitip_deploy();

  slow->generatePath({
    {0_ft, 0_ft, 0_deg},
    {0.75_ft, 0_ft, 0_deg}},
    "align on wall"
  );

  slow->setTarget("align on wall",1);
  slow->waitUntilSettled();

  intake_left.moveVoltage(-12000);
  intake_right.moveVoltage(-12000);
  pros::delay(300);
  intake_left.moveVoltage(0);
  intake_right.moveVoltage(0);
  pros::delay(400);


  intake_left.moveVoltage(12000);
  intake_right.moveVoltage(12000);

  tenstack->generatePath({
  		{0_ft, 0_ft, 0_deg},
  		{4.5_ft, 0_ft, 0_deg}},
  		"4 cube"
  	);


    tenstack->setTarget("4 cube");
    tenstack->waitUntilSettled();

    pros::delay(1000);

    intake_left.moveVoltage(0);
    intake_right.moveVoltage(0);

    fast->generatePath({
          {0_ft, 0_ft, 0_deg},
          {0.5_ft, 0_ft, 0_deg}},
          "tonext"
        );

      fast->setTarget("tonext");
      fast->waitUntilSettled();

      intake_left.moveVoltage(12000);
      intake_right.moveVoltage(12000);

  slow->generatePath({
        {0_ft, 0_ft, 0_deg},
        {3_ft, 0_ft, 0_deg}},
        "middle"
      );


    slow->setTarget("middle");
    slow->waitUntilSettled();



    intakeLeft.set_brake_mode				(pros::E_MOTOR_BRAKE_HOLD);
    intakeRight.set_brake_mode			(pros::E_MOTOR_BRAKE_HOLD);

  pros::delay(1000);

      tenstack->generatePath({
  		{0_ft, 0_ft, 0_deg},
  		{1.25_ft, 0_ft, 0_deg}},
  		"after"
  	);
    tenstack->setTarget("after");
    tenstack->waitUntilSettled();

    intake_left.moveVoltage(0);
    intake_right.moveVoltage(0);


  intakeLeft.set_brake_mode				(pros::E_MOTOR_BRAKE_HOLD);
  intakeRight.set_brake_mode			(pros::E_MOTOR_BRAKE_HOLD);

  lift = 0;



  chassisauto->turnAngle(40_deg);
  chassisauto->waitUntilSettled();



  tenstack->generatePath({
  	{0_ft, 0_ft, 0_deg},
  	{1.7_ft, 0_ft, 0_deg}},
		"Drive to Blue"
  );

  tenstack->setTarget("Drive to Blue");
  tenstack->waitUntilSettled();

  outtake_nine_stack();

  intakeLeft.set_brake_mode				(pros::E_MOTOR_BRAKE_COAST);
  intakeRight.set_brake_mode			(pros::E_MOTOR_BRAKE_COAST);

  angler.set_brake_mode				(pros::E_MOTOR_BRAKE_BRAKE);
  pros::delay(500);
  stack_macro();
  pros::delay(1000);
  release_macro();



  towerturns->turnAngle(-153_deg);
  towerturns->waitUntilSettled();


  intake_left.moveVoltage(12000);
  intake_right.moveVoltage(12000);

slow->generatePath({
  	{0_ft, 0_ft, 0_deg},
  	{2.5_ft, 0_ft, 0_deg}},
		"1st"
  );

  slow->setTarget("1st");
  slow->waitUntilSettled();

  fast->generatePath({
  	{0_ft, 0_ft, 0_deg},
  	{2.5_ft, 0_ft, 0_deg}},
		"2nd"
  );

  fast->setTarget("2nd",1);
  fast->waitUntilSettled();

  intake_left.moveVoltage(0);
  intake_right.moveVoltage(0);

  towerturns->turnAngle(232_deg);
  towerturns->waitUntilSettled();

  fast->generatePath({
    {0_ft, 0_ft, 0_deg},
    {2_in, 0_ft, 0_deg}},
    "idk"
  );

  fast->setTarget("idk");
  fast->waitUntilSettled();

pros::delay(500);

  tower2();

  lift_down();

  fast->generatePath({
    {0_ft, 0_ft, 0_deg},
    {1.1_ft, 0_ft, 0_deg}},
    "hmm"
  );

  fast->setTarget("hmm",1);
  fast->waitUntilSettled();

  towerturns->turnAngle(75_deg);
  towerturns->waitUntilSettled();

  intake_left.moveVoltage(12000);
  intake_right.moveVoltage(12000);

  tenstack->generatePath({
    {0_ft, 0_ft, 0_deg},
    {2.7_ft, 0_ft, 0_deg}},
    "bro"
  );

  tenstack->setTarget("bro");
  tenstack->waitUntilSettled();

  tenstack->generatePath({
    {0_ft, 0_ft, 0_deg},
    {0.2_ft, 0_ft, 0_deg}},
    "hmhmmhm"
  );

  tenstack->setTarget("hmhmmhm",1);
  tenstack->waitUntilSettled();

  intake_left.moveVoltage(0);
  intake_right.moveVoltage(0);


  tower2();

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
//	red_small_zone();
//	one_point();


programmingSkillz();
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
