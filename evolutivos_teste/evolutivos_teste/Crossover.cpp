#include "Crossover.h"


Individuo* crossover(Individuo *individuo1, Individuo *individuo2) {
	// Filho a ser gerado
	Individuo* novoIndividuo = new Individuo();

	// Verificar qual individuo possui melhor fitness. O individuo escolhido
	// terá maior influência sobre o crossover
	if (compararParametros(individuo1->getFitness(), individuo2->getFitness()))
		calcularParametrosIndividuo(novoIndividuo, individuo1, individuo2);
	else calcularParametrosIndividuo(novoIndividuo, individuo2, individuo1);

	return novoIndividuo;
}


void calcularParametrosIndividuo(Individuo* individuo_target, Individuo *individuo1, Individuo *individuo2) {
	individuo_target->setProbAtk(recalcularParametro(individuo1->getProbAtk(), individuo2->getProbAtk()));
	individuo_target->setVelAtk(recalcularParametro(individuo1->getVelAtk(), individuo2->getVelAtk()));
	individuo_target->setVelDef(recalcularParametro(individuo1->getVelDef(), individuo2->getVelDef()));
	individuo_target->setTAtk(recalcularParametro(individuo1->getTAtk(), individuo2->getTAtk()));
	individuo_target->setTDef(recalcularParametro(individuo1->getTDef(), individuo2->getTDef()));
	individuo_target->setTorque(recalcularParametro(individuo1->getTorque(), individuo2->getTorque()));
	individuo_target->setWeight(recalcularParametro(individuo1->getWeight(), individuo2->getWeight()));
}

bool compararParametros(float param1, float param2) {
	if (param1 > param2)
		return true;
	else return false;
}


float recalcularParametro(float param1, float param2) {
	return ((CROSS_PERC * param1) + ((1 - CROSS_PERC) * param2));
}