#ifndef DEFINES_H
#define DEFINES_H

	//Delta para mutação
	#define DELTA_VEL_ATK 2
	#define DELTA_VEL_DEF 2
	#define DELTA_T_ATK 1
	#define DELTA_T_DEF 1
	#define DELTA_TORQUE 2
	#define DELTA_WEIGHT 2
	#define DELTA_PROB 0.05

	//Pontuação
	#define VICTORY 3
	#define DRAW 1
	#define DEFEAT 0

	//Altura mínima para considerar robo em queda livre
	#define MIN_HEIGHT -2

	//Estados da máquina de estados
	#define IDLE 1000
	#define ALIGN_ATK 1001
	#define ATK 1002
	#define ALIGN_DODGE 1003
	#define DODGE 1004

	//Percentual gênico do pai de melhor fitness
	#define CROSS_PERC 0.7

	//Taxa de mutação
	#define MUT_RATE 0.3

	//Tamanho da população do genético
	#define POP_SIZE 10

	//Distância máxima para leitura dos sensores
	#define MAX_DIST 10

	//Número de gerações para evoluir
	#define MAX_GEN 10

	//Controle da velocidade do robo
	#define FRONT -1
	#define BACK 1

	//Tempo de cada partida em milissegundos de tempo real(não de simulação)
	#define T_MAX 5000

	//Velocidade de rotação
	#define V_ROT 0.5

	//Pausa na execução
	#define PAUSE system("PAUSE")


#endif