
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

/*
 * Random.cc
 *
 *  Created on: 8 Sep 2020
 *      Author: Elia
 */

/**
 * Genera un numero casuale a partire da t, con valore massimo n-1
 * t serve per avere risultati diversi se chiamiamo PaoloFox piu' volte lo stesso secondo
 */
int PaoloFox(int n,int t)
{
	srand(time(0)+t);
	return (rand()%n);
}

