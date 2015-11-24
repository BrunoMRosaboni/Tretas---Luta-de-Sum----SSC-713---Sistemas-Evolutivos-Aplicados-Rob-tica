#ifndef FUNCAO_H_
#define FUNCAO_H_

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

void mutacao(Individuo*);
double CalculaValores(float , float , unsigned long int*);
void GeraSemente(unsigned long int*);

#endif