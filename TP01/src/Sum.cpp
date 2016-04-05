/*
 * Sum.cpp
 *
 *  Created on: Feb 23, 2016
 *      Author: Pedro
 */

#include "Defs.h"
#include "Sum.h"

string calcSum(int* sequence, int size){
	int* sum = new int[size];
	int* index = new int[size];

	//the starting index
	for(int i = 0; i < size; i++){
		int val = 0;

		//the size
		for(int j = i; j < size; j++){
			val += sequence[j];
			if(i == 0){
				sum[j] = val;
				index[j] = i;
			}
			else if(val < sum[j-i]){
				sum[j-i] = val;
				index[j-i] = i;
			}
		}
	}

	//compute da info
	stringstream result;

	for(int i=0; i < size;i++)
		result << sum[i] << "," << index[i] << ";";

	return result.str();

}


