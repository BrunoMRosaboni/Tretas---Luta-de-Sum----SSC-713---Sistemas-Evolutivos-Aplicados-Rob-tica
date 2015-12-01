#ifndef POPULACAO_H
#define POPULACAO_H

#include<vector>
#include<algorithm>
#include <iostream>

#include "Individuo.h"
#include "Utils.h"
#include "Defines.h"
#include "Selection.h"

using namespace std;

class Populacao {

public:

	Populacao();
	Populacao(short int vId,int clientId);
	~Populacao();

	//Ordenar popula��o em ordem decrescente de fitness
	void sortPop();

	//Realizar corte da popula��o para a pr�xima gera��o
	void updatePop();

	void insertChildren(vector<Individuo *> children);

	//Funa��o de compara��o de fitness para ordena��o
	static bool compareFitness(Individuo *ind1, Individuo *ind2);
	
	//Preparar indiv�duo para batalha
	void prepareForBattle(int idx);

	//Fazer c�pia do melhor indiv�duo
	void copyBest(Individuo *); 

	//Apresentar melhor indiv�duo
	void printBest();

	//Sele��o de pais para crossover
	void selectParents(int &idx1,int &idx2);

	//Zerar fitness de toda popula��o
	void resetFitness();

	//Popula��o
	vector<Individuo*> pop;


private:

	//Melhor indiv�duo
	Individuo *bestInd;

	//ID do robo - robot_1 ou robot_2
	short int id;
};

#endif