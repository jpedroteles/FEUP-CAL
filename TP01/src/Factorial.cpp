/*
 * Factorial.c
 *
 *  Created on: Feb 23, 2016
 *      Author: Pedro
 */

#include "Defs.h"
#include "Factorial.h"

int factorialRecurs(int n){
	int temp;
	if(n<=1){
		return 1;
	}
	temp=n * factorialRecurs(n-1);
	return temp;
}


int factorialDinam(int n){
	int ret = 1;
	for(int i = 1; i <= n; i++)
		ret *= i;
	return ret;
}

int* factorialDinamArray(int n){
	int* valores = new int [n+1];
	valores[0]=1;
	for(int i = 1; i <= n; i++){
		valores[i] = i* valores[i-1];
	}
	return valores;
}

