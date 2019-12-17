 #include "main.h"

//****************************|Motors|****************************
pros::Motor intakeLeft        (5, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intakeRight       (2, pros::E_MOTOR_GEARSET_18, true,  pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor lift              (3, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor angler            (4, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightBack    (17,pros::E_MOTOR_GEARSET_18, true,  pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftBack     (18,pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftFront    (19,pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightFront   (20,pros::E_MOTOR_GEARSET_18, true,  pros::E_MOTOR_ENCODER_COUNTS);

//****************************|Sensors|*******************************
pros::ADIGyro gyro               ('g');
pros::ADIPotentiometer anglerPot ('h');

//****************************|Controllers|****************************
pros::Controller controller(pros::E_CONTROLLER_MASTER);
