/*
 *  Soubor:      rider.c
 *  Řešení:      IOS - Projekt 2
 *  Autor:       Radek Duchon - xducho07, VUT FIT 1BIT 2017/18
 *  Přeloženo:   gcc 6.4.0
 *  Datum:       30.4.2018
 */

#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include "externs.h"
#include "rider.h"


int rider(int I, int *act)
{
    sem_wait(action);
    fprintf(out, "%d\t: RID %d \t: start\n", ++(*act), I);
    sem_post(action);

    sem_wait(opened);//muzu na zastavku?
    sem_post(opened);

    sem_wait(waitpls);
    sem_wait(action);
    fprintf(out, "%d\t: RID %d \t: enter: %d\n", ++(*act), I, ++(*cekame));//vchazim na zastavku
    sem_post(action);
    sem_post(waitpls);

    sem_wait(nastup);//muzu nastoupit?

    sem_wait(action);
    fprintf(out, "%d\t: RID %d \t: boarding\n", ++(*act), I);
    sem_post(action);

    sem_post(waiting);//nastoupeno, muzes jet
    
    sem_wait(dojezd);
    sem_wait(action);
    fprintf(out, "%d\t: RID %d \t: finish\n", ++(*act), I);
    sem_post(action);
    return 0;
}


int riders(int r, int art, int *act)
{
    srand(time(NULL));
    pid_t pid[r];
    
    for (int i = 0; i < r; ++i)
    {
        if (art != 1) usleep(rand()%art*1000);

        pid[i] = fork();

        if (pid[i] == -1)
        {
            fprintf(stderr, "Error: Nepodarilo se spustit proces RID %d.\n", i+1);
            for (int j = 0; j < i; ++j) waitpid(pid[j], NULL, 0);
            *cekame = -65536;
            return 1;
        } else if (pid[i] == 0) return rider(i+1, act);
    }

    for (int i = 0; i < r; ++i) waitpid(pid[i], NULL, 0);

    return 0;
}
