/*
 *  Soubor:      externs.h
 *  Řešení:      IOS - Projekt 2
 *  Autor:       Radek Duchon - xducho07, VUT FIT 1BIT 2017/18
 *  Přeloženo:   gcc 6.4.0
 *  Datum:       30.4.2018
 */

#ifndef _EXTERNS_H_
#define _EXTERNS_H_


extern sem_t *nastup; //muze se nastupovat
extern sem_t *opened; //je otevrena zastavka
extern sem_t *odjezd; //autobus odjel
extern sem_t *action; //bus counter protector
extern sem_t *dojezd; //autobusu dojel
extern sem_t *waiting;
extern sem_t *waitpls;

extern int *cekame;

extern FILE *out;


#endif
