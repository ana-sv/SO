// Ana Videira - 2015012218 
// Sistemas Operativos 2021/2022


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// EXERCICIO MODIFICADO
// São passados por argumento N asteriscos e o S o simbolo a imprimir
// Variavel de ambiente TEMPO para contar os segundos entre cada printf

int main(int argc, char** argv) {
    
    int i,n,t = 1;
    char *str;
    
    if(argc != 3 ){    //verifico se exitem 3 argumentos, o numero de argumentos + os 2 que quero 
        printf("[ERRO] Nr de args invalido!\n ");
        exit(3);
    }
    
    n=atoi(argv[1]);        // atribuo o numero de * / iterações a n 
    str = getenv("TEMPO");  // vou buscar o valor da variavel de ambiente TEMPO
    
    if(str!=NULL)
        t=atoi(str);
    
    for(i=0; i<n;i++){
        printf("%s", argv[2]);
        fflush(stdout);           //fflush() porque não temos \n no printf , fflush() permite forçar a saida do que está pendente
        sleep(t);
    }

    return (EXIT_SUCCESS);
}