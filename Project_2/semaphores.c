/*
 *  Soubor:      semaphores.c
 *  Řešení:      IOS - Projekt 2
 *  Autor:       Radek Duchon - xducho07, VUT FIT 1BIT 2017/18
 *  Přeloženo:   gcc 6.4.0
 *  Datum:       30.4.2018
 */

#include <semaphore.h>
#include <fcntl.h>
#include <stdio.h>
#include "externs.h"
#include "semaphores.h"

#ifndef S_IWUSR
    #define S_IWUSR 0400
#endif

#ifndef S_IRUSR
    #define S_IRUSR 0200
#endif


void semaph_init()
{
    semaph_rm();
    nastup = sem_open("nastup-xducho07", O_CREAT, S_IWUSR | S_IRUSR, 0);
    opened = sem_open("opened-xducho07", O_CREAT, S_IWUSR | S_IRUSR, 1);
    odjezd = sem_open("odjezd-xducho07", O_CREAT, S_IWUSR | S_IRUSR, 0);
    action = sem_open("action-xducho07", O_CREAT, S_IWUSR | S_IRUSR, 1);
    dojezd = sem_open("dojezd-xducho07", O_CREAT, S_IWUSR | S_IRUSR, 0);
    waiting = sem_open("waiting-xducho07", O_CREAT, S_IWUSR | S_IRUSR, 0);
    waitpls = sem_open("waitpls-xducho07", O_CREAT, S_IWUSR | S_IRUSR, 1);
}


void semaph_rm()
{
    sem_close(nastup);
    sem_close(opened);
    sem_close(odjezd);
    sem_close(action);
    sem_close(dojezd);
    sem_close(waiting);
    sem_close(waitpls);
    sem_unlink("nastup-xducho07");
    sem_unlink("opened-xducho07");
    sem_unlink("odjezd-xducho07");
    sem_unlink("action-xducho07");
    sem_unlink("dojezd-xducho07");
    sem_unlink("waiting-xducho07");
    sem_unlink("waitpls-xducho07");
}
