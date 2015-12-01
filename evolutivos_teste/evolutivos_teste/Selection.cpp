#include "Selection.h"


 int tournament2(vector<Individuo *> & pop) {
	int i1, i2;

	//Escolher pai 1
	i1 = rand()%pop.size();
	do {
		i2 = rand()%pop.size();
	} while (i2 == i1);

	return (pop[i1]->getFitness() > pop[i2]->getFitness()) ? i1 : i2;

}