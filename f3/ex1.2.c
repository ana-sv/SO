// Ana Videira - 2015012218 
// Sistemas Operativos 2021/2022

// comando ps a -> conseguimos ver o aparecimento( e desaparecimento) do processo resultante da execução do programa 

// PID – O número do processo
// TTY – O nome do console em que está “logado” o utilizador 
// TIME - Tempo que o processo utilizou da CPU (horas:minutos:segundos)
// COMMAND – O nome do comando que disparou o processo



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv) {

    char str[100];
    printf("\nEscreva qualquer coisa! ");
    scanf("%s", str);
    printf("\nEscreveu:  %s", str);

}