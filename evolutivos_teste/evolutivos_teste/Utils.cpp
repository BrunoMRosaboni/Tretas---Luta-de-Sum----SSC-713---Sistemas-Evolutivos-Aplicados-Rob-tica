#include "Utils.h"

float randomFloat(float min, float max) {
	return (((float)rand()/(float)RAND_MAX)*(max - min) + min);
}

void initSeed() {
	srand(time(NULL));
}