#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>

// Print integer type Binaries (type_Size parameter should be in "byte" size)
void binaryPrint(long long value, int type_Size){
    for (int i = (type_Size * 8) - 1; i >= 0; i--)
    	putchar((value & (1 << i)) ? '1' : '0');
}

unsigned int peasantMultiply_32(unsigned int a, unsigned int b) {
	unsigned int valid_number[32];
	int n = 0; 

	while(a) {
		if (a & 1) valid_number[n++] = b;
		a = a >> 1;
		b = b << 1;
	}
	while(n--) a += valid_number[n];
	
	return a;
}

unsigned int small_PeasantMultiply_32(unsigned int a, unsigned int b) {
	unsigned int sum = 0;
	while(a) {
		if (a & 1) sum += b;
		a = a >> 1;
		b = b << 1;
	}
	return sum;
}

#endif