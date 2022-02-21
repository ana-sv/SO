# Exame 2021-2022 - Época Normal 
#### 22 Janeiro 2022
## Parte I - Sem Consulta

#### 1) Assuma que encontra um sistema Unix em que as passwords dos utilizadores estão encriptadas, no ficheiro/etc/passwd. Descreva detalhadamente os méritos e os problemas desta situação. Se achar que há problemas, exemplifique uma ação que poss por em causa o sistema com base na situação descrita. Se não houver problema nenhum justifique também. 

O ficheiro /etc/passwd é o ficheiro mais importante do sistema Linux pois armazena a informação sobre os utilizadosres do sistema incluindo nomeadamente a suas passwords. Um dos problemas deste ficheiro é o facto de ser legivel por todos os utilizadores - isto cria assim um problema de proteção de dados dos utilizadores. Uma vez que o HASH (resultante da encriptação das passwords) está incluido neste ficheiro torna-se assim possivel tentar "adivinhar" uma password. Uma password encontrada pode até nem ser a mesma usada pelo utilizador mas, se gerar o mesmo HASH servirá para autentificação. 

#### 2) Num computador + sistema operativo moderno será desejavel e possivel impedir que um programa execute qualquer tipo de operação? Se achar que sim, explique porquê, como funciona e quais são os mecanismos (hardware/software) envolvidos nessa caracteristica, e indique um exemplo de algo que não deva ser permitido e porquê.

Sim, é sempre desejável impedir que um programa execute qualquer tipo de operação. Isto é possivel controlar pois um programa apenas consegue requisitar serviços do sistema através de chamadas ao sistema e isso implica passar a exeução de dentro do código do processo para o código do sistema. 
Estas chamadas aos sistema são implementadas com interrupções(traps) e são essas interrupções que impedem saltos para endereços indevidos.
A trap salta sempre para o endereço que está na tabela de interrupções, que será o inicio da rotina a invocar. 
A tabela em questão está protegida contra escrita em modo utilizador e deste modo não pode ter alterada por qualquer programa-utilizador. 


#### 3) O endereçamento virtual resolve alguns probelmas que existem no endereçamento real. Identifique dois desses problemas e explique como é que o endereçamento virtual os resolve. 

Endereçamento real - Os endereços gerados e utilizados pelos programas em execução corresmpondem diretamente  posições na memória física existente no computador. Do ponto de vista do hardware é mais simples de implementar mas encontra algumas dificuldaes e limitações importantes:
- Fragmentação decorrente da atribuição/libertação de memória
- Codigo não recolocável 
- Limmites quanto ao tamanho máximo dos programas 
- Dificuldades na concretização de isolamento e segurança 

Endereçamento Virtual - Cada processo apercebe-se de um conjunto de endereços ( espaço de endereçamento ) sem relação direta com qualquer porção de memória real.
No endereçamento virtual o espaço de endereçamento de cada processo é subdividido num conjunto de blocos. Cada bloco pode estar mapeado em qualquer zona da memória fisica, não é preciso manter a ordem que os blocos aparentam ter logo, é resolvido assim o problema de fragmentação que acontece com o endereçamento real. 
Usando a memória virtual, pode-se armazenar temporariamente em disco alguns blocos do espaço de endereçamento que não façam falta de momento resolvendo assim também a questão do limite de tamanho máximo dos programas. 

