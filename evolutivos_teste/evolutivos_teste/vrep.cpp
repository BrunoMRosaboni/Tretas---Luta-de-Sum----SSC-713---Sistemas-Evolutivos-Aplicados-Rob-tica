extern "C" {
	#include "remoteApi/extApi.h"
}
#include <stdio.h>

#include <time.h>
#include <iostream>
#include <string>
#include "Defines.h"
#include "Utils.h"
#include "Populacao.h"
#include "Individuo.h"
#include "Crossover.h"
#include "Mutacao.h"

//#include <gsl/gsl_rng.h>
//#include <gsl/gsl_sf_bessel.h>

using namespace std;

void genetico();
void x1();

int main() {
	x1();
	//genetico();

	return 0;
}

void genetico() {
	clock_t tStart;
	clock_t tEnd;

	string ip = "127.0.0.1";
	int port = 2500;
	int clientId = 1;

	//Filhos das populações
	vector<Individuo *> chdn1;
	vector<Individuo *> chdn2;

	//Índices para selecionar pais no crossover
	int idxP1, idxP2;

	//Iniciar semente para geração de números aleatórios
	initSeed();

	//Conectar com Vrep 
	cout << "Conectando..." << endl;
	clientId = simxStart(ip.c_str(), port, true, true, 3000, 5);

	if (clientId != -1) {
		cout << "Conectado!!!" << endl << endl;

		//Criar populações
		Populacao *p1 = new Populacao(1, clientId);
		Populacao *p2 = new Populacao(2, clientId);

		//Avaliação inicial
		cout << "Avaliação inicial..." << endl;
		//zerar fitness de todos os indivíduos para novas avaliações
		p1->resetFitness();
		p2->resetFitness();

		//Todos de uma população lutam contra todos da outra
		for (int i = 0; i < p1->pop.size(); i++) {
			for (int j = 0; j < p2->pop.size(); j++) {
				
				//Carregar robos na cena
				p1->prepareForBattle(i);
				p2->prepareForBattle(j);

				//iniciar luta
				simxStartSimulation(clientId, simx_opmode_oneshot);
				tStart = clock();
				do {
					p1->pop[i]->action();
					p2->pop[j]->action();

					//Analisar se algum dos  dois cairam
					if (p1->pop[i]->freeFall() || p2->pop[j]->freeFall()) {
						break;
					}

					tEnd = clock();
				} while ((tEnd - tStart) <= T_MAX);

				// Pausar luta e analisar resultado
				simxPauseSimulation(clientId, simx_opmode_oneshot);

				cout << "p1[" << i << "] vs p2[" << j << "]: ";
				//Empate
				if ((p1->pop[i]->freeFall() && p2->pop[j]->freeFall()) || (!p1->pop[i]->freeFall() && !p2->pop[j]->freeFall())) {
					p1->pop[i]->evaluate(DRAW);
					p2->pop[j]->evaluate(DRAW);
					cout << "Empate!" << endl;
				}else if (p1->pop[i]->freeFall()) {//p2 ganhou
					p1->pop[i]->evaluate(DEFEAT);
					p2->pop[j]->evaluate(VICTORY);
					cout << "p2["<<j<<"] ganhou!" << endl;
				}else if (p2->pop[j]->freeFall()) {//p1 ganhou
					p1->pop[i]->evaluate(VICTORY);
					p2->pop[j]->evaluate(DEFEAT);
					cout << "p1[" << i << "] ganhou!" << endl;
				}

				//Remover robos para a próxima batalha
				p1->pop[i]->removeModel();
				p2->pop[j]->removeModel();

				//Teste
				//p1->pop[i]->evaluate(rand()%3+1);
				//p2->pop[j]->evaluate(rand() % 3 + 1);
			}
		}

		cout << "Avaliacao inicial concluida!" << endl << endl;
		cout << "Evolucao iniciada!" << endl;

		for (int g = 0; g < MAX_GEN; g++) {
			cout << "Geracao: " << g+1 << endl;

			//Crossover e mutação - Gerar POP_SIZE/2 indivíduos
			for (int cont = 0; cont < (POP_SIZE / 2); cont++) {
				
				p1->selectParents(idxP1, idxP2);
				chdn1.push_back(crossover(p1->pop[idxP1],p1->pop[idxP2]));
				mutacao(chdn1.back());

				p2->selectParents(idxP1, idxP2);
				chdn2.push_back(crossover(p2->pop[idxP1], p2->pop[idxP2]));
				mutacao(chdn2.back());

			}
			
			//Inserir novos indivíduos na população
			p1->insertChildren(chdn1);
			p2->insertChildren(chdn2);

			//Limpar vetor de filhos
			chdn1.clear();
			chdn2.clear();

			p1->pop[0]->print();
			p1->pop[10]->print();

			//zerar fitness de todos os indivíduos para novas avaliações
			p1->resetFitness();
			p2->resetFitness();

			//Todos de uma população lutam contra todos da outra
			for (int i = 0; i < p1->pop.size(); i++) {
				for (int j = 0; j < p2->pop.size(); j++) {
				
					//Carregar robos na cena
					p1->prepareForBattle(i);
					p2->prepareForBattle(j);

					//iniciar luta
					simxStartSimulation(clientId, simx_opmode_oneshot);
					tStart = clock();
					do {
						p1->pop[i]->action();
						p2->pop[j]->action();

						//Analisar se algum dos  dois cairam
						if (p1->pop[i]->freeFall() || p2->pop[j]->freeFall()) {
							break;
						}

						tEnd = clock();
					} while ((tEnd - tStart) <= T_MAX);

					// Pausar luta e analisar resultado
					simxPauseSimulation(clientId, simx_opmode_oneshot);

					cout << "p1[" << i << "] vs p2[" << j << "]: ";
					//Empate
					if ((p1->pop[i]->freeFall() && p2->pop[j]->freeFall()) || (!p1->pop[i]->freeFall() && !p2->pop[j]->freeFall())) {
						p1->pop[i]->evaluate(DRAW);
						p2->pop[j]->evaluate(DRAW);
						cout << "Empate!" << endl;
					}
					else if (p1->pop[i]->freeFall()) {//p2 ganhou
						p1->pop[i]->evaluate(DEFEAT);
						p2->pop[j]->evaluate(VICTORY);
						cout << "p2[" << j << "] ganhou!" << endl;
					}
					else if (p2->pop[j]->freeFall()) {//p1 ganhou
						p1->pop[i]->evaluate(VICTORY);
						p2->pop[j]->evaluate(DEFEAT);
						cout << "p1[" << i << "] ganhou!" << endl;
					}

					//Remover robos para a próxima batalha
					p1->pop[i]->removeModel();
					p2->pop[j]->removeModel();

					//Teste
					//p1->pop[i]->evaluate(rand() % 3 + 1);
					//p2->pop[j]->evaluate(rand() % 3 + 1);
				}
			}
			
			//Armazenar apenas os melhores indivíduos para a próxima geração
			p1->updatePop();
			p2->updatePop();

			//Armazenar o melhor indivíduo
			p1->copyBest(p1->pop[0]);
			p2->copyBest(p2->pop[0]);
			

			p1->printBest();
			p2->printBest();
		}

		//Parar simulação
		simxStopSimulation(clientId, simx_opmode_oneshot);			
		
		//Finalizar conexão
		simxFinish(clientId);
		cout << "Conexão encerrada" << std::endl;
	}else {
		cout << "Não conectado!" << std::endl;
	}

}

