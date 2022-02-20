## Exercicios sobre Comandos Linux 
#### Exames dos Anos 2020 - 2022


#### 1) Apresente no ecra o username e user id do utilizador que tem o segundo user id mais elevado no sistema ( exemplo do conteudo do ficheiro: maria 1006 ). A correta realização desta tarefa não deve depender da pasta atual em que se encontra na linha de comandos. 

lista nomes de utilizadores e user id sem os : , ordenar a 2 coluna revertida, 2 linhas a partir de cima e 1 a partir de baixo

``
cut -d: -f1,3 /etc/passwd | tr ":" " " | sort -n -k2 -r | head -2 | tail -1 
``


#### 2) Guarde na sua pasta pessoal um ficheiro com o nome "ficheiro.txt" cujo conteudo será com o nome e o tamanho ( apenas estes dois campos - um linha por cada ficheiro), dos cinco maiores ficheiros que se encontram na diretoria /etc. Se o ficheiro já existir, a informação é acrescentada ao que já lá estava. A correta realização desta tarefa não deve depender da pasta atual em que se encontra na linha de comandos. 

na pasta pessoal, na diretoria apresenta nome e tamanho, ordenado revertidadmente ( nao é preciso mais nada porque a primeira columa é já o tamanho e é por ai que queremos ordenar) , 5 linhas a contar de cima, tudo isto para o ficheiro.txt 

``
cd /home/ana | ......   | sort -rn | head -5 > "ficheiro.txt"     REVER
``

#### 3) Utilizando apenas uma linha de comandos, elimine todos os named pipes existentes na sua homedir ( directoria pessoal ). A resposta nao deve depender da diretoria em que se encontra atualmente.
``
cd /home/ana | find -type p -delete
``
#### 4) Utilizando apenas uma linha de comandos, coloque no ficheiro " resultado.txt" o nome de todos os ficheiros que exitem na pasta "/tmp" que tenham extenção ".txt" e pertencentes ao utilizador com o username(login) "antonio". A lista de ficheiros deve estar organizada por ordem crescente do tamanho dos ficheiros. 
``
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