#### 4) O programa scicalc (scientific calculator) é um programa que já existe para Linux ( se o instalar) que efectua cálculos aritméticos de números de virgula flutuante. Usa-se em linha de comandos de forma que os exemplos abaixo ilustram. 
![image](https://user-images.githubusercontent.com/44445562/154860501-92717598-4966-49f1-97f1-2583d64b7a46.png)

##### Usando obrigatoriamente o programa já existente scicalc , faça um programa em C para Unix/Linux que peça ao utilizador os dois operandos e a operação a realizar e apresente o resultado no ecra no seguinte formato: se nao tiver havido erro, a mensagem é: "o resultado foi:" em que x é o valor calculado; se tiver havido erro, aparece simplesmente "enganou-se em qualquer coisa". O seu programa não é responsável por analisar a validade dos dados de entrada , mas tem que descobrir se a operação correu bem ou não e apanhar o resultado. O seu programa deve permitir ao utilizador, numa única execução, efectuar vários cálculos, terminando quando o primeiro operando for "fim".

-----------------------------------------> PRECISA DE REVISAO

```C

int main(int argc, char **argv)
{

    int str[10], pid, n;
    float resultado;

    int fd[2];
    if ( pipe(fd) < 0 ){
        perror("Erro no pipe");
        exit(1);
    }
    

    while (1)
    {

        printf("\nInsira operando1 operacao operando2: ");
        scanf("%s", str);

        if (strcmp(str, "fim") == 0)
            break;


        pid = fork();
        if (pid == -1)
        {
            perror("erro no fork");
            break;
        }
        else if (pid == 0)  // child
        { 
            close(fd[0]); // fecha o lado de ler
            execl("./scicalc", "./scicalc", str, NULL);

        }else{ // parent
          
            close(fd[1]); // fecha o lado de escrever

            n = read(fd[0], &resultado, sizeof(resultado) );
            if(n==-1)
                perror("erro ao ler pipe");

            if( resultado == -1 )
                printf("\nEnganou-se em qualquer coisa");
            else
                printf("\nO resultado foi: %f", resultado);
          
      
        };

    }

}
```



## Parte II - Com Consulta

#### 1.a) Apresente no ecra o username e user id do utilizador que tem o segundo user id mais elevado no sistema ( exemplo do conteudo do ficheiro: maria 1006 ). A correta realização desta tarefa não deve depender da pasta atual em que se encontra na linha de comandos. 


lista nomes de utilizadores e user id, substitui os : por um espaço , ordenar a 2 coluna revertida, 2 linhas a partir de cima e 1 a partir de baixo

``
cut -d: -f1,3 /etc/passwd | tr ":" " " | sort -n -k2 -r | head -2 | tail -1 
``

#### 1.b) Guarde na sua pasta pessoal um ficheiro com o nome "ficheiro.txt" cujo conteudo será com o nome e o tamanho ( apenas estes dois campos - um linha por cada ficheiro), dos cinco maiores ficheiros que se encontram na diretoria /etc. Se o ficheiro já existir, a informação é acrescentada ao que já lá estava. A correta realização desta tarefa não deve depender da pasta atual em que se encontra na linha de comandos. 

ordena ls por tamanho do ficheiro | esquece os espaços a mais| fica com a 4 e 5 colunas delimitadas por " " | 5 linhas de cima ) poe no ficheiro que está na pasta pessoal
``
ls -lS /etc | tr -s " "| cut -d " " -f4,5 | head -5  >  /home/ana/ficheiro.txt
``


#### 2) Escreva um programa que receba o nome de N ficheiros através da linha de comandos e lance N threads, indicando a cada uma o nome de um desses N ficheiros. Cada thread irá contar o número total de linhas do ficheiro que lhe foi indicado e incrementar um contador geral, comum a todas elas. O incremento é feito a cada nova linha lida no ficheiros. No final, a thread inicial do processo deverá apresentar o valor do contador geral. Se em alguma das threads, ocorrer um erro na abertura do ficheiro, ela deve terminar cada uma das threads que foram criadas, incluindo ela própria, de forma a que o processo possa encerrar também logo de seguida.

Não é necessário implementar o algoritmo que conta o número de linhas. Deve considerar a função seguinte: 

``
int leProximaLinha(char ficheiro[] ); 
``

Devolve 1 se leu mais uma linha, 0 se chegou ao fim e nao leu nada, -1 se nao conseguiu aceder ao ficheiro. 

