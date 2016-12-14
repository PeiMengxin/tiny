#ifndef _PARAM_H__
#define _PARAM_H__

#include <stdint.h>
#include <iostream>
#include <vector>

class PID
{
public:
	PID();
	~PID();

	uint16_t p;
	uint16_t i;
	uint16_t d;
	uint16_t n;

private:

};

class Sensor
{
public:
	Sensor();
	~Sensor();

	short VAL_ACC_X;
	short VAL_ACC_Y;
	short VAL_ACC_Z;

	short VAL_GYR_X;
	short VAL_GYR_Y;
	short VAL_GYR_Z;
	
	short VAL_HM_X;
	short VAL_HM_Y;
	short VAL_HM_Z;

private:

};

class GPS
{
public:
	GPS();
	~GPS();

	double longitude;
	double latitude;
	double elevation;

private:

};

class Param
{
public:
	Param();
	~Param();

	float avoid_scope;
	float excepted_height;
	float sensitivity;

	uint8_t enable_height;
	uint8_t enable_avoidObj;

	PID pid_custom;
	PID pid_outerlayer;
	PID pid_innerlayer;
	PID pid_height;
	PID pid_position;

	uint16_t rocker_mid[4];

private:

};

class DataShow
{
public:
	DataShow();
	~DataShow();

	uint16_t pwm[5];
	int control[4];
	uint8_t state;
	float fusion_data;
	float height;

	GPS gps;
	Sensor sensor;

private:

};

class ChartCtrlData
{
public:
	ChartCtrlData();
	~ChartCtrlData();

	std::vector<double> x;
	std::vector<double> y;

private:

};


#endif //_PARAM_H__



