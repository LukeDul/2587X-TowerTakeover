#include "main.h"

void one_point()
{
	tray_intake_deploy();

	translate(300, -127);

	pros::delay(500);

	translate(1000, 127);

	pros::delay(1000);

	antitip_deploy();
}
