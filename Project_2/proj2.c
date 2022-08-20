/*
 *  Soubor:      proj2.c
 *  Řešení:      IOS - Projekt 2
 *  Autor:       Radek Duchon - xducho07, VUT FIT 1BIT 2017/18
 *  Přeloženo:   gcc 6.4.0
 *  Datum:       30.4.2018
 */

#define SKEY 31415
#define WAITKEY 31416

#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "bus.h"
#include "proj2.h"
#include "rider.h"
#include "semaphores.h"


sem_t *nastup; //mohu nastupovat?
sem_t *opened; //je otevrena zastavka?
sem_t *odjezd; //odjezd!
sem_t *action; //pro pocitadlo akci
sem_t *dojezd; //autobus dojel
sem_t *waiting; //cekajici
sem_t *waitpls; //opravdu nevchazejte na tu zastavku!

int *cekame; //pocet cestujicich na zastavce

FILE *out;


int crtshmem(int key)
{
    int id = shmget(key, sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);

    if (id < 0)
    {
        fprintf(stderr, "Error: Ńepodarilo se vytvorit sdilenou pamet\n");
        return -1;
    }

    return id;
}

int endshmem(int id)
{
    int ret = shmctl(id, IPC_RMID, NULL);
    
    if(ret < 0)
    {
        fprintf(stderr, "Error: Nepodarilo se ukoncit sdilenou pamet\n");
        return 1;
    }

    return 0;
}

int args_load(int *args, char *argv[])
{
    char *endptr;
    
    args[0] = strtol(argv[1], &endptr, 10);
    if (args[0] <= 0 || *endptr != '\0')
    {
        fprintf(stderr, "Error: Zadan neplatny pocet procesu\n");
        return 1;
    }
    
    args[1] = strtol(argv[2], &endptr, 10);
    if (args[1] <= 0 || *endptr != '\0')
    {
        fprintf(stderr, "Error: Zadana neplatna kapacita autobusu\n");
        return 1;
    }
    
    args[2] = strtol(argv[3], &endptr, 10);
    if (args[2] < 0 || args[2] > 1000 || *endptr != '\0')
    {
        fprintf(stderr, "Error: Zadana neplatna hodnota argumentu \"ART\"\n");
        return 1;
    }
    
    args[3] = strtol(argv[4], &endptr, 10);
    if (args[3] < 0 || args[3] > 1000 || *endptr != '\0')
    {
        fprintf(stderr, "Error: Zadana neplatna hodnota argumentu \"ABT\"\n");
        return 1;
    }

    return 0;
}


int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        fprintf(stderr, "Error: Zadan neplatny pocet argumentu\n");
        return 1;
    }

    int args[4]; //r, c, art, abt;

    if (args_load(args, argv)) return 1;

    out = fopen("proj2.out","w");

    if (!out)
    {
        fprintf(stderr, "Error: Nepodarilo se otevrit soubor 'proj2.out' pro zapis.\n");
        return 1;
    }
    setbuf(out, NULL);

    int segment_id = crtshmem(SKEY);
    if (segment_id == -1)
    {
        fprintf(stderr, "Error: Nepodarilo se vytvorit sdilenou pamet pro pocitani akci.\n");
        return 1;
    }

    int zastavka_id = crtshmem(WAITKEY);
    if (zastavka_id == -1)
    {
        fprintf(stderr, "Error: Nepodarilo se vytvorit sdilenou pamet pro pocet cekajicich rideru.\n");
        endshmem(segment_id);
        return 1;
    }

    cekame = (int *) shmat(zastavka_id, NULL, 0);

    semaph_init();

    int *act = (int *) shmat(segment_id, NULL, 0);
    
    pid_t pid_rider = fork();

    if (pid_rider == -1)
    {
        fprintf(stderr, "Error: Nepodarilo se spustit pomocny proces.\n");
        return 1;
    } else if (pid_rider == 0) return riders(args[0], args[2]+1, act); //r, art+1, act

    pid_t pid_bus = fork();
    if (pid_bus == -1)
    {
        fprintf(stderr, "Error: Nepodarilo se spustit proces BUS.\n");
        return 1;
    } else if (pid_bus == 0) return bus(args[0], args[1], args[3]+1, act); //r, c, abt+1, act

    waitpid(pid_rider, NULL, 0);
    waitpid(pid_bus, NULL, 0);

    fclose(out);
    int ctrl = *cekame;

    semaph_rm();
    shmdt(act);
    shmdt(cekame);

    if (endshmem(zastavka_id) || endshmem(segment_id)) return 1;

    return (ctrl < 0);
}