void x1() {

	clock_t tStart;
	clock_t tEnd;

	string ip = "127.0.0.1";
	int port = 2500;
	int clientId;

	Individuo *ind1 = new Individuo(1, 1, 5, 5, 1700, 1500, 7, 5, 0);
	Individuo *ind2 = new Individuo(2, 0.5, 4, 5, 1700, 1000, 7, 5, 0);

	//Conectar com Vrep e sensores
	cout << "Conectando..." << endl;

	clientId = simxStart(ip.c_str(), port, true, true, 3000, 5);
	if (clientId != -1) {
		cout << "Conectado!" << std::endl;

		ind1->setClientId(clientId);
		ind1->loadModel();
		ind1->initStreamingSensors();
		ind1->initRobotVRep();

		ind2->setClientId(clientId);
		ind2->loadModel();
		ind2->initStreamingSensors();
		ind2->initRobotVRep();
		PAUSE;

		//Laço principal
		tStart = clock();
		while (simxGetConnectionId(clientId) != -1) {
			simxPauseCommunication(clientId, 1);
			ind1->action();
			ind2->action();
			simxPauseCommunication(clientId, 0);

			tEnd = clock();
			if ((tEnd - tStart) >= 30000) {

				simxStopSimulation(clientId, simx_opmode_oneshot);
				
			}
		}

		simxFinish(clientId);
		cout << "Conexão encerrada" << std::endl;
	}
	else
		cout << "Não conectado!" << std::endl;
}