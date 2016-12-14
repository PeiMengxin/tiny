#include "stdafx.h"
#include "datatransform.h"

short BytetoUint(unsigned char* databuf, int cnt)
{
	short r = 0;
	r <<= 8;
	r |= (databuf[cnt] & 0x00ff);
	r <<= 8;
	r |= (databuf[cnt + 1] & 0x00ff);
	return r;
}

int BytetoUint3(unsigned char* databuf, int cnt)
{
	int r = 0;
	r <<= 8;
	r |= (databuf[cnt] & 0x00ff);
	r <<= 8;
	r |= (databuf[cnt + 1] & 0x00ff);
	r <<= 16;
	r |= (databuf[cnt + 2] & 0x00ff);
	return r;
}

long Bytetoint(unsigned char* databuf, int cnt)
{
	long r = 0;
	//r=(((char)RX_Data[cnt]<<24)|((char)RX_Data[cnt+1]<<16)|((char)RX_Data[cnt+2]<<8)|(char)RX_Data[cnt+3]);
	r <<= 8;
	r |= (databuf[cnt] & 0x00ff);
	r <<= 8;
	r |= (databuf[cnt + 1] & 0x00ff);
	r <<= 8;
	r |= (databuf[cnt + 2] & 0x00ff);
	r <<= 8;
	r |= (databuf[cnt + 3] & 0x00ff);
	return r;
}