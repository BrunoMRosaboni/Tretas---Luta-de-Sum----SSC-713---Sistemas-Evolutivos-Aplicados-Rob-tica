#include "Mutacao.h"

void mutacao(Individuo* ind){

	float mutVal;
	
	//Probabilidade de ataque
	if (randomFloat(0,1) < MUT_RATE){
		mutVal = randomFloat(-DELTA_PROB, DELTA_PROB);
		ind->setProbAtk(ind->getProbAtk() + mutVal);
	}

	//Velocidade de ataque
	if (randomFloat(0, 1) < MUT_RATE) {
		mutVal = randomFloat(-DELTA_VEL_ATK, DELTA_VEL_ATK);
		ind->setVelAtk(ind->getVelAtk() + mutVal);
	}

	//Velocidade de esquiva
	if (randomFloat(0, 1) < MUT_RATE) {
		mutVal = randomFloat(-DELTA_VEL_DEF, DELTA_VEL_DEF);
		ind->setVelDef(ind->getVelDef() + mutVal);
	}

	//Tempo de ataque
	if (randomFloat(0, 1) < MUT_RATE) {
		mutVal = randomFloat(-DELTA_T_ATK, DELTA_T_ATK);
		ind->setTAtk(ind->getTAtk() + mutVal);
	}

	//Tempo de defesa
	if (randomFloat(0, 1) < MUT_RATE) {
		mutVal = randomFloat(-DELTA_T_DEF, DELTA_T_DEF);
		ind->setTDef(ind->getTDef() + mutVal);
	}

	//Torque
	if (randomFloat(0, 1) < MUT_RATE) {
		mutVal = randomFloat(-DELTA_TORQUE, DELTA_TORQUE);
		ind->setTorque(ind->getTorque() + mutVal);
	}

	//Peso
	if (randomFloat(0, 1) < MUT_RATE) {
		mutVal = randomFloat(-DELTA_WEIGHT, DELTA_WEIGHT);
		ind->setWeight(ind->getWeight() + mutVal);
	}

	
}