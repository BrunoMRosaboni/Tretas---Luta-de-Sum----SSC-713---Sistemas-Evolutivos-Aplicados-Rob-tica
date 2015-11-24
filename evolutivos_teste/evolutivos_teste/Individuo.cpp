#include "Individuo.h"
#include <iostream>
using namespace std;

Individuo::Individuo() {
	init(-1, -1, -1, -1, -1, -1, -1,-1);
}

Individuo::Individuo(short int vId, float vProbAtk, float vVelAtk, float vVelDef, float vTAtk,float vTDef, float vTorque, float vFitness) {
	init(vId, vProbAtk, vVelAtk, vVelDef, vTAtk,vTDef, vTorque, vFitness);
}

void Individuo::init(short int vId, float vProbAtk, float vVelAtk, float vVelDef, float vTAtk, float vTDef,float vTorque, float vFitness) {
	this->id = vId;
	this->probAtk = vProbAtk;
	this->velAtk = vVelAtk;
	this->velDef = vVelDef;
	this->tAtk = vTAtk;
	this->tDef = vTDef;
	this->torque = vTorque;
	this->fitness = vFitness;

	this->state = IDLE;
	this->prevState = IDLE;

	srand(time(NULL));
}

void Individuo::initStreamingSensors() {
	cout << "Conexão dos motores e sensores do robo #"+to_string(this->id)+"\n";

	sensorName = "Pioneer_p3dx_leftMotor_robot_"+to_string(this->id);

	if (simxGetObjectHandle(this->clientId, sensorName.c_str(),
		&motorLeft, simx_opmode_oneshot_wait) == simx_return_ok)
		cout << "Conectado no motor esquerdo." << std::endl;
	else
		cout << "Não conectado no motor esquerdo." << std::endl;

	sensorName = "Pioneer_p3dx_rightMotor_robot_" + to_string(this->id);
	if (simxGetObjectHandle(this->clientId, sensorName.c_str(),
		&motorRight, simx_opmode_oneshot_wait) == simx_return_ok)
		cout << "Conectado no motor direito." << std::endl;
	else
		cout << "Não conectado no motor direito." << std::endl;

	for (int i = 0; i < 2; i++) {
		sensorName = "LaserPointer_sensor_front_" + to_string(i + 1)+"_robot_"+to_string(this->id);
		if (simxGetObjectHandle(this->clientId, sensorName.c_str(), &laserPointerFront[i], simx_opmode_oneshot_wait) == simx_return_ok) {
			cout << "Conectado ao laser pointer front #" << i + 1 << endl;
			simxReadProximitySensor(this->clientId, laserPointerFront[i], NULL, NULL,
				NULL, NULL, simx_opmode_streaming);
		}
		else {
			cout << "Nao conectado ao laser pointer" << endl;
		}

		sensorName = "LaserPointer_sensor_back_" + to_string(i + 1) + "_robot_" + to_string(this->id);
		if (simxGetObjectHandle(this->clientId, sensorName.c_str(), &laserPointerBack[i], simx_opmode_oneshot_wait) == simx_return_ok) {
			cout << "Conectado ao laser pointer back #" << i + 1 << endl;
			simxReadProximitySensor(this->clientId, laserPointerBack[i], NULL, NULL,
				NULL, NULL, simx_opmode_streaming);
		}
		else {
			cout << "Nao conectado ao laser pointer" << endl;
		}

		sensorName = "LaserPointer_sensor_right_" + to_string(i + 1) + "_robot_" + to_string(this->id);
		if (simxGetObjectHandle(this->clientId, sensorName.c_str(), &laserPointerRight[i], simx_opmode_oneshot_wait) == simx_return_ok) {
			cout << "Conectado ao laser pointer right #" << i + 1 << endl;
			simxReadProximitySensor(this->clientId, laserPointerRight[i], NULL, NULL,
				NULL, NULL, simx_opmode_streaming);
		}
		else {
			cout << "Nao conectado ao laser pointer" << endl;
		}

		sensorName = "LaserPointer_sensor_left_" + to_string(i + 1) + "_robot_" + to_string(this->id);
		if (simxGetObjectHandle(this->clientId, sensorName.c_str(), &laserPointerLeft[i], simx_opmode_oneshot_wait) == simx_return_ok) {
			cout << "Conectado ao laser pointer back #" << i + 1 << endl;
			simxReadProximitySensor(this->clientId, laserPointerLeft[i], NULL, NULL,
				NULL, NULL, simx_opmode_streaming);
		}
		else {
			cout << "Nao conectado ao laser pointer" << endl;
		}
	}
}

