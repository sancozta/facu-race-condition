# Condição de Corrida

O objetivo deste projeto é abordar o problema da condição de corrida, na tentativa de propor uma solução. Na busca desta solução foi utilizado para controlar o acesso ao recurso o conceito de semáforo, de forma a utilizar as operações **down** e **up**. O projeto foi desenvolvido e testado em ambiente linux (Ubuntu e Fedora) utilizando o compilador gcc para compilar o programa que foi escrito em linguagem c, utilizando a biblioteca pthread no padrão POSIX estabelecido pela IEEE.

O recurso aqui é representando no papel da escrita em um arquivo .txt o programa cria 10 threads que represetam os escritores, essas threads executam a função **fwritew** individualmente que chama a operação **down** realizando um decremento na variavel **sem** que inicia em 1 e que representa o controle do semáforo. O primeiro escritor que executar a operação **down** entra na região crítica do recurso, como o semáforo vai para 0 outros escritores que executarem **down** não conseguiram entrar na região crítica e consequentemente não escreverão no arquivo. O escritor que entrar na região crítica realizará a escrita no arquivo e logo em seguida executará a operação **up** incrementando 1 a variável **sem** e indicando aos outros escritores que o recurso foi liberado e esta disponível.

Os resultados obtidos são a execução de todas as threads tentando utilizar o recurso, porém caso o recurso esteja sendo utilizado fato que será controlado pela variável **sem**, naturalmente a thread chegará ao fim de sua execução sem conseguir escrever no arquivo. Naturalmente algumas threads não escreveram no arquivo e outras sim. A execução pode se acomanhada pelo terminal onde é mostrado todas as fases do processamento, e pode ser verificado no arquivo file.txt na raiz do arquivo executado, os escritores que escreveram no arquivo.

## Pré - Requisitos

- Sistema operacional linux
- Compilador gcc

## Compilação e Execução

- Para compilar o código utilize a seguinte instrução em ambiente linux
    
    gcc projeto.c -pthread -o projeto.bin

- Após compilar basta executar utilizando
    
    ./projeto.bin
