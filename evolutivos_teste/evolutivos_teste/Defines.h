#ifndef DEFINES_H
#define DEFINES_H

	//Delta para mutação
	#define DELTA_VEL_ATK 2
	#define DELTA_VEL_DEF 2
	#define DELTA_T_ATK 1
	#define DELTA_T_DEF 1
	#define DELTA_TORQUE 2
	#define DELTA_PESO 2
	#define DELTA_PROB 0.05

	//Pontuação
	#define VITORIA 3
	#define EMPATE 1
	#define DERROTA 0

	//Estados da FSM
	#define IDLE 1000
	#define ALIGN_ATK 1001
	#define ATK 1002
	#define ALIGN_DODGE 1003
	#define DODGE 1004

	//Percentual gênico do pai de melhor fitness
	#define CROSS_PERC 0.7

	//Distância máxima para leitura dos sensores
	#define MAX_DIST 10

	//Controle da velocidade do robo
	#define FRONT -1
	#define BACK 1

	//Tempo de cada partida em segundos
	#define T_MAX 30

	//Velocidade de rotação
	#define V_ROT 0.3

#endif