 #include "main.h"

 int frontLeft = 9;
 int backLeft = 6;
 int frontRight = 10;
 int backRight = 7;

 int intakeLeftPort = 5;
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

Motor frontLeftMotor(frontLeftPort);
Motor backLeftMotor(backLeftPort);
Motor frontRightMotor(frontRightPort);
Motor backRightMotor(backRightPort);

Motor intakeRightMotor(intakeRightPort);
Motor intakeLeftMotor(intakeLeftPort);

Motor anglerMotor(anglerPort);
Motor liftMotor(liftPort);

//motor groups
MotorGroup intake({intakeRightPort, intakeLeftPort});

//****************************|Sensors|*******************************
pros::ADIGyro gyro               ('g');
pros::ADIPotentiometer anglerPot ('h');

//****************************|Controllers|****************************
pros::Controller controller(pros::E_CONTROLLER_MASTER);
