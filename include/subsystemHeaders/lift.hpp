#include "main.h"

#ifndef LIFT_H
#define LIFT_H
//****************************|Helper Functions|****************************
void set_lift(int power);
void stop_lift();
double liftPosition();

//****************************|Position Functions|***************************
void ml_down_position();
void ml_low_score_position();
void ml_low_descore_position();
void ml_medium_score_position();
void ml_medium_descore_position();

//****************************|Lift Macros|**********************************

void lm_score_low_position();

//****************************|Lift Operation Control|***********************

void lift_macros_fn(void* param);
void lift_pos(void*param);
#endif
