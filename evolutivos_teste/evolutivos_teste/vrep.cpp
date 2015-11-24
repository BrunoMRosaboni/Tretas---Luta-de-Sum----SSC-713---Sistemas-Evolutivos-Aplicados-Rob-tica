extern "C" {
	#include "remoteApi/extApi.h"
}
#include <stdio.h>

#include <iostream>
#include <string>
#include <time.h>
#include "Individuo.h"
#include "Defines.h"
//#include <gsl/gsl_rng.h>
//#include <gsl/gsl_sf_bessel.h>



using namespace std;
//string stateName(short int state);

int main() {

	//double x = 5.0;
	//double y = gsl_sf_bessel_J0(x);
	//printf("J0(%g) = %.18e\n", x, y);

	Individuo *ind1 = new Individuo(1,0.7,4,4,1.5,1.5,6,0);
	Individuo *ind2 = new Individuo(2, 0.7, 5, 5, 1, 1, 20, 0);
	//ind1->print();
	//exit(0);

	string ip = "127.0.0.1";
	int port = 2500;
	int clientId;
	
	//Conectar com Vrep e sensores
	cout << "Conectando..." << endl;
	
		clientId = simxStart(ip.c_str(), port, true, true, 3000, 5);
	if (clientId != -1) {
		cout << "Conectado!" << std::endl;
		ind1->setClientId(clientId);
		ind1->initStreamingSensors();

		ind2->setClientId(clientId);
		ind2->initStreamingSensors();

		//Laço principal
		while (simxGetConnectionId(clientId) != -1) {		
			ind1->action();
			ind2->action();
		}

		simxFinish(clientId);
		cout << "Conexão encerrada" << std::endl;
	}
	else
		cout << "Não conectado!" << std::endl;


	return 0;
}
