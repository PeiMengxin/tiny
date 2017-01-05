#ifndef _PARAM_H__
#define _PARAM_H__

#include <stdint.h>
#include <iostream>
#include <vector>
#include <deque>

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

class Angle
{
public:
	Angle();
	~Angle();

	short Pitch;
	short Roll;
	short Yaw;

private:

};

class Sensor
{
public:
	Sensor();
	~Sensor();

	short acc_x;
	short acc_y;
	short acc_z;

	short gry_x;
	short gry_y;
	short gry_z;
	
	short hm_x;
	short hm_y;
	short hm_z;

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

class Coordinate
{
public:
	Coordinate();
	~Coordinate();

	int x;
	int y;
	int z;
	int id;

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

class DataShow
{
private:
	DataShow();
	static DataShow *m_pInstance;
	class CGarbo   //它的唯一工作就是在析构函数中删除CSingleton的实例
	{
	public:
		~CGarbo();
	};
	static CGarbo Garbo;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数

public:
	static DataShow * GetInstance();

	uint16_t pwm[5];
	int control[4];
	uint8_t state;
	float fusion_data;
	float height;

	GPS gps;
	Sensor sensor;
	Angle angle;
	Coordinate coodinate;
	Coordinate hopecoor;
	Coordinate originalQR;

	bool obstacle;
};



#endif //_PARAM_H__



