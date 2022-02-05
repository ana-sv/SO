#include "utils.h"


void leEMostraPipes(char * quem , int fd){  // atendimento da chamada de informação via pipe 

    char buffer[200];
    int bytes;
    bytes = read( fd, buffer, sizeof(buffer) );
    buffer[bytes] = '\0';

    if( (bytes>0) && (buffer[strlen(buffer)-1] == '\n') ){
        buffer[bytes] = '\0';
    }

    printf("\n[FROM %s] %s ( %d bytes)\n",quem, buffer, bytes);

    if( strcmp(buffer, "sair" ) == 0 ){
        unlink("pipe_a");
        unlink("pipe_b");
        exit(EXIT_SUCCESS);
     }

}




int main(int argc, char *argv[])
{

    int fd_a, fd_b, fd_c; //file descriptor dos pipes
    int nfd;              // valor de retorno do select
    fd_set read_fds;      // conjunto das flags para descrtitores de ficheiros
    struct timeval tv;    // timeout para select

    signal(SIGINT, exitByCrtlC); // para interromper via Crtl^C

    //criar pipes
    mkfifo("pipe_a", 00777);
    mkfifo("pipe_b", 00777);

    // abre os pipes read+write - nonblock!
    fd_a = open("pipe_a", O_RDONLY | O_NONBLOCK);

    if (fd_a == -1)
    {
        sayThisAndExit("Error open pipe_a");
    }

    fd_b = open("pipe_b", O_RDONLY | O_NONBLOCK);
    if (fd_b == -1)
    {
        sayThisAndExit("Error open pipe_b");
    }


    while(1){

        tv.tv_sec = 10;
        tv.tv_usec = 0;

        FD_ZERO( &read_fds );       // inicializa conjunto de fd 
        FD_SET(0, &read_fds );      // adiciona stdin ao conjunto
        FD_SET(fd_a, &read_fds );   // adiciona pipe_a ao conjunto 
        FD_SET(fd_b, &read_fds );   // adiciona pipe_b ao conjunto 


        // select- vẽ se há dados nos fd (stdin , pipes) - modifica os sets
        // bloqueia ate: sinal, timeout, se há dados para ler, exceptions
        nfd = select( max(fd_a, fd_b) +1, &read_fds, NULL, NULL , &tv);
                     
        // max(fd_a, fd_b) +1 -----> max valor dos vários df +1
        // &read_fds, -----> read fd set 
        // NULL ---> write fd set 
        // NULL ----> exception set
        //  & tv -----> timeout se ambos a 0 -> retorna logo (polling) ; atualiza tv -> quanto tempo faltava para o timeout

        if( nfd == 0 ){
            printf("\nEstou a espera... \n ");
            fflush(stdout);
            continue;
        }

        if ( nfd == -1){
            close(fd_a); 
            close(fd_b);
            unlink("pipe_a");
            unlink("pipe_b");
            sayThisAndExit("Select error");
        }

        if( FD_ISSET(0, &read_fds) ){ // STDIN TEM ALGO PARA LER???
            keyboard();
            // sem "continue" porque nao vai logo para a proxima iteração, pode ser que pipe_a ou pipe_b tenham algo
        }

        if( FD_ISSET(fd_a, &read_fds) ){ // FD_A TEM ALGO PARA LER?? ( PIPE_A )
            leEMostraPipes("A", fd_a );
            // sem "continue" porque nao vai logo para proxima iteração, pode ser que pipe_b tenham algo 
        }

        if( FD_ISSET(fd_b, &read_fds) ){  // FD_B TEM ALGO PARA LER?? ( PIPE_B )
            leEMostraPipes("B", fd_b);
            // em " continue" ! 
        }

    }

    return EXIT_SUCCESS; // em principio, neste exemplo, nao chegará aqui

}