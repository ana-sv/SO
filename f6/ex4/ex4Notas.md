# Sistemas Operativos 2021/2022
## Multibanco Remoto 

#### Servidor 
- Armazena as contas dos clientes e atende os pedidos destes 
- A logica deve estar do lado do servidor, sendo o cliente apenas um ponto de inserção de comandos e de apresentação de informação recebida do servidor 
- O servidor " apenas " guarda o saldo da conta do cliente que inicialmente é 0 
- o servidor só suporta no máximo 20 contas de clientes em simultaneo 
- Além de atender os clientes , o servidor permite
        <listar> listar todas as contas existentes no sistema
        <sair> do sistema sem ser necessário notificar aos clientes que fechou

#### Cliente
- Obter <saldo> da sua conta 
- <levantar><quantidade> em que o seu saldo tem que ter atualizado e pode ficar a negativo
- <depositar><quantidade> em que o seu saldo tem que ser atualizado
- <sair> do sistema , e elimina a conta deste no servidor




###### Usar:
      - names pipes, threads com mutex ( por causa so comando listar que pode entrar em conflito )
      - sigaction, pthread_kill e pthread_exit 

