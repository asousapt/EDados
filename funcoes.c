#include <stdio.h>
#include <time.h>
#include "tools.h"

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
