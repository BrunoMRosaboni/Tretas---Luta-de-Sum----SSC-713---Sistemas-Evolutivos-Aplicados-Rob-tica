#include "Individuo.h"

Individuo::Individuo() {
	init(-1, -1, -1, -1, -1, -1, -1,-1,-1);
}

Individuo::Individuo(short int vId, float vProbAtk, float vVelAtk, float vVelDef, float vTAtk,float vTDef, float vTorque, float vWeight,float vFitness) {
	init(vId, vProbAtk, vVelAtk, vVelDef, vTAtk,vTDef, vTorque,vWeight, vFitness);
}

void Individuo::init(short int vId, float vProbAtk, float vVelAtk, float vVelDef, float vTAtk, float vTDef,float vTorque,float vWeight, float vFitness) {
	this->id = vId;
	this->probAtk = vProbAtk;
	this->velAtk = vVelAtk;
	this->velDef = vVelDef;
	this->tAtk = vTAtk;
	this->tDef = vTDef;
	this->torque = vTorque;
	this->weight = vWeight;
	this->fitness = vFitness;
	this->robotName = "robot_" + to_string(this->id);
	
	this->state = IDLE;
	this->prevState = IDLE;	
}

void Individuo::initStreamingSensors() {
	//cout << this->robotName << ": Conexao com motores, sensores e corpo do robo #" + to_string(this->id) + "\n";

	sensorName = "Pioneer_p3dx_robot_" + to_string(this->id);

	if (simxGetObjectHandle(this->clientId, sensorName.c_str(),
		&body, simx_opmode_oneshot_wait) == simx_return_ok) {
		//cout << this->robotName << ": Conectado corpo do motor." << std::endl;
		simxGetObjectPosition(clientId, body, -1, position, simx_opmode_streaming);
	}
	else {
		cout << this->robotName << ": Nao conectado ao corpo do motor." << std::endl;
	}

	sensorName = "Pioneer_p3dx_leftMotor_robot_" + to_string(this->id);

	if (simxGetObjectHandle(this->clientId, sensorName.c_str(),
		&motorLeft, simx_opmode_oneshot_wait) == simx_return_ok) {
		//cout << this->robotName << ": Conectado no motor esquerdo." << std::endl;
	}
	else
		cout << this->robotName << ": Nao conectado no motor esquerdo." << std::endl;

	sensorName = "Pioneer_p3dx_rightMotor_robot_" + to_string(this->id);
	if (simxGetObjectHandle(this->clientId, sensorName.c_str(),
		&motorRight, simx_opmode_oneshot_wait) == simx_return_ok){
		//cout << this->robotName << ": Conectado no motor direito." << std::endl;
	}
	else
		cout << this->robotName << ": Nao conectado no motor direito." << std::endl;

	sensorName = "Pioneer_p3dx_caster_freeJoint_robot_" + to_string(this->id);
	if (simxGetObjectHandle(this->clientId, sensorName.c_str(),
		&casterWheel, simx_opmode_oneshot_wait) == simx_return_ok) {
	//	cout << this->robotName << ": Conectado a rodinha livre." << std::endl;
	}
	else
		cout << this->robotName << ": Nao conectado a rodinha livre." << std::endl;

	for (int i = 0; i < 2; i++) {
		sensorName = "LaserPointer_sensor_front_" + to_string(i + 1)+"_robot_"+to_string(this->id);
		if (simxGetObjectHandle(this->clientId, sensorName.c_str(), &laserPointerFront[i], simx_opmode_oneshot_wait) == simx_return_ok) {
			//cout << this->robotName << ": Conectado ao laser pointer front #" << i + 1 << endl;
			simxReadProximitySensor(this->clientId, laserPointerFront[i], NULL, NULL,
				NULL, NULL, simx_opmode_streaming);
		}else {
			cout << this->robotName << ": Nao conectado ao laser pointer front #" << i + 1 << endl;
		}

		sensorName = "LaserPointer_sensor_back_" + to_string(i + 1) + "_robot_" + to_string(this->id);
		if (simxGetObjectHandle(this->clientId, sensorName.c_str(), &laserPointerBack[i], simx_opmode_oneshot_wait) == simx_return_ok) {
			//cout << this->robotName << ": Conectado ao laser pointer back #" << i + 1 << endl;
			simxReadProximitySensor(this->clientId, laserPointerBack[i], NULL, NULL,
				NULL, NULL, simx_opmode_streaming);
		}else {
			cout << this->robotName << ": Nao conectado ao laser pointer back" << i + 1 << endl;
		}

		sensorName = "LaserPointer_sensor_right_" + to_string(i + 1) + "_robot_" + to_string(this->id);
		if (simxGetObjectHandle(this->clientId, sensorName.c_str(), &laserPointerRight[i], simx_opmode_oneshot_wait) == simx_return_ok) {
			//cout << this->robotName << ": Conectado ao laser pointer right #" << i + 1 << endl;
			simxReadProximitySensor(this->clientId, laserPointerRight[i], NULL, NULL,
				NULL, NULL, simx_opmode_streaming);
		}else {
			cout << this->robotName << ": Nao conectado ao laser pointer right" << i + 1 << endl;
		}

		sensorName = "LaserPointer_sensor_left_" + to_string(i + 1) + "_robot_" + to_string(this->id);
		if (simxGetObjectHandle(this->clientId, sensorName.c_str(), &laserPointerLeft[i], simx_opmode_oneshot_wait) == simx_return_ok) {
			//cout << this->robotName << ": Conectado ao laser pointer back #" << i + 1 << endl;
			simxReadProximitySensor(this->clientId, laserPointerLeft[i], NULL, NULL,
				NULL, NULL, simx_opmode_streaming);
		}else {
			cout << this->robotName << ": Nao conectado ao laser pointer back" << i + 1 << endl;
		}
	}

	/*simxGetObjectPosition(clientId, body, -1, initPosBody, simx_opmode_oneshot_wait);
	simxGetObjectPosition(clientId, motorLeft, -1, initPosLeftWheel, simx_opmode_oneshot_wait);
	simxGetObjectPosition(clientId, motorRight, -1, initPosRightWheel, simx_opmode_oneshot_wait);
	simxGetObjectPosition(clientId, casterWheel, -1, initPosCasterWheel, simx_opmode_oneshot_wait);*/
	/*cout << "X: " << initPosBody[0] << " Y: " << initPosBody[1] << " Z: " << initPosBody[2] << endl;
	cout << "X: " << initPosLeftWheel[0] << " Y: " << initPosLeftWheel[1] << " Z: " << initPosLeftWheel[2] << endl;
	cout << "X: " << initPosRightWheel[0] << " Y: " << initPosRightWheel[1] << " Z: " << initPosRightWheel[2] << endl;
	cout << "X: " << initPosCasterWheel[0] << " Y: " << initPosCasterWheel[1] << " Z: " << initPosCasterWheel[2] << endl;*/

}

