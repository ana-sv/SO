// Sistemas Operativos 2021/2022
// PROGRAMACAO DE ALGORITMOS PARALELIZAVEIS COM THREADS 

// CALCULO DO VALOR DE PI COM O METODO MONTE CARLO 

/*

Este exemplo -> Utiliza várias threads para calcular o valor de PI

- Todas as threads são baseadas na mesma função ( é o mesmo algoritmo, apenas os dados variam )
- Usa-se a estratégia habitual : é passado um ponteiro para as threads de forma a que cada uma saiba o que deve fazer 


- A thread inicial (main) , lança as threads e depois aguarda um intervalo de tempo. 
- Findo esse tempo indica às threads que devem terminar.
        - o numero de threads é indicado em linha de comandos
        - o intervalo de tempo é indicado em linha de comandos
        - as threads são terminadas pela estrategia habitual com a " variavel continua "

- A funcao main aguarda que as threads tenham garantidamente terminado, e só entao é que vai verificar os totais de dardos que cada thread produziu 



*/



// falta passar para aqui o codigo 