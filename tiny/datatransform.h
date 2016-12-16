#ifndef __DATATRANSFORM_H__
#define __DATATRANSFORM_H__

#include <iostream>
#include <vector>

#define COM_DATA_SIZE_MAX 128

short BytetoUint(unsigned char* databuf, int cnt);
int BytetoUint3(unsigned char* databuf, int cnt);
long Bytetoint(unsigned char* databuf, int cnt);


bool initColorTable(std::vector < COLORREF >& ColorTable);

#endif // __DATATRANSFORM_H__