void Individuo::removeModel() {
	if (simxRemoveModel(clientId, body, simx_opmode_oneshot_wait) == simx_return_ok) {
		//cout << robotName << ": modelo removido com sucesso" << endl;
	}else {
		cout << robotName << ": nao foi possivel remover o modelo" << endl;
	}
}

void Individuo::loadModel() {
	
	string fileName = "C:\\Users\\Rodrigo\\Rodrigo\\USP\\8º Semestre\\Evolutivos\\vrep_c++\\evolutivos_teste\\Debug\\"+robotName + ".ttm";
	if (simxLoadModel(clientId,fileName.c_str(), 0x1,NULL ,simx_opmode_oneshot_wait) == simx_return_ok) {
		//cout << robotName << ": modelo carregado com sucesso" << endl;
	}else {
		cout << robotName << ": erro ao carregar modelo" << endl;
	}
}

void Individuo::initRobotVRep() {
	//inicializar torque
	if (simxSetJointForce(clientId, this->motorLeft, torque, simx_opmode_oneshot_wait) == simx_return_ok) {
		//cout << this->robotName << ": torque do motor esquerdo alterado com sucesso!" << endl;
	}else {
		cout << this->robotName << ": nao foi possível alterar o torque do motor esquerdo!" << endl;
	}
	
	if (simxSetJointForce(clientId, this->motorRight, torque, simx_opmode_oneshot_wait) == simx_return_ok) {
		//cout << this->robotName << ": torque do motor direito alterado com sucesso!" << endl;
	}
	else {
		cout << this->robotName << ": nao foi possível alterar o torque do motor direito!" << endl;
	}

	//inicializar massa
	if (simxSetObjectFloatParameter(clientId, this->body, 3005, this->weight, simx_opmode_oneshot_wait) == simx_return_ok) {
		//cout << this->robotName << ": massa alterada com sucesso!"<<endl;
	}else {
		cout << this->robotName << ": nao foi possível alterar a massa do robo!" << endl;
	}

}

