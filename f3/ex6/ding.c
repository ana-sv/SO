// Ana Videira - 2015012218 
// Sistemas Operativos 2021/2022


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv) {
	char * ptdic[] ={"ola", "dia", "noite", "manha", "tarde"};
	char * usdic[] ={"hello", "day", "night", "morning", "afternoon"};
	
    printf("Traducao em Ingles: ");
	if (argc != 2) {
		printf ("Síntaxe: %s Palavra_A_Traduzir", argv[0]);
		return (EXIT_FAILURE);
	}
	for (int i=0; i < 5; i++) {
		if (strcmp(argv[1], ptdic[i]) == 0) {
			printf("%s\n",usdic[i]);
			return (EXIT_SUCCESS);
		}
	}
	printf("Word translation not found!\n");
    return (EXIT_SUCCESS);
}