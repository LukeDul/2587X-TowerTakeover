#include "main.h"

#ifndef GLOBALS_H
#define GLOBALS_H
//****************************|Ports|****************************
extern int frontLeft;
extern int backLeft;
extern int frontRight;
extern int backRight;

extern int liftPort;
extern int intakeLeftPort;
extern int intakeRightPort;

//****************************|Motors|****************************
extern pros::Motor lift;
extern pros::Motor intakeLeft;
extern pros::Motor intakeRight;
extern pros::Motor angler;
extern pros::Motor driveLeftBack;
extern pros::Motor driveLeftFront;
extern pros::Motor driveRightBack;
extern pros::Motor driveRightFront;
extern MotorGroup intake;

//Drivetrain motors
extern Motor frontLeftMotor;
extern Motor backLeftMotor;
extern Motor frontRightMotor;
extern Motor backRightMotor;

//Drive motor groups
extern MotorGroup driveL;
extern MotorGroup driveR;

extern ChassisScales scales;

extern Motor intakeRightMotor;
extern Motor intakeLeftMotor;

 //Angler
extern Motor anglerMotor;
extern Motor liftMotor;

//Intake
extern MotorGroup intake;

//****************************|Sensors|****************************
extern pros::ADIGyro gyro;
extern pros::ADIPotentiometer anglerPot;

//****************************|Controller|**************************
extern pros::Controller controller;

#endif
