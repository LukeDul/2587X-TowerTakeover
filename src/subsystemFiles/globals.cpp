 #include "main.h"

 int frontLeft = 9;
 int backLeft = 6;
 int frontRight = 10;
 int backRight = 7;

 int intakeLeftPort = 2;
 int intakeRightPort = 4;
 int liftPort = 3;
 int anglerPort = 8;

//****************************|Motors|****************************
pros::Motor intakeLeft        (intakeLeftPort, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intakeRight       (intakeRightPort, pros::E_MOTOR_GEARSET_18, true,  pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor lift              (liftPort, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor angler            (anglerPort, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightBack    (backRight,pros::E_MOTOR_GEARSET_18, true,  pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftBack     (backLeft,pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftFront    (frontLeft,pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightFront   (frontRight,pros::E_MOTOR_GEARSET_18, true,  pros::E_MOTOR_ENCODER_COUNTS);

//****************************|Sensors|*******************************
pros::ADIGyro gyro               ('g');
pros::ADIPotentiometer anglerPot ('h');

//****************************|Controllers|****************************
pros::Controller controller(pros::E_CONTROLLER_MASTER);

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
