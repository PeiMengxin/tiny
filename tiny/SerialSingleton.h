#ifndef SerialSingleton_h__
#define SerialSingleton_h__

#include <serial/serial.h>

class SerialSingleton
{
private:
	SerialSingleton();
	static SerialSingleton *m_pInstance;
	class CGarbo   //它的唯一工作就是在析构函数中删除CSingleton的实例
	{
	public:
		~CGarbo();
	};
	static CGarbo Garbo;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数

public:
	static SerialSingleton * GetInstance();

	serial::Serial serial_port;
};


#endif // SerialSingleton_h__
