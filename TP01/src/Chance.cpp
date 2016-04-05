/*
 * Chance.cpp
 *
 *  Created on: Feb 23, 2016
 *      Author: Pedro
 */

#include "Change.h"
#include "Defs.h"

string calcChange(int n){
	stringstream change;

	int* changeDone= new int[n+1];
	int* lastCoin = new int[n+1];
	int coinValues[3] = {5, 2, 1};

	for(int i=0; i <=n; i++){
		changeDone[i]=0;
		lastCoin[i]=0;
	}

	for(int i=0; i<3; i++){
		int coinValue=coinValues[i];
		if(coinValue<=n){
			for(int j= coinValue; j<=n;j++){
				//check saved values
				int remainder= j-coinValue;
				if(changeDone[j] + coinValue <= j && (coinValue+ changeDone[remainder]) <=j){
					changeDone[j] =coinValue +changeDone[remainder];
					lastCoin[j] =i;
				}
			}
		}
	}

	//compute string
	for(int i=1; i<=n; i++){
		bool comma=false;
		for( int j=i; j>0; j -= coinValues[lastCoin[j]]){
			if(comma)
			change<<",";

			change << coinValues[lastCoin[j]];
			comma=true;
		}
		change <<";";
		comma=false;
	}
	return change.str();
}
