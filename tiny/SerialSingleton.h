#ifndef SerialSingleton_h__
#define SerialSingleton_h__

#include <serial/serial.h>

class SerialSingleton
{
private:
	SerialSingleton();
	static SerialSingleton *m_pInstance;
	class CGarbo   //����Ψһ��������������������ɾ��CSingleton��ʵ��
	{
	public:
		~CGarbo();
	};
	static CGarbo Garbo;  //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������

public:
	static SerialSingleton * GetInstance();

	serial::Serial serial_port;
};


#endif // SerialSingleton_h__
