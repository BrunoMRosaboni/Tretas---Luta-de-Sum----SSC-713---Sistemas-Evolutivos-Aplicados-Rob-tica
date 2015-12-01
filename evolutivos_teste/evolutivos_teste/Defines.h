#ifndef DEFINES_H
#define DEFINES_H

	//Delta para muta��o
	#define DELTA_VEL_ATK 2
	#define DELTA_VEL_DEF 2
	#define DELTA_T_ATK 1
	#define DELTA_T_DEF 1
	#define DELTA_TORQUE 2
	#define DELTA_WEIGHT 2
	#define DELTA_PROB 0.05

	//Pontua��o
	#define VICTORY 3
	#define DRAW 1
	#define DEFEAT 0

	//Altura m�nima para considerar robo em queda livre
	#define MIN_HEIGHT -2

	//Estados da m�quina de estados
	#define IDLE 1000
	#define ALIGN_ATK 1001
	#define ATK 1002
	#define ALIGN_DODGE 1003
	#define DODGE 1004

	//Percentual g�nico do pai de melhor fitness
	#define CROSS_PERC 0.7

	//Taxa de muta��o
	#define MUT_RATE 0.3

	//Tamanho da popula��o do gen�tico
	#define POP_SIZE 10

	//Dist�ncia m�xima para leitura dos sensores
	#define MAX_DIST 10

	//N�mero de gera��es para evoluir
	#define MAX_GEN 10

	//Controle da velocidade do robo
	#define FRONT -1
	#define BACK 1

	//Tempo de cada partida em milissegundos de tempo real(n�o de simula��o)
	#define T_MAX 5000

	//Velocidade de rota��o
	#define V_ROT 0.5

	//Pausa na execu��o
	#define PAUSE system("PAUSE")


#endif