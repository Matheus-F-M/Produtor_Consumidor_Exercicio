# Produtor_Consumidor_Exercicio
Exercício sobre o problema Produtor Consumidor. CESAR School; 3º Período; Turma A; 2022.1; 05/2022

## Objetivo
Este código possui como objetivo simular uma resolução para o problema de sincronização: Produtor Consumidor, utilizando um buffer fixo e semáforos.

## Funcionamento
Este código recebe do usuário 4 números que determinam respectivamente: Quantidade de Produtoes; Quantidade de Consumidores; Limite do Valor Produzido e Tamanho do Buffer.

São declarados globalmente: O buffer, o tamanho do buffer, 3 semáforos, e 4 variáveis globais.

O "produto" gerado é um inteiro originado de uma função matemática: f(x) = 2 * x + 1 em que 0 <= X <= N, em que "N" é o limite delimitado pelo usuário. O valor de "x"
inicia como sendo 0 e é incrementado até atingir o valor de "N" e então voltando para o valor de 0.

Existem 2 funções para criar threads: A dos produtores e a dos consumidores. Essa funções recebem como parâmetros uma outra função que determina o comportamento da
thread como produtora ou consumidora bem como o identificador da thread. Através dos semáforos os consumidores são capazes de determinar se o buffer está ou não vazio
dado os valores dos semáforos, com o uso de um semáforo que funciona como uma trava mutex, é impedido que múltiplas threads acessem as variáveis globais e o buffer
simultâneamente.

Quando a "trava" é adquirida por um produtor este insere o elemento gerado no buffer e então solta a trava e modifica os outros 2 semáforos indicando quantos espaços
do buffer estão disponíveis e quantos estão vazios. O consumidor realiza o processo oposto, "consumindo" o valor presente no espaço do buffer que se encontra
atualmente, o substituindo por 0 e também modifica os outros 2 semáforos. Este processo continua indefinidamente até que o usuário decida pará-lo via comando de
terminal.

## Instalação
``` sh
git clone https://github.com/Matheus-F-M/Produtor_Consumidor_Exercicio.git
```
## Comandos do Makefile:
### Compilar
``` sh
make binary 
```

### Executar
``` sh
make run 
```

### Limpar
``` sh
make clean 
```

#### Observação:
O código funciona como o indicado, entretanto ao invés de imprimir o índice da thread, imprime o endereço de memória do respectivo índice.
