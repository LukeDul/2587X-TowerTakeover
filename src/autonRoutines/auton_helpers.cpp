#include "main.h"

void outtake_nine_stack()
{
	intake_left.moveRelative(-700, 50);
	intake_right.moveRelative(-700, 50);
}

//deploys intake and tray
void tray_intake_deploy()//preload cannot be in front of robot
{//delays could be less
	setIntake(-12000);

	pros::delay(2000);

	setIntake(0);

	pros::delay(1000);
}

//deploys anti-tips
void antitip_deploy()//will not work if against wall
{//delays could be less
	move_angler_up(500);

	move_angler_down(0);
}

//****************************|Auton Functions|****************************

//scores one cube in any zone


void outtake_stack()
{
	intake_left.moveRelative(-620, 200);
	intake_right.moveRelative(-620, 200);
}
