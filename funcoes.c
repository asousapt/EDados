#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "ListaGenerica.h"
#include "funcoes.h"

int validarInt(char *pergunta, int menor,int maior){
	int num;
	do{
		printf("%s(%d-%d)", pergunta,menor,maior);
		scanf("%d", &num);
		if(num<menor ||num>maior){
			printf("Input invalido, por favor volte a introduzir(%d-%d)",menor,maior);
		}
	}while(num<menor ||num>maior);
	fflush(stdin);
	return num;
}

char *getString(char *pergunta){
	char string[100];
	printf("%s",pergunta);
	gets(string);
	fflush(stdin);
	return string;
}

int aleatorio(int min, int max){ 
	return min + rand()%(max-min+1);
}

int validaHoras(int hora, int minutos) {
	if (hora == 0 && minutos == 0 ){
		printf("Hora invalida (00:01 - 23:59)");
		return 0; 
	} 
	if (hora < 0 || hora > 23) {
		return 0;
		printf("Hora invalida (00:01 - 23:59)");
	} 
	if (minutos < 0 || minutos > 59) {
		printf("Hora invalida (00:01 - 23:59)");
		return 0; 
	}

	return 1;
}

time_t convertToTime(int hora, int minutos){
	time_t x = time(0);
	struct tm *tmp = localtime(&x);
	tmp->tm_hour = hora;
	tmp->tm_min = minutos;
	time_t tempo = mktime(tmp);
	return tempo;
}

int validaHorasFecho(int hora,int minutos,time_t abertura){
	if(!validaHoras(hora,minutos)) return 0;
	time_t fecho = convertToTime(hora,minutos);
	if(difftime(fecho,abertura)<0){
		printf("Tempo de fecho invalido, coloque um tempo de fecho maior que o tempo de abertura");
		return 0;
	}
	return 1;
}

//Caixa que mais atendeu pessoas
CAIXA *CaixaMaisAtendeu(ListaGenerica *lg){
	CAIXA *caixa = Maior(lg,CompararPessoas);
	return caixa;
}

//Caixa que mais vendeu
CAIXA *CaixaMaisAtendeu(ListaGenerica *lg){
	CAIXA *caixa = Maior(lg,CompararProdutos);
	return caixa;
}