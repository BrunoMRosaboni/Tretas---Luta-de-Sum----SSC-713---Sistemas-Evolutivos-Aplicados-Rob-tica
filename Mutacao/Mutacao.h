#ifndef MUTACAO_H_
#define MUTACAO_H_

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

void mutacao(Individuo*);
//double CalculaValores(float , float , unsigned long int*);
void GeraSemente(double*);
double DistribuicaoUniforme(double, double, double);

#endif