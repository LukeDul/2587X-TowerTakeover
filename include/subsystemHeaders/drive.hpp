#include "main.h"

#ifndef DRIVE_H 
#define DRIVE_H
//helper
void setDrive(int left, int right);

void resetDriveEncoders();
double avgDriveEncoderValue();
double avgRightDrive();
double avgLeftDrive();
void right_translate( int units, int voltage);
void left_translate(int units, int voltage);

//DRIVER CONTROLER FUNCTIONS
void setDriveMotors();

//auton FUNCTIONS
void translate(int units, int voltage);

void rotate(int degrees, int voltage);

void drive_pid(double set_point);

#endif
