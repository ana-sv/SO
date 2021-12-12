#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define MYPIPE "pipeSO"

void sig_handler(int signal, siginfo_t *info, void *extra){
    if(signal == SIGINT){
        exit(0);
    }

}

int main(void){
    int fd1, n; 
    char str[256];
    struct sigaction action;

    setbuf(stdout,NULL);
    
    mkfifo(MYPIPE, 0777); 

    action.sa_flags = SA_RESTART | SA_SIGINFO; //inicializar as flags 
    action.sa_sigaction = sig_handler; //registar a função

    if(sigaction(SIGINT, &action , NULL) == -1 ){
        printf("Erro ao colocar a funcao ao servico do sinal");
        exit(0);
    }

    do{
        fd1 = open(MYPIPE, O_RDONLY); //abre pipe com permissoes de leitura
        n = read(fd1,str,sizeof(str) -1 );
        str[n -1] = '\0';
        printf("[ECO] Li %i bytes do pipe: -%s-.\n", n, str);

        close(fd1);
    }while(strcmp(str, "sair"));
    
    unlink(MYPIPE);
    return 0; 

}