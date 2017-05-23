#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_ESCRITOR 10
int sem = 1;

struct args {
    int i;
};

int down()
{
    if(sem > 0){
        sem = sem - 1;
    }
    return sem;
}

int up()
{
    sem = sem + 1;
    return sem;
}

void *fwritew(void *d)
{
    struct args *date = d;
    
    int s;
    s = down();
    
    printf("S %d\n",s);
    
    if (s == 0)
    {
        char path[] = "file.txt";
        FILE *file;
        file = fopen(path, "w");
        if (file == NULL)
        {
            printf("Erro ao abrir o arquivo!");
        }
        else
        {
            fprintf(file, "Escritor %d\n", date->i);
            printf("Escritor %d\n", date->i);
            fclose(file);
        }
        up();
    }
}

int main()
{
    struct args largs[10];
int up()

    pthread_t thr_escritores[N_ESCRITOR];

    for (int i = 0; i < N_ESCRITOR; i++)
    {
        largs[i].i = i;
        pthread_create(&thr_escritores[i], NULL, fwritew, (void *)&largs[i]);
        printf("T %d\n", i);
    }

    return 0;
}