bool Individuo::freeFall() {
	float pos[3];
	simxGetObjectPosition(clientId, body, -1, position, simx_opmode_buffer);

	return (position[2] < MIN_HEIGHT) ? true : false;
}

void Individuo::evaluate(short int res) {
	fitness += res;
}

void Individuo::resetFitness() {
	fitness = 0;
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

		//Iniciar cronometragem da ação de ataque ou defesa
		startTime = clock();

		break;


	case ALIGN_ATK:
		prevState = state;
		endTime = clock();
		//Verificar se o tempo de ataque acabou
		if ((endTime - startTime) >= this->tAtk) {
			state = IDLE;			
		}else {

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

			//Se os dois sensores da frente estao apontando para o inimigo entao atacar pela frente
			if (activeSensorCounterFront == 2) {			
				state = ATK;
				dir = FRONT;
				
				/*simxSetJointTargetVelocity(this->clientId, motorLeft, 0,
					simx_opmode_streaming);
				simxSetJointTargetVelocity(this->clientId, motorRight, 0,
					simx_opmode_streaming);*/
			}//Senao atacar dando ré
			else if (activeSensorCounterBack == 2) {				
				state = ATK;
				dir = BACK;
				
				/*simxSetJointTargetVelocity(this->clientId, motorLeft, 0,
					simx_opmode_streaming);
				simxSetJointTargetVelocity(this->clientId, motorRight, 0,
					simx_opmode_streaming);*/
			}
			else {//Se nada for encontrado, entao continuar procurando					

				simxSetJointTargetVelocity(this->clientId, motorLeft, V_ROT,
					simx_opmode_streaming);
				simxSetJointTargetVelocity(this->clientId, motorRight, V_ROT,
					simx_opmode_streaming);
				//extApi_sleepMs(100);
			}

		}
		break;

	case ATK:
		prevState = state;
		//time(&endTime);
		endTime = clock();

		//Se tempo de ataque acabou entao voltar ao estado inicial
		if ((endTime- startTime) >= this->tAtk) {
			state = IDLE;
			//clock = false;
		}else {
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

		endTime = clock();
		if ((endTime - startTime) >= this->tDef) {
			state = IDLE;
		}else {
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

			//Se os dois sensores da direita estao apontando para o inimigo entao recuar
			if (activeSensorCounterRight > 1) {
				state = DODGE;
				dir = FRONT;
			}//Senao atacar dando ré
			else if (activeSensorCounterLeft > 1) {
				state = DODGE;
				dir = FRONT;
			}
			else {//Se nada for encontrado, entao continuar procurando					

				simxSetJointTargetVelocity(this->clientId, motorLeft, -V_ROT,
					simx_opmode_streaming);
				simxSetJointTargetVelocity(this->clientId, motorRight, V_ROT,
					simx_opmode_streaming);
				//extApi_sleepMs(100);
			}
		}

		
		break;

	case DODGE:
		prevState = state;
		
		endTime = clock();
		//Se tempo de ataque acabou entao voltar ao estado inicial
		if ((endTime - startTime) >= tDef) {
			state = IDLE;
			//clock = false;
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

	/*if (state != prevState ) {
		cout << this->robotName<<": Mudanca de estado: " << stateName(prevState) << " para " << stateName(state) << endl;
	}*/
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

string const Individuo::getRobotName() {
	return this->robotName;
}

void const Individuo::print() {
	cout << this->robotName << endl
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

float const Individuo::getWeight() {
	return this->weight;
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
void Individuo::setWeight(const float value) {
	this->weight = value;
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
