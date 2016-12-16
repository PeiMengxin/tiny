#include "stdafx.h"
#include "SerialSingleton.h"

SerialSingleton *SerialSingleton::m_pInstance = nullptr;

SerialSingleton::SerialSingleton()
{

}

SerialSingleton * SerialSingleton::GetInstance()
{
	if (m_pInstance == NULL)  //判断是否第一次调用
		m_pInstance = new SerialSingleton();
	return m_pInstance;
}

SerialSingleton::CGarbo::~CGarbo()
{
	if (SerialSingleton::m_pInstance)
		delete SerialSingleton::m_pInstance;
}
