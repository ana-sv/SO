#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{

    char str[40];
    int status, n;
    int fd[2]; // leitura e o 0, escrita é o 1
    void *estado;

    pipe(fd);

    if (n = (fork()) == 0)
    {
        printf("(FILHO) Sou o %d, o meu pai e o %d\n", getpid(), getppid());

        close(0); //fecha o stdin

        dup(fd[0]); // duplicar a extremidade de leitura do pipe na posiçao 0 , substitur pelo stdin que esta na posiçao 0

        // filho fica com o controlo

        close(fd[0]);
        close(fd[1]);

        execlp("tr", "tr", "a-z", "A-Z", NULL);

        exit(1);
    }
    else
    {
        printf("PALAVRA: ");
        scanf("%s", str);

        write(fd[1], str, strlen(str));
        write(fd[1], "\n", 1);

        //envia palavra ao filho atraves do pipe

        wait(&estado);
    }

    return (EXIT_SUCCESS);
}
