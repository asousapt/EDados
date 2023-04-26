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
			printf("Input invalido, por favor volte a introduzir");
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
	if (hora == 0 && minutos == 0 ) return 0; 
	if (hora < 0 || hora > 23) return 0; 
	if (minutos < 0 || minutos > 59) return 0; 
			
	return 1;
}