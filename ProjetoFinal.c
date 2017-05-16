#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_ESCRITOR 10
int sem = 1;

struct args {
    FILE *f;
    int i;
};

int down()
{
    sem = sem - 1;
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
    if (s == 0)
    {
        fprintf(date->f, "Escritor %d\n", date->i);
        printf("Escritor %d\n", date->i);
    }
    up();
}

int main()
{
    char path[] = "file.txt";
    FILE *file;
    struct args largs[10];

    file = fopen(path, "w");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo!");
    }
    else
    {
        pthread_t thr_escritores[N_ESCRITOR];

        for (int i = 0; i < N_ESCRITOR; i++)
        {
            largs[i].f = file;
            largs[i].i = i;
            pthread_create(&thr_escritores[i], NULL, fwritew, (void *)&largs[i]);
        }

        for (int i = 0; i < N_ESCRITOR; i++)
        {
            pthread_join(thr_escritores[i], NULL);
        }

        fclose(file);
        
        return 0;
    }
    
}