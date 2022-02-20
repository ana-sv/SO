# Exame Exemplo 2021-2022


#### 1) Considere a arquitetura do sistema micro-kernel ( é a que o Windows utiliza). Indique se esta arquitetura é muito estável ou pouco estável e explique a razão se ser dessa estabilidade (ou falta dela).

A arquitetura de sistema micro-kernel é muito estável devido à quantidade reduzida de código em execução em modo núcleo. Os serviços do sistema correm como programas semelhantes aos do utilizador e a requisição de serviços é feita através de mensagens entre processos. As tarefas do nucleo resumen-se a escalonamento , despacho e gestao de comunicação entre processos. 

#### 4) Utilizando apenas uma linha de comandos, elimine todos os named pipes existentes na sua homedir ( directoria pessoal ). A resposta nao deve depender da diretoria em que se encontra atualmente.
``
cd /home/ana | -type p delete
``
#### 5) Utilizando apenas uma linha de comandos, coloque no ficheiro " resultado.txt" o nome de todos os ficheiros que exitem na pasta "/tmp" que tenham extenção ".txt" e pertencentes ao utilizador com o username(login) "antonio". A lista de ficheiros deve estar organizada por ordem crescente do tamanho dos ficheiros. 
``
``
