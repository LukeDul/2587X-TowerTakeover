 #include "main.h"

//****************************|Motors|****************************
pros::Motor intakeLeft        (5, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intakeRight       (4, pros::E_MOTOR_GEARSET_18, true,  pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor lift              (3, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor angler            (8, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightBack    (7,pros::E_MOTOR_GEARSET_18, true,  pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftBack     (6,pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftFront    (9,pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightFront   (10,pros::E_MOTOR_GEARSET_18, true,  pros::E_MOTOR_ENCODER_COUNTS);

//****************************|Sensors|*******************************
pros::ADIGyro gyro               ('g');
pros::ADIPotentiometer anglerPot ('h');

//****************************|Controllers|****************************
pros::Controller controller(pros::E_CONTROLLER_MASTER);
