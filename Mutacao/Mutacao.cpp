/*Função de mutação -- Tretas de Robo*/
/*
Exemplo:
* individuo
*   prob: 0.5
*   velAtk: 1
*   VelDef: 1
*   tAtk: 3
*   tDef: 3
*   torque: 10
*   peso: 50
*   fitness: 15
*/

/*0% a 100%*/
#define PROB_OCORRENCIAMUTSUP 1
#define PROB_OCORRENCIAMUTINF 0

/*Mutação para velAtk*/
#define VELATK_TAXADEMUTACAO 0.6
#define VELATK_SUPERIORLIMITMUT 0.5
#define VELATK_INFERIORLIMITMUT -0.5
/*Mutação para velDef*/
#define VELDEF_TAXADEMUTACAO 0.6
#define VELDEF_SUPERIORLIMITMUT 0.5
#define VELDEF_INFERIORLIMITMUT -0.5
/*Mutação par tAtk*/
#define TATK_TAXADEMUTACAO 0.6
#define TATK_SUPERIORLIMITMUT 0.5
#define TATK_INFERIORLIMITMUT -0.5
/*Mutação para tDef*/
#define TDEF_TAXADEMUTACAO 0.6
#define TDEF_SUPERIORLIMITMUT 0.5
#define TDEF_INFERIORLIMITMUT -0.5
/*Mutação para Torque*/
#define TORQUE_TAXADEMUTACAO 0.6
#define TORQUE_SUPERIORLIMITMUT 0.5
#define TORQUE_INFERIORLIMITMUT -0.5
/*Mutação para Peso*/
#define PESO_TAXADEMUTACAO 0.6
#define PESO_SUPERIORLIMITMUT 0.5
#define PESO_INFERIORLIMITMUT -0.5



void mutacao(Individuo* AuxIndividuo)
{
	double Escolha, Seed;

	srand((double)time(NULL));

	/*Gera uma semente*/
	GeraSemente(&Seed);
	//Escolha = CalculaValores(PROB_OCORRENCIAMUTINF, PROB_OCORRENCIAMUTSUP, &Seed);
	Escolha = DistribuicaoUniforme(PROB_OCORRENCIAMUTINF, PROB_OCORRENCIAMUTSUP, Seed);
	if (VELATK_TAXADEMUTACAO > Escolha)
	{
		GeraSemente(&Seed);
		//Escolha = CalculaValores(VELATK_INFERIORLIMITMUT, VELATK_SUPERIORLIMITMUT, &Seed);
		Escolha = DistribuicaoUniforme(VELATK_INFERIORLIMITMUT, VELATK_SUPERIORLIMITMUT, Seed);
		AuxIndividuo->velAtk = AuxIndividuo->velAtk + Escolha;
	}
	
	GeraSemente(&Seed);
	Escolha = DistribuicaoUniforme(PROB_OCORRENCIAMUTINF, PROB_OCORRENCIAMUTSUP, Seed);
	if (VELDEF_TAXADEMUTACAO > Escolha)
	{
		GeraSemente(&Seed);
		Escolha = DistribuicaoUniforme(VELDEF_INFERIORLIMITMUT, VELDEF_SUPERIORLIMITMUT, Seed);
		AuxIndividuo->velDef = AuxIndividuo->velDef + Escolha;
	}

	GeraSemente(&Seed);
	Escolha = DistribuicaoUniforme(PROB_OCORRENCIAMUTINF, PROB_OCORRENCIAMUTSUP, Seed);
	if (TATK_TAXADEMUTACAO > Escolha)
	{
		GeraSemente(&Seed);
		Escolha = DistribuicaoUniforme(TATK_INFERIORLIMITMUT, TATK_SUPERIORLIMITMUT, Seed);
		AuxIndividuo->tAtk = AuxIndividuo->tAtk + Escolha;
	}

	GeraSemente(&Seed);
	Escolha = DistribuicaoUniforme(PROB_OCORRENCIAMUTINF, PROB_OCORRENCIAMUTSUP, Seed);
	if (TDEF_TAXADEMUTACAO > Escolha)
	{
		GeraSemente(&Seed);
		Escolha = DistribuicaoUniforme(TDEF_INFERIORLIMITMUT, TDEF_SUPERIORLIMITMUT, Seed);
		AuxIndividuo->tDef = AuxIndividuo->tDef + Escolha;
	}

	GeraSemente(&Seed);
	Escolha = DistribuicaoUniforme(PROB_OCORRENCIAMUTINF, PROB_OCORRENCIAMUTSUP, Seed);
	if (TORQUE_TAXADEMUTACAO > Escolha)
	{
		GeraSemente(&Seed);
		Escolha = DistribuicaoUniforme(TORQUE_INFERIORLIMITMUT, TORQUE_SUPERIORLIMITMUT, Seed);
		AuxIndividuo->torque = AuxIndividuo->torque + Escolha;
	}

	GeraSemente(&Seed);
	Escolha = DistribuicaoUniforme(PROB_OCORRENCIAMUTINF, PROB_OCORRENCIAMUTSUP, Seed);
	if (PESO_TAXADEMUTACAO > Escolha)
	{
		GeraSemente(&Seed);
		Escolha = DistribuicaoUniforme(PESO_INFERIORLIMITMUT, PESO_SUPERIORLIMITMUT, Seed);
		AuxIndividuo->peso = AuxIndividuo->peso + Escolha;
	}
}

/*Antiga função para calculo de valores a partir de uma distribuição uniforme utilizando a biblioteca gsl*/
/*double CalculaValores(float LimiteInferior, float LimiteSuperior, unsigned long int* Seed)
{
	const gsl_rng_type * T;
  	gsl_rng * r;
  	double Valor;

  	T = gsl_rng_default;
  	r = gsl_rng_alloc (T);*/

  	/*A linha a seguir atribui uma semente diferente toda vez que a função é exexutada*/
/*  	gsl_rng_set (r, *Seed);

  	Valor = gsl_ran_flat(r, LimiteInferior, LimiteSuperior);

  	gsl_rng_free (r);

  	return Valor;
}*/

void GeraSemente(double* Seed)
{
	double aux;

	do
	{
		aux = rand() % 1;

	}while(aux == *Seed);

	*Seed = aux;
}

double DistribuicaoUniforme(double min, double max, double Seed)
{
	double x;
	
	x = (Seed * (max - min)) + min;

	return x;
}