#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>
#include <signal.h>

#include <pthread.h>

void sayThisAndExit(char *p)
{
    perror(p);
    exit(EXIT_FAILURE);
}

void ExitByCrtlC(int s)
{
    printf("\n -> Crtl ^C Ativated ");
    exit(EXIT_SUCCESS);
}