```C
typedef struct
{
    char nomeFicheiro[50];
    int *ptrContador;          // ponteiro para o contador de linhas
    pthread_mutex_t *ptrMutex; // ponteiro para mutex
    pthread_cond_t *ptrCondv;  // ponteiro para variavel condiciona
    pthread_t tid;             // id da thread
    void *retval;              // codigo de terminação da thread
    int cancel;
} TDados;

void *funcaoThread(void *arg)
{
    TDados *dados = (TDados *)arg;
    int res;

    do
    {
        res = leProximaLinha(dados->nomeFicheiro);

        if (res == 1)
        {
            pthread_mutex_lock(dados->ptrMutex);
            dados->ptrContador++;
            pthread_mutex_unlock(dados->ptrMutex);
        }
        if (res == -1)
        {
            // erro -> envia sinal para a variavel condicional para terminar
            pthread_cond_signal(dados->ptrCondv); 
        }

    } while (res != 0 || dados->cancel == 0);
}

int main(int argc, char *argv[])
{

    int nthreads,contador=0, i, res;

    for (nthreads = 1; argv[nthreads] != NULL; nthreads++);
    nthreads--; // porque começa no 1 por causa do argv em arvg[0] é o nome do programa

    if (nthreads == 0)
    {
        printf("Sem ficheiros para contar linhas ");
        exit(1);
    }

    TDados tdados[nthreads];
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // mutex
    pthread_cond_t condv = PTHREAD_COND_INITIALIZER;   // variavel condicional

    for (i = 0; i < nthreads; i++)
    {
        tdados[i].cancel = 0;
        tdados[i].ptrContador = &contador;
        tdados[i].ptrMutex = &mutex;
        tdados[i].ptrCondv = &condv;
        strcpy(tdados[i].nomeFicheiro, argv[i + 1]);
        res = pthread_create(&tdados[i].tid, NULL, funcaoThread, (void *)&tdados[i]);
    }

    // aguarda sinalização da variavel condicional
    // bloqueia no wait e o mutex é libertado enquanto bloqueado
    // o mutex é automaticamente readquirido quando o wait acorda
    pthread_cond_wait(&condv, &mutex);

    //indicar ás threads para terminarem
    for (i = 0; i < nthreads; i++)
        tdados[i].cancel = 1; // nunca terminar threads à força

    for (i = 0; i < nthreads; i++)
        pthread_join(tdados[i].tid, &tdados[i].retval);

    printf("Numero total de linhas dos ficheiros: %d", contador );

    pthread_mutex_destroy(&mutex);

    exit(0);
}
```


#### 3) Pretende-se um sistema informatizado para gerir o acsso às caixas de fila única de um supermercado. Este sistema é constituido por um processo distribuidor (distribui clientes pelas caixas) , N processos caixas e vários processos clientes. O mecanismo de comunicação entre os varios processos é names pipes. As aplicações cliente e caixa já estão implementadas e o foco da questão é o distribuidor.

Cada novo cliente que surge irá contactar o distribuidor, fornecendo-lhe apenas uma string que corresponde ao seu nome. De seguida aguarda que caixa o contacte através do name pipe com o seu nome. Existem dois tipos de clientes, os normais e os prioritários, existindo um named pipe diferente para cada um desres dois tipos de cliente. 

O distribuidor é responsável por lançar uma nova caixa para cada novo cliente. Cada caixa atende um cliente, após que termina. Existe um número máximo de caixas em simultaneo, especificado através da variável de ambiente NCAIXAS. 

O funcionamento do distribuidor é: se ainda não tiver atingido esse número , o distribuidor averigua se tem clientes para atender, e caso tenha, lança uma caixa para ele, passando-lhe ( através de segmentos de linha de comandos ) toda a informação necessária que permita ao caixa interagir com o cliente. Se existir um cliente prioritário, será atendido antes dos clientes normais que ainda nao tenham sido atribuidos a nenhum caixa. 

