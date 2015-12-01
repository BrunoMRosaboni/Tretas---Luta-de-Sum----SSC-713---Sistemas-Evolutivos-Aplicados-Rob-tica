#include "Populacao.h"


Populacao::Populacao(){
	
}

Populacao::Populacao(short int vId,int clientId) {
	this->id = vId;
	this->pop.resize(POP_SIZE, new Individuo());

	//Inicializar indivíduos com parâmetros aleatórios
	for (int i = 0; i < POP_SIZE; i++) {
		pop[i]->init(id, randomFloat(0, 1),randomFloat(1,30), randomFloat(1, 30), randomFloat(1, 5), randomFloat(1, 5), randomFloat(1, 30), randomFloat(5, 90),-1);
		pop[i]->setClientId(clientId);
	}

	bestInd = new Individuo();
}

Populacao::~Populacao() {
	pop.clear();
}

void Populacao::prepareForBattle(int idx) {
	pop[idx]->loadModel();
	pop[idx]->initStreamingSensors();
	pop[idx]->initRobotVRep();
}

bool Populacao::compareFitness(Individuo *ind1, Individuo *ind2) {
	return (ind1->getFitness() > ind2->getFitness());
}

void Populacao::sortPop() {
	std::sort(pop.begin(), pop.end(), compareFitness);
}


void Populacao::selectParents(int &idx1, int &idx2) {

	do {
		idx1 = tournament2(pop);
		idx2 = tournament2(pop);
	} while (idx1 == idx2);
}

void Populacao::printBest() {
	bestInd->print();
}

void Populacao::resetFitness() {
	for (int i = 0; i < pop.size(); i++) {
		pop[i]->resetFitness();
	}
}

void Populacao::copyBest(Individuo *ind) {
	bestInd->setFitness(ind->getFitness());
	bestInd->setProbAtk(ind->getProbAtk());
	bestInd->setVelAtk(ind->getVelAtk());
	bestInd->setVelDef(ind->getVelDef());
	bestInd->setTAtk(ind->getTAtk());
	bestInd->setTDef(ind->getTDef());
	bestInd->setTorque(ind->getTorque());
	bestInd->setWeight(ind->getWeight());
}

void Populacao::insertChildren(vector<Individuo*> children) {
	//Inserir filhos na população
	pop.insert(pop.begin(), children.begin(), children.end());
}

void Populacao::updatePop() {
	
	//Ordenar indivíduos pelo fitness
	sortPop();

	//Liberar memória dos indivíduos a serem descartados
	for (int i = POP_SIZE; i < pop.size(); i++) {
		delete(pop[i]);
	}

	//Eliminar ponteiros nulos da população
	vector<Individuo *>::iterator it = pop.begin() + POP_SIZE;

	pop.erase(it, pop.end());

	//cout << "POP_SIZE: " << pop.size() << endl;

}