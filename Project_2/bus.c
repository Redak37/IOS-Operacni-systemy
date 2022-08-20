/*
 *  Soubor:      bus.c
 *  Řešení:      IOS - Projekt 2
 *  Autor:       Radek Duchon - xducho07, VUT FIT 1BIT 2017/18
 *  Přeloženo:   gcc 6.4.0
 *  Datum:       30.4.2018
 */

#include <semaphore.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "bus.h"
#include "externs.h"


int bus(int r, int c, int abt, int *act)
{
    int odjeti = 0, inb;
    srand(time(NULL));

    sem_wait(action);
    fprintf(out, "%d\t: BUS\t\t: start\n", ++(*act));
    sem_post(action);
   
    while(odjeti < r)
    {
        sem_wait(opened); //zavrena zastavka

        sem_wait(action);
        fprintf(out, "%d\t: BUS\t\t: arrival\n", ++(*act));
        sem_post(action);

        if (*cekame != 0)
        {
            sem_wait(action);
            fprintf(out, "%d\t: BUS\t\t: start boarding: %d\n", ++(*act), *cekame);
            sem_post(action);
     
            sem_wait(waitpls);
            for (int i = 0; i < c && i < *cekame; ++i) sem_post(nastup);//nastupte kdo muzete
            
            for (int i = 0; i < *cekame && i < c; ++i) sem_wait(waiting);//muzu odjet?
            sem_post(waitpls);

            if (*cekame < 0) return 1;

            if (*cekame > c)
            {
                inb = c;
                odjeti += c;
                *cekame -= c;
            } else {
                inb = *cekame;
                odjeti += inb;
                *cekame -= inb;
            }

            for (int i = 0; i < inb; ++i) sem_post(odjezd);//odjezd lidi
    
            sem_wait(action);
            fprintf(out, "%d\t: BUS\t\t: end boarding: %d\n", ++(*act), *cekame);
            fprintf(out, "%d\t: BUS\t\t: depart\n", ++(*act));
            sem_post(action);
            sem_post(opened);

            usleep(rand()%abt*1000);
        
            for (int i = 0; i < inb; ++i) sem_post(dojezd);//konec cesty

            sem_wait(action);
            fprintf(out, "%d\t: BUS\t\t: end\n", ++(*act));
            sem_post(action);
        } else {
            sem_wait(action);
            fprintf(out, "%d\t: BUS\t\t: depart\n", ++(*act));
            sem_post(action);
            sem_post(opened);

            if (abt != 1) usleep(rand()%abt*1000);
            
            sem_wait(action);
            fprintf(out, "%d\t: BUS\t\t: end\n", ++(*act));
            sem_post(action);
        }
    }

    sem_wait(action);
    fprintf(out, "%d\t: BUS\t\t: finish\n", ++(*act));
    sem_post(action);

    return 0;
}
