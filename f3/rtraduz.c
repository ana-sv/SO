// Ana Videira - 2015012218 
// Sistemas Operativos 2021/2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>    /* strcmp() */
#include <unistd.h>    /* exec() */
#include <sys/types.h> /* wait() */
#include <sys/wait.h>   

int translate(const char * language, const char * translator) {
    char word[25] = "";
    int pid = 0;
    int status = 0;
    char c; //to flush the standard input

    printf("\nPlease enter a word to translate to %s:", language);
    fflush(stdout);
    scanf("%24s", word);
    while ((c = getchar()) != EOF && c != '\n') {
    }

    pid = fork();
    switch (pid) {
        case -1:
            perror("Unable to fork()");
            return EXIT_FAILURE;

        case 0:
            execl(translator, translator, word, (char *) NULL);
            perror("Unable to exec()");
            return EXIT_FAILURE;

        default:
            if (wait(&status) == -1) { //we need to wait for the translation process to end
                perror("Unable to wait()");
                return EXIT_FAILURE;
            } else return EXIT_SUCCESS;
    }
}

int main(int argc, char** argv) {
    char option = 'x';
    int pid = 0;


    do {
        printf("\nSelect an option (x-exit; i-English dictionary; f-French dictionary):");
        scanf("%c", &option);
        switch (option) {
            case 'x':
                printf("Nice to meet you. Bye!");
                break;
            case 'i':
                translate("english", "ding");
                break;
            case 'f':
                translate("french", "rdfran");
                break;
            default:
                printf("Invalid option!");
                break;
        }
    } while (option != 'x');

    printf("\n%s is exiting.\n", argv[0]);
    return EXIT_SUCCESS;
}

