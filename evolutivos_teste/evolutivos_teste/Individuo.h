#ifndef INDIVIDUO_H
#define INDIVIDUO_H
#include "Defines.h"
#include <time.h>
#include <string>

extern "C" {
	#include "remoteApi/extApi.h"
}


using namespace std;

class Individuo {

public:

	Individuo();
	Individuo(short int vId,float vProbAtk, float vVelAtk, float vVelDef, float vTAtk,float vTDef, float vTorque, float vFitness);

	//Inicializar informa��es gen�ticas
	void init(short int vId,float vProbAtk, float vVelAtk, float vVelDef, float vTAtk,float vTDef, float vTorque, float vFitness);
	
	//Inicializar streaming dos sensores
	void initStreamingSensors();

	//Mostrar informa��es gen�ticas
	void const print();

	//Executar uma a��o
	void action();

	//Nome de um estado
	string stateName(short int value);

	float const getProbAtk();
	float const getVelAtk();
	float const getVelDef();
	float const getTAtk();
	float const getTDef();
	float const getTorque();
	float const getFitness();
	short int const getId();
	int const getClientId();

	void setProbAtk(const float value);
	void setVelAtk(const float value);
	void setVelDef(const float value);
	void setTAtk(const float value);
	void setTDef(const float value);
	void setTorque(const float value);
	void setFitness(const float value);
	void setId(const short int value);
	void setClientId(const int value);

	//Descritores dos motores e sensores
	int motorLeft, motorRight;
	int laserPointerFront[2];
	int laserPointerBack[2];
	int laserPointerRight[2];
	int laserPointerLeft[2];
	int dir;

	
	//String auxiliar para obten��o dos descritores dos sensores e motores
	string sensorName;

	//Vari�veis para contabilizar tempo de ataque e defesa
	time_t startTime;
	time_t endTime;

	//Flag para indicar contagem de tempo
	bool clock = false;

	//Estado atual
	short int state;
	short int prevState;

	//Dist�ncia de um sensor a um objeto
	float sensorDist;

	//inteiro auxiliar para contar quantos sensores consegue detectar algum objeto
	short int activeSensorCounterFront;
	short int activeSensorCounterBack;
	short int activeSensorCounterRight;
	short int activeSensorCounterLeft;

	//Vari�veis para leitura dos sensores
	simxUChar res;
	simxFloat coord[3];

private:
	float probAtk;
	float velAtk;
	float velDef;
	float vRot;
	float tAtk;
	float tDef;
	float torque;
	float peso;
	float fitness;
	short int id;

	//Client ID para comunica��o com o VREP
	int clientId;
	

};

#endif