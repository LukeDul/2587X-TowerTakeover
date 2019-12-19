#include "main.h"

#ifndef DRIVE_H
#define DRIVE_H

//****************************|Helper Functions|********************************
void setDrive(int left, int right);

void resetDriveEncoders();

double avgDriveEncoderValue();

double avgRightDrive();

double avgLeftDrive();

double currDriveValue();

//****************************|Autonomous Functions|****************************
void translate(int units, int voltage);

void rotate(int degrees, int voltage);

void drive_pid(double set_point);

void right_translate( int units, int voltage);

void left_translate(int units, int voltage);

//****************************|Driver Control Function|*************************
void driveControl();

#endif
