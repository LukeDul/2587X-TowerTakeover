#include "main.h"

#ifndef GLOBALS_H
#define GLOBALS_H

//****************************|Motors|****************************
extern pros::Motor lift;
extern pros::Motor intakeLeft;
extern pros::Motor intakeRight;
extern pros::Motor angler;
extern pros::Motor driveLeftBack;
extern pros::Motor driveLeftFront;
extern pros::Motor driveRightBack;
extern pros::Motor driveRightFront;

//****************************|Sensors|****************************
extern pros::ADIGyro gyro;
extern pros::ADIPotentiometer anglerPot;

//****************************|Controller|**************************
extern pros::Controller controller;

#endif
