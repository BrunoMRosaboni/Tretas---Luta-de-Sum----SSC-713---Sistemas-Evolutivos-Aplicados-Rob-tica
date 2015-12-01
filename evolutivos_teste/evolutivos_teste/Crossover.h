#ifndef CROSSOVER_H
#define CROSSOVER_H

#include "Individuo.h"

Individuo* crossover(Individuo *individuo1, Individuo *individuo2);

void calcularParametrosIndividuo(Individuo* individuo_target, Individuo *individuo1, Individuo *individuo2);

bool compararParametros(float param1, float param2);

float recalcularParametro(float param1, float param2);

#endif