Depreende-se que as caixas informam o distribuidor quando terminam o atendimento de um cliente. Essa notificação deve também ser feita por named pipe. 
Todos os names pipes aqui referidos pertencem ao distribuidor. Implemente o código do destribuidor. 



```C

int contadorCaixas;
int fdClienteN, fdClienteP, fdCaixa;

void sayThisAndExit(char *p)
{
    perror(p);
    close(fdClienteP);
    close(fdClienteN);
    close(fCaixa);
    exit(EXIT_FAILURE);
}

void exitByCrtlC(int s)
{
    printf("\n -> Crtl ^C Ativated ");
    close(fdClienteP);
    close(fdClienteN);
    close(fCaixa);
    exit(EXIT_SUCCESS);
}

int max(int a, int b, int c)  // ranhoso, but should work
{

    if (a > b && a > c)
        return a;

    if ( b> a && b > c)
        return b ;

    if (c > a && c > b)
        return c;
}




int main(int argc, char *argv[])
{
    int res, res1, res2, res3;
    int ncaixas;

    //select
    int nfd;
    fd_set read_fds;

    signal(SIGINT, exitByCrtlC); // para interromper via Crtl^C

    //recebe a variavel de ambiente NCAIXAS
    if (argc != 2)
        sayThisAndExit("Erro ao recolher variavel ambiente");

    if (ncaixas = argv[1] == 0)
        ncaixas = 10;

    //cria pipes
    mkfifo("pipeClientePrioritario", 0777);
    mkfifo("pipeClienteNormal", 0777);
    mkfifo("pipeCaixa", 0777);

    // abre pipes READ + NONBLOCK
    fdClienteP = open("pipeClientePrioritario", O_RDONLY | O_NONBLOCK);
    fdClienteN = open("pipeClienteNormal", O_RDONLY | O_NONBLOCK);
    fdCaixa = open("pipeCaixa", O_RDONLY | O_NONBLOCK);
    if (fdClienteP == -1 | fdClienteN == -1 | fdCaixa == -1)
        sayThisAndExit("Erro pipes");

    //ciclo select
    while (1)
    {
        FD_ZERO(&read_fds);
        FD_SET(fdClienteP, &read_fds);
        FD_SET(fdClienteN, &read_fds);
        FD_SET(fdCaixa, &read_fds);

        nfd = select(max(fdClienteP + fdClienteP + fdCaixa) + 1, &read_fds, NULL, NULL, NULL);

        if (nfd == -1)
           sayThisAndExit("Erro no select");

        if (contadorCaixas < ncaixas)
        {

            // lê primeiro o prioritário se tiver alguma coisa
            if (FD_ISSET(fdClienteP, &read_fds))
                readPipesClientes(fdClienteP);

            if (FD_ISSET(fdClienteN, &read_fds))
                readPipesClientes(fdClienteN);
        }

        if (FD_ISSET(fdCaixa, &read_fds))
        {

            char str[50];
            int bytes;
            bytes = read(fd, str, sizeof(str));
            if (bytes == -1)
                sayThisAndExit("Erro a ler pipe caixa");

            if (strcmp(str, "Caixa Terminada") == 0)
                contadorCaixas--;
        }
    }

    return EXIT_SUCCESS; // em principio nao chegará aqui
}



void readPipesClientes(int fd)
{
    char name[50];
    int bytes;
    int pid;

    // recebe o nome do cliente que é também o nome do seu pipe
    bytes = read(fd, name, sizeof(name));
    if (bytes == -1)
        sayThisAndExit("Erro a ler pipes ");

    if ((bytes > 0) && (name[strlen(name) - 1] == '\n'))
        name[bytes] = '\0';

    //lança nova caixa
    pid = fork();

    if (pid < 0)
    {
        sayThisAndExit("Erro no fork")
    }
    else if (pid == 0) // child
    { 

        execl(caixa, caixa, nome, (char *) NULL); // REVER
       
    }
    else{       // parent
         contadorCaixas++;
    }
}

```
