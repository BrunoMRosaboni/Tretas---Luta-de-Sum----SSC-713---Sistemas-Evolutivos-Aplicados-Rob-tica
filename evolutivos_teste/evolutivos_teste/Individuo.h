#ifndef INDIVIDUO_H
#define INDIVIDUO_H
#include "Defines.h"
#include <time.h>
#include <iostream>
#include <string>

extern "C" {
	#include "remoteApi/extApi.h"
}

using namespace std;

class Individuo {

public:

	Individuo();
	Individuo(short int vId,float vProbAtk, float vVelAtk, float vVelDef, float vTAtk,float vTDef, float vTorque,float vWeight, float vFitness);
	
	//Inicializar informações genéticas
	void init(short int vId,float vProbAtk, float vVelAtk, float vVelDef, float vTAtk,float vTDef, float vTorque,float vWeight, float vFitness);
	
	//Inicializar streaming dos sensores
	void initStreamingSensors();

	//Mostrar informações genéticas
	void const print();

	//Inicializar parâmetros peso, torque e posição inicial ao vRep
	void initRobotVRep();

	//Remover modelo da cena
	void removeModel();

	//Carregar modelo na cena
	void loadModel();

	//Executar uma ação
	void action();

	//Verificar se robo caiu
	bool freeFall();

	//Pontuar indivíduo de acordo com o resultado de uma partida
	void evaluate(short int res);

	//Zerar Fitness
	void resetFitness();

	//Retornar nome do robo
	string const getRobotName();

	//Nome de um estado
	string stateName(short int value);

	float const getProbAtk();
	float const getVelAtk();
	float const getVelDef();
	float const getTAtk();
	float const getTDef();
	float const getTorque();
	float const getWeight();
	float const getFitness();
	short int const getId();
	int const getClientId();

	void setProbAtk(const float value);
	void setVelAtk(const float value);
	void setVelDef(const float value);
	void setTAtk(const float value);
	void setTDef(const float value);
	void setTorque(const float value);
	void setWeight(const float value);
	void setFitness(const float value);
	void setId(const short int value);
	void setClientId(const int value);


private:
	float probAtk;
	float velAtk;
	float velDef;
	float vRot;
	float tAtk;
	float tDef;
	float torque;
	float weight;
	float fitness;
	short int id;
	string robotName;

	//Client ID para comunicação com o VREP
	int clientId;
	
	//Descritores dos motores, sensores e corpo
	int motorLeft, motorRight,casterWheel;
	int laserPointerFront[2];
	int laserPointerBack[2];
	int laserPointerRight[2];
	int laserPointerLeft[2];
	int dir;
	int body;

	//String auxiliar para obtenção dos descritores dos sensores e motores
	string sensorName;

	//Variáveis para contabilizar tempo de ataque e defesa
	clock_t startTime;
	clock_t endTime;

	//Flag para indicar contagem de tempo
	bool clockFlag = false;

	//Estado atual
	short int state;
	short int prevState;

	//Distância de um sensor a um objeto
	float sensorDist;

	//inteiro auxiliar para contar quantos sensores consegue detectar algum objeto
	short int activeSensorCounterFront;
	short int activeSensorCounterBack;
	short int activeSensorCounterRight;
	short int activeSensorCounterLeft;

	//Coordenadas do robo
	float position[3];

	//Variáveis para leitura dos sensores
	simxUChar res;
	simxFloat coord[3];

};

#endif