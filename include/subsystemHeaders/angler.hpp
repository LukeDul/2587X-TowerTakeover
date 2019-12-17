#include "main.h"

#ifndef ANGLER_H
#define ANGLER_H
//****************************|Helper Functions|****************************
void set_angler(int power);
void stop_angler();
double anglerPosition();
void angler_down();

//****************************|Custom Movement Functions|*******************
void move_angler_up(int target_position);
void move_angler_down(int target_position);
void move_angler(int target_position, int voltage);

//****************************|Macro Functions|******************************
void stack_macro();
void release_macro();

//****************************|Angler Operation Control|**********************
void anglerControl();

#endif
