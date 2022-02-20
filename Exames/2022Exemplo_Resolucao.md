# Exame Exemplo 2022
> este exame dado como exemplo em 2022 foi o exame da época normal do ano 2021

#### 1) Considere a arquitetura do sistema micro-kernel ( é a que o Windows utiliza). Indique se esta arquitetura é muito estável ou pouco estável e explique a razão se ser dessa estabilidade (ou falta dela).

A arquitetura de sistema micro-kernel é muito estável devido à quantidade reduzida de código em execução em modo núcleo. Os serviços do sistema correm como programas semelhantes aos do utilizador e a requisição de serviços é feita através de mensagens entre processos. As tarefas do nucleo resumen-se a escalonamento , despacho e gestao de comunicação entre processos. 


#### 2) O codigo abaixo representa um programa que procura e mostra números primos. A thread procura identifica os números e a thread mostra imprime esses números.
![image](https://user-images.githubusercontent.com/44445562/154860125-d81778b4-6dfb-4aa2-939d-dd736f2bb389.png)

#### 2.a) Indentifique eventuais partes menos boas no código tendo em atenção que a matéria envolvida é de SO e não de IP. 

#### 2.b) Resolva essas partes menos boas utilizando funções genéricas tal como nas aulas teóricas, ou usando as folhas de consulta autorizadas. Tem que manter a procura e a apresnetação em threads diferente. 

#### 3) Considere uma máquina com 10Kb de RAM de memória paginada ( paginas de 2 Kb ) em que o sistema simula a existencia de mais memória à custa de um page file. O algoritmo de substituição de páginas é o NRU. A tabela descreve a totalidade da memória no instante t1 2 e 4. No instante t2 surge a necessidade de encaixar uma nova página em memória. Descreva o que acontece sa sequência desse pedido. 
![image](https://user-images.githubusercontent.com/44445562/154860156-ffee38ed-fce3-4c3c-9b97-2a6a0b4ab57d.png)

A página de indice 1 vai sair da tabela e passa para a memória secundária, dando assim lugar á nova página. A página de indice 1 é a escolhida pois após o instante t1 é a única com R=0 e M=0. 


#### 4) Utilizando apenas uma linha de comandos, elimine todos os named pipes existentes na sua homedir ( directoria pessoal ). A resposta nao deve depender da diretoria em que se encontra atualmente.
``
cd /home/ana | -type p delete
``


#### 5) Utilizando apenas uma linha de comandos, coloque no ficheiro " resultado.txt" o nome de todos os ficheiros que exitem na pasta "/tmp" que tenham extenção ".txt" e pertencentes ao utilizador com o username(login) "antonio". A lista de ficheiros deve estar organizada por ordem crescente do tamanho dos ficheiros. 
``
ls -laS $( find /tmp -user antonio | grep ".txt$" ) > resultado.txt
``


#### 6)
``
code
``


#### 7)
``
code
``


