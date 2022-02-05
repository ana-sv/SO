#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <time.h>

void mostra(){
    printf("\n[ signal ] WAKE UP LOSER!\n");
    alarm(10);
}

int main(int argc, char const *argv[]){
    int i,res, nErradas=0, nCertas=0, tempo=10, num1,num2;
    char str[40];

    srand( (unsigned int) time(NULL) );
    signal(SIGALRM,mostra);
    printf("\n[MY PID: %d]", getpid());

    do{

        printf("\n[%d] Erradas \t [%d] Certas\n", nErradas, nCertas);

        num1 = rand() % 101;
        num2 = rand() % 101;
        printf("\n%d seconds left.....", tempo);
        printf( "\n%d + %d ? \n", num1,num2);
        fflush(stdout);
        alarm(tempo);
        scanf("%d", &res);
        alarm(0);

        if(res == num1+num2 ){
            nCertas++;
            tempo++;
        }else{
            nErradas++;
            tempo--;
        }

 
    }while( tempo>0  );

    exit(0);
}