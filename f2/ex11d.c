#include <stdio.h>
#include <stdlib.h>

int main( int argc, char const *argv[], char *envp[] ){
    int i;
    char *str;

    str = getenv("NOME");
    printf("O meu nome é %s\n", str);

    return 0 ;
}


// no terminal definir antes a variavel de ambiente: 
//export NOME="Ana Rita"
