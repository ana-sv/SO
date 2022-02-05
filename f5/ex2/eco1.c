#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define MYPIPE "pipeSO"
#define PIPE_P "pipeP%d"


typedef struct Mensagem
{
    char str[100];
    char pipeName[10];

}mensagem;


void sig_handler(int signal, siginfo_t *info, void *extra){
    if(signal == SIGINT){
        printf("\nEco vai encerrar....");
        unlink(MYPIPE);
        remove(MYPIPE);
        exit(0);
    }

}

int main(void){
    int fd1,fd2,n; 
    char str[256];
    struct sigaction action;
    mensagem sms;
    

    setbuf(stdout,NULL);
    
    // cria fifo eco
    mkfifo(MYPIPE, 0777); 

    action.sa_flags = SA_RESTART | SA_SIGINFO; //inicializar as flags 
    action.sa_sigaction = sig_handler; //registar a função

    if(sigaction(SIGINT, &action , NULL) == -1 ){
        printf("Erro ao colocar a funcao ao servico do sinal");
        exit(0);
    }

    do{

        fd1 = open(MYPIPE, O_RDONLY); //abre fifo eco com permissoes de leitura (bloqueante)
        n = read(fd1, &sms, sizeof(sms));

        printf("[ECO] Li %i bytes do pipe: -%s-.\n", n, sms.str);

        fd2 = open(sms.pipeName, O_WRONLY); // abre pipe produtor para escrita (bloqueante)
        strcpy(sms.str,"Recebi a mendagem, Obrigada! ");
        n = write(fd2, &sms, sizeof(sms) );

        close(fd1);
        close(fd2);

    }while(strcmp(str, "sair"));
    
    unlink(MYPIPE);
    return 0; 

}