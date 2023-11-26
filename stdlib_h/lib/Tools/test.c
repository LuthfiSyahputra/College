#include <stdio.h>


int peasantMultiply_32(int a, int b) {
	int valid_number[32];
	int n = 0; 

	while(a) {
		if (a & 1) valid_number[n++] = b;
		a = a >> 1;
		b = b << 1;
	}
	for (int i = 0; i < n; i++) a += valid_number[i];
	
	return a;
}

int main() {
	int a, b;
	a = 239;
	b = 183;
	printf("a: %d  b: %d\npeasant_multiply: %d\nbuiltin_multiplier: %d\n", a, b, peasantMultiply_32(a, b), a*b);

}