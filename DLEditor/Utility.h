#ifndef UTILITY_H_
#define UTILITY_H_

#include <stdlib.h>
#include <time.h>
#include <math.h> 

int Dice(int n) {
	//returns 1dn
	if (n <= 0)	return 255;
	if (n == 1) return 1;
	srand((unsigned)time(NULL));
	return (rand() % (n - 1)) + 1;
}

int Bonus(int attribute) {
	float f = (attribute - 10) / 2;
	return (int)f;
}
#endif
