#include "stdafx.h"
#include "Param.h"


Param::Param()
{
	avoid_scope = 0;
	excepted_height = 1000;
	sensitivity = 1500;

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


ChartCtrlData::ChartCtrlData()
{
}

ChartCtrlData::~ChartCtrlData()
{
}

PID::~PID()
{

}

PID::PID()
{
	p = 0;
	i = 0;
	d = 0;
	n = 0;
}

Sensor::~Sensor()
{

}

Sensor::Sensor()
{
	VAL_ACC_X = 0;
	VAL_ACC_Y = 0;
	VAL_ACC_Z = 0;
	VAL_GYR_X = 0;
	VAL_GYR_Y = 0;
	VAL_GYR_Z = 0;
	VAL_HM_X = 0;
	VAL_HM_Y = 0;
	VAL_HM_Z = 0;
}

GPS::~GPS()
{

}

GPS::GPS()
{
	latitude = 0.0;
	longitude = 0.0;
	elevation = 0.0;
}

Angle::~Angle()
{

}

Angle::Angle()
{
	Pitch = 0;
	Roll = 0;
	Yaw = 0;
}

DataShow *DataShow::m_pInstance = nullptr;

DataShow::DataShow()
{
	for (size_t i = 0; i < 4; i++)
	{
		pwm[i] = 0;
		control[i] = 0;
	}
	pwm[4] = 0;

	state = 0;
	fusion_data = 0;
	height = 0;
}

DataShow * DataShow::GetInstance()
{
	if (m_pInstance == NULL)  //判断是否第一次调用
		m_pInstance = new DataShow();
	return m_pInstance;
}

DataShow::CGarbo::~CGarbo()
{
	if (DataShow::m_pInstance)
		delete DataShow::m_pInstance;
}

Coordinate::~Coordinate()
{

}

Coordinate::Coordinate()
{
	x = 0;
	y = 0;
	z = 0;
	id = 0;
}