void Individuo::action() {
	switch (state) {
	case IDLE:
		prevState = state;
		if ((double)rand() / (double)RAND_MAX < this->probAtk) {
			state = ALIGN_ATK;
		}
		else {
			state = ALIGN_DODGE;
		}
		break;

	case ALIGN_ATK:
		prevState = state;

		activeSensorCounterFront = 0;
		activeSensorCounterBack = 0;

		
		//Checar sensores dianteiros
		for (int i = 0; i < 2; i++) {
			if (simxReadProximitySensor(this->clientId, laserPointerFront[i], &res,
				coord, NULL, NULL, simx_opmode_buffer) == simx_return_ok) {
				//Checar coordenada z(pois está que aponta pra frente)
				this->sensorDist = coord[2];
				if ((this->sensorDist < MAX_DIST) && (res > 0)) {
					activeSensorCounterFront++;
				}
			}
		}

		//Checar sensores traseiros
		for (int i = 0; i < 2; i++) {
			if (simxReadProximitySensor(this->clientId, laserPointerBack[i], &res,
				coord, NULL, NULL, simx_opmode_buffer) == simx_return_ok) {
				//Coordenada Z
				this->sensorDist = coord[2];
				if ((this->sensorDist < MAX_DIST) && (res > 0)) {
					activeSensorCounterBack++;
				}
			}
		}

		//Se os dois sensores da frente estão apontando para o inimigo então atacar pela frente
		if (activeSensorCounterFront > 1) {
			//Contabilizar instante de início de ataque
			if (clock == false) {
				clock = true;
				time(&startTime);
			}
			state = ATK;
			dir = FRONT;
		}//Senão atacar dando ré
		else if (activeSensorCounterBack > 1) {
			//Contabilizar instante de início de ataque
			if (clock == false) {
				clock = true;
				time(&startTime);
			}
			state = ATK;
			dir = BACK;
		}
		else {//Se nada for encontrado, então continuar procurando					
			
			simxSetJointTargetVelocity(this->clientId, motorLeft, -V_ROT,
				simx_opmode_streaming);
			simxSetJointTargetVelocity(this->clientId, motorRight, V_ROT,
				simx_opmode_streaming);
			//extApi_sleepMs(100);
		}
		break;

	case ATK:
		prevState = state;
		time(&endTime);

		//Se tempo de ataque acabou então voltar ao estado inicial
		if (difftime(endTime, startTime) >= this->tAtk) {
			state = IDLE;
			clock = false;
		}
		else {
			//Atacar
			simxSetJointTargetVelocity(this->clientId, motorLeft, dir*velAtk,
				simx_opmode_streaming);
			simxSetJointTargetVelocity(this->clientId, motorRight, dir*velDef,
				simx_opmode_streaming);
			//extApi_sleepMs(100);
			state = ALIGN_ATK;
		}

		break;

	case ALIGN_DODGE:

		prevState = state;

		activeSensorCounterRight = 0;
		activeSensorCounterLeft = 0;

		//Checar sensores da direita
		for (int i = 0; i < 2; i++) {
			if (simxReadProximitySensor(this->clientId, laserPointerRight[i], &res,
				coord, NULL, NULL, simx_opmode_buffer) == simx_return_ok) {
				//Checar coordenada z(pois está que aponta pra frente)							
				this->sensorDist = coord[2];
				if ((this->sensorDist < MAX_DIST) && (res > 0)) {
					activeSensorCounterRight++;
				}
			}
		}

		//Checar sensores da esquerda
		for (int i = 0; i < 2; i++) {
			if (simxReadProximitySensor(this->clientId, laserPointerLeft[i], &res,
				coord, NULL, NULL, simx_opmode_buffer) == simx_return_ok) {
				//Coordenada Z
				this->sensorDist = coord[2];
				if ((this->sensorDist < MAX_DIST) && (res > 0)) {
					activeSensorCounterLeft++;
				}
			}
		}

		//Se os dois sensores da frente estão apontando para o inimigo então atacar pela frente
		if (activeSensorCounterRight > 1) {
			//Contabilizar instante de início de ataque
			if (clock == false) {
				clock = true;
				time(&startTime);
			}
			state = DODGE;
			dir = FRONT;
		}//Senão atacar dando ré
		else if (activeSensorCounterLeft > 1) {
			//Contabilizar instante de início de ataque
			if (clock == false) {
				clock = true;
				time(&startTime);
			}
			state = DODGE;
			dir = BACK;
		}
		else {//Se nada for encontrado, então continuar procurando					
			
			simxSetJointTargetVelocity(this->clientId, motorLeft, -V_ROT,
				simx_opmode_streaming);
			simxSetJointTargetVelocity(this->clientId, motorRight, V_ROT,
				simx_opmode_streaming);
			//extApi_sleepMs(100);
		}
		break;

	case DODGE:
		prevState = state;
		time(&endTime);

		//Se tempo de ataque acabou então voltar ao estado inicial
		if (difftime(endTime, startTime) >= tDef) {
			state = IDLE;
			clock = false;
		}
		else {
			//Esquivar
			simxSetJointTargetVelocity(this->clientId, motorLeft, dir*velDef,
				simx_opmode_streaming);
			simxSetJointTargetVelocity(this->clientId, motorRight, dir*velDef,
				simx_opmode_streaming);
			
		}
		break;

	}

	if (state != prevState) {
		cout << "Robot_"<<to_string(this->id)<<": Mudanca de estado: " << stateName(prevState) << " para " << stateName(state) << endl;
	}
}


