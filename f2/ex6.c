#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[]){
    int i;
    printf("[DEBUG] Inicio...\n");

    for(i=0; i<argc; i++){
        printf("ARG[%d] = '%s'\n", i, argv[i] );
    }
    i = atoi(argv[2]);

    printf("\nComo sabe o seu programa o nome que tem o seu ficheiro executavel? ");
    printf("\nO nome do executavel e' SEMPRE o primeiro argumento a ser passado em argv");
    printf("\n[DEBUG] FIM\n");

    return(0);
}