#include "main.h"

void on_left_button() {
  static bool pressed = false;
  pressed = !pressed;
  if (pressed) {
		runBlueSmallZone = false;
		runOnePointAuton = false;
		runRedSmallZone = true;
    pros::lcd::set_text(2, "Run Red Small Zone");

  } else {
    pros::lcd::clear_line(2);
  }
}

void on_center_button() {
  static bool pressed = false;
  pressed = !pressed;
  if (pressed) {
    pros::lcd::set_text(2, "Run 1 Point Auton");
		runOnePointAuton = true;
		runBlueSmallZone = false;
		runRedSmallZone = false;
  } else {
    pros::lcd::clear_line(2);
  }
}

void on_right_button() {
  static bool pressed = false;
  pressed = !pressed;
  if (pressed) {
    pros::lcd::set_text(2, "Run Blue Small Zone ");
		runBlueSmallZone = true;
		runRedSmallZone = false;
		runOnePointAuton = false;
  } else {
    pros::lcd::clear_line(2);
  }
}

void LCD_init(){

  bool runRedSmallZone = false;
  bool runBlueSmallZone = false;
  bool runOnePointAuton = false;

  pros::lcd::initialize();

  pros::lcd::register_btn0_cb(on_left_button);
  pros::lcd::register_btn2_cb(on_right_button);
  pros::lcd::register_btn1_cb(on_center_button);
}

void LCD_op(){
  if(runRedSmallZone == true){
  //	red_small_zone();
  }else if (runBlueSmallZone == true){
  //	blue_small_zone();
  }else if(runOnePointAuton == true){
  //	one_point();
  }
}
