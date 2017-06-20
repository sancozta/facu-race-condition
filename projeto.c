#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//QUANTIDADE DE ESCRITORES
#define N_ESCRITOR 10

//VARIÁVEL PARA CONTROLE DO SEMÁFORO
int sem = 1;

//ESTRUTURA PARA REGISTRO DO NUMERO DO ESCRITOR
struct args
{
    int i;
};

//OPERAÇÃO DOWN
int down()
{
    int r = sem;
    if (sem == 1)
    {
        sem = sem - 1;
    }
    return r;
}

//OPERAÇÃO UP
int up()
{
    sem = sem + 1;
    return sem;
}

//FUNÇÃO EXECUTANDA PELAS THREADS
void *fwritew(void *d)
{
    struct args *date = d;

    printf("Escritor %d executando.\n", date->i);

    //DOWN PARA VERIFICAR DISPONIBILIDADE DO RECURSO
    int s;
    s = down();

    //CASO O SEMÁFORO ESTEJA LIBERADO
    if (s > 0)
    {
        printf("Semáforo liberado para o escritor %d.\n", date->i);
        char path[] = "file.txt";
        FILE *file;
        file = fopen(path, "a+");
        if (file == NULL)
        {
            printf("Erro ao abrir o arquivo para o escritor %d.\n", date->i);
        }
        else
        {
            //CASO TUDO OCORRA BEM A THREADS ESCREVE NO ARQUIVO
            fprintf(file, "Escritor %d\n", date->i);
            printf("Escritor %d escreveu no arquivo.\n", date->i);
        }
        fclose(file);

        //LIBERANDO RECURSO UTILIZADO
        up();
    }
    //CASO O SEMÁFORO ESTEJA FECHADO
    else
    {
        printf("Semáforo fechado para o escritor %d.\n", date->i);
        printf("Escritor %d não conseguiu escrever no arquivo.\n", date->i);
    }
}

//MÉTODO MAIN
int main()
{
    struct args largs[10];

    pthread_t thr_escritores[N_ESCRITOR];

    //CRIANDO E EXECUTANDO AS THREADS
    for (int i = 0; i < N_ESCRITOR; i++)
    {
        largs[i].i = i;
        pthread_create(&thr_escritores[i], NULL, fwritew, (void *)&largs[i]);
        printf("Escritor %d foi criado.\n", i);
    }

    //UTILIZANDO PTHREAD JOIN PARA GARANTIR QUE O PROGRAMA SÓ TERMINE APÓS EXECUÇÃO DE TODAS AS THREADS
    for (int i = 0; i < N_ESCRITOR; i++)
    {
        pthread_join(thr_escritores[i], NULL);
    }

    return 0;
}
