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

bool initColorTable(std::vector < COLORREF >& ColorTable)
{
	ColorTable.push_back(RGB(255, 0, 0));
	ColorTable.push_back(RGB(0, 255, 0));
	ColorTable.push_back(RGB(0, 0, 255));
	ColorTable.push_back(RGB(255, 255, 0));
	ColorTable.push_back(RGB(255, 0, 255));
	ColorTable.push_back(RGB(0, 255, 255));
	ColorTable.push_back(RGB(65, 100, 225));
	ColorTable.push_back(RGB(119, 136, 153));
	ColorTable.push_back(RGB(50, 205, 50));
	ColorTable.push_back(RGB(255, 140, 0));
	ColorTable.push_back(RGB(139, 236, 19));
	ColorTable.push_back(RGB(0, 127, 240));
	ColorTable.push_back(RGB(178, 34, 34));
	ColorTable.push_back(RGB(128, 0, 0));
	ColorTable.push_back(RGB(189, 183, 107));
	ColorTable.push_back(RGB(218, 165, 32));

	return true;
}