string Individuo::stateName(short int value) {
	switch (value) {
	case IDLE:
		return "IDLE";
		break;

	case ALIGN_ATK:
		return "ALIGN_ATK";
		break;

	case ALIGN_DODGE:
		return "ALIGN_DODGE";
		break;

	case ATK:
		return "ATK";
		break;

	case DODGE:
		return "DODGE";
		break;
	}
}

void const Individuo::print() {
	cout << "Robot_" << to_string(this->id) << endl
		<< "probAtk: " << this->probAtk << endl
		<< "velAtk: " << this->velAtk << endl
		<< "velDef " << this->velDef << endl
		<< "tAtk: " << this->tAtk << endl
		<< "torque: " << this->torque << endl
		<< "fitness: " << this->fitness << endl;
}

short int const Individuo::getId() {
	return this->id;
}

float const Individuo::getProbAtk() {
	return this->probAtk;
}

float const Individuo::getVelAtk() {
	return this->velAtk;
}

float const Individuo::getVelDef() {
	return this->velDef;
}

float const Individuo::getTAtk() {
	return this->tAtk;
}

float const Individuo::getTDef() {
	return this->tDef;
}

float const Individuo::getTorque() {
	return this->torque;
}

float const Individuo::getFitness() {
	return this->fitness;
}

int const Individuo::getClientId(){
	return this->clientId;
}


void Individuo::setProbAtk(const float value) {
	this->probAtk = value;
}
void Individuo::setVelAtk(const float value) {
	this->velAtk = value;
}
void Individuo::setVelDef(const float value) {
	this->velDef = value;
}
void Individuo::setTAtk(const float value) {
	this->tAtk = value;
}
void Individuo::setTDef(const float value) {
	this->tDef = value;
}
void Individuo::setTorque(const float value) {
	this->torque = value;
}
void Individuo::setFitness(const float value) {
	this->fitness = value;
}
void Individuo::setId(const short int value) {
	this->id = value;
}
void Individuo::setClientId(const int value) {
	this->clientId = value;
}

