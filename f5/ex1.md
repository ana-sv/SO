
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


>  relação entre um named pipe e o sistema de ficheiros: verifica-se que o conteudo da disretoria se altera. Exite uma nova entrada correpondente a um ficheiro especial que é o named pipe. Este tem a letra indicadora p que pode ser visualizanda fazendo ls -l 

> A forma como a informação é inviada nos named pipes é sem formato especifico (byte stream); 

>  Forma como funciona a deteção de novos dados diponiveis e deo fim do ficheiro pelos named pipes:     COMPLETAR