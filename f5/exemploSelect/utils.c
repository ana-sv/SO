#include "utils.h"



void sayThisAndExit(char * p){
    perror(p);
    exit(EXIT_FAILURE);
}


void exitByCrtlC(int s){
    printf("\n -> Crtl ^C Ativated " );
    exit(EXIT_SUCCESS);
}

int max(int a, int b){
    return (a>b) ? a: b;
}


void keyboard(){
    char buffer[200];
    int bytes;

    fgets(buffer, sizeof(buffer), stdin );  // scanf("%s", buffer);
    if( strlen(buffer)>0 && (buffer[strlen(buffer)-1]=='\n')  ){ // se tem lá alguma coisa que termina com \n 
        buffer[strlen(buffer)-1] == '\0';
    } 
    printf("[KEYBOARD: %s]\n", buffer);
    fflush(stdout);

    if(strcmp(buffer,"sair")==0){
        unlink("pipe_a");
        unlink("pipe_b");
        exit(EXIT_SUCCESS);
    }


}