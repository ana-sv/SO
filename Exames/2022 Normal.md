# Exame 2021-2022 Normal - 22 Janeiro 2022
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

#### 4) 
