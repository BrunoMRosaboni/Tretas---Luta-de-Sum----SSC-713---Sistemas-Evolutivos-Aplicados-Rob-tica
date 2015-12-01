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

	//Ordenar população em ordem decrescente de fitness
	void sortPop();

	//Realizar corte da população para a próxima geração
	void updatePop();

	void insertChildren(vector<Individuo *> children);

	//Funação de comparação de fitness para ordenação
	static bool compareFitness(Individuo *ind1, Individuo *ind2);
	
	//Preparar indivíduo para batalha
	void prepareForBattle(int idx);

	//Fazer cópia do melhor indivíduo
	void copyBest(Individuo *); 

	//Apresentar melhor indivíduo
	void printBest();

	//Seleção de pais para crossover
	void selectParents(int &idx1,int &idx2);

	//Zerar fitness de toda população
	void resetFitness();

	//População
	vector<Individuo*> pop;


private:

	//Melhor indivíduo
	Individuo *bestInd;

	//ID do robo - robot_1 ou robot_2
	short int id;
};

#endif