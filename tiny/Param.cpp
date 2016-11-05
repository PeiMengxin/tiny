#include "stdafx.h"
#include "Param.h"


Param::Param()
{
	avoid_scope = 0;
	excepted_height = 1000;
	sensitivity = 1500;

	pid_p = 0;
	pid_i = 0;
	pid_d = 0;

	rocker_mid[0] = 1500;
	rocker_mid[1] = 1500;
	rocker_mid[2] = 1500;
	rocker_mid[3] = 1500;

	enable_avoidObj = 0;
	enable_height = 0;
}


Param::~Param()
{
}





DataShow::DataShow()
{
	for (size_t i = 0; i < 4; i++)
	{
		pwm[i] = 0;
		control[i] = 0;
	}
	pwm[4] = 0;

	state = 0;
	radar_fusion = 0;
	excepted_height = 0;
}

DataShow::~DataShow()
{
}