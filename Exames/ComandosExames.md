## Exercicios sobre Comandos Linux 
#### Exames dos Anos 2020 - 2022


#### 1) Apresente no ecra o username e user id do utilizador que tem o segundo user id mais elevado no sistema ( exemplo do conteudo do ficheiro: maria 1006 ). A correta realização desta tarefa não deve depender da pasta atual em que se encontra na linha de comandos. 

lista nomes de utilizadores e user id sem os : , ordenar a 2 coluna revertida, 2 linhas a partir de cima e 1 a partir de baixo

``
cut -d: -f1,3 /etc/passwd | tr ":" " " | sort -n -k2 -r | head -2 | tail -1 
``


#### 2) Guarde na sua pasta pessoal um ficheiro com o nome "ficheiro.txt" cujo conteudo será com o nome e o tamanho ( apenas estes dois campos - um linha por cada ficheiro), dos cinco maiores ficheiros que se encontram na diretoria /etc. Se o ficheiro já existir, a informação é acrescentada ao que já lá estava. A correta realização desta tarefa não deve depender da pasta atual em que se encontra na linha de comandos. 

ordena ls por tamanho do ficheiro | esquece os espaços a mais| fica com a 4 e 5 colunas delimitadas por " " | 5 linhas de cima ) poe no ficheiro que está na pasta pessoal
``
ls -lS /etc | tr -s " "| cut -d " " -f4,5 | head -5  >  /home/ana/ficheiro.txt
``

#### 3) Utilizando apenas uma linha de comandos, elimine todos os named pipes existentes na sua homedir ( directoria pessoal ). A resposta nao deve depender da diretoria em que se encontra atualmente.
``
cd /home/ana | find -type p -delete
``
#### 4) Utilizando apenas uma linha de comandos, coloque no ficheiro " resultado.txt" o nome de todos os ficheiros que exitem na pasta "/tmp" que tenham extenção ".txt" e pertencentes ao utilizador com o username(login) "antonio". A lista de ficheiros deve estar organizada por ordem crescente do tamanho dos ficheiros. 
``
ls -lS $( find /tmp -user antonio | grep ".txt$" ) > resultado.txt
``

#### 5) Utilizando a linha de comandos, coloque no ficheiro "nomes.txt" o login (username) dos utilizadores do sistema que utilizam a shell bash e que tem o nome próprio começado por uma letra minuscula. Esta informação deve estar ondenada por ondem crescente do grupo primário do utilizador. 
escolhe a 1 e 5 colunas | troca o : por espaço | organiza pelo nome crescente 
``
cut -d: -f1,5 /etc/passwd | tr ":" " " | sort  ----> falta a cena da letra minuscula
``


## sort
ordena numeros(-n) da segunda coluna(-k2) na ordem reversa(-r)
``
sort -n -k2 -r
``

## ls
ls ordenado pelo tamanho do ficheiro , maiores primeiro
``
ls -S
``


## cut 
###### corta coluna 2,5,7 do ficheiro txt
`` 
cut -c 2,5,7 ficheiro.txt
``

###### apresenta o corte delimitado por espaço do 1º campo do ficheiro txt
``
 cut -d " " -f 1 ficheiro.txt
``

###### apresenta o corte delimitado por espaço do 1º a 4ª campos do ficheiro txt
``
 cut -d " " -f 1-4 ficheiro.txt
``

###### apresenta do ficheiro.txt o corte delimitado por " " o primeiro campo ordenado de forma reversa
``
cat state.txt | cut -d ' ' -f 1 | sort -r
``

###### lista nomes de utilizadores sem ":"  OU SEJA, apresenta o corte delimitado por ":" do primeiro campo do ficheiro /etc/passwd 

``
cut -d: -f1 /etc/passwd   
``
ou
``
cut -d ":" -f1 /etc/passwd   
``


###### lista nomes de utilizadores e user id sem os : 
``
cut -d: -f1,3 /etc/passwd | tr ":" " " 
``

