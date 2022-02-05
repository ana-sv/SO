
## Named Pipes
### Ficha 5, ex 1 

cria named pipe:
```  
mkfifo pipezinho 
```

mostra o que está no pipe, espera até que haja algo e depois termina:
```
cat pipe
```


escrever no pipe:
```
echo "hey hey hey " > pipe
```
```
ls > pipe
```


>  Relação entre um named pipe e o sistema de ficheiros: 
        Verifica-se que o conteudo da diretoria se altera quando criado um novo named pipe. 
        Existe uma nova entrada correpondente a um ficheiro especial que é o named pipe que tem como letra indicadora p. 
        Isto pode ser visualizanda fazendo ls -l 


> A forma como a informação é enviada nos named pipes é em byte stream , ou seja , sem formato especifico.

>  Forma como funciona a deteção de novos dados diponiveis e do fim do ficheiro pelos named pipes:
        Os names pipes funconam como ficheiros... COMPLETAR
