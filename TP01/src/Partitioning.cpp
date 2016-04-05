/*
 * Partitioning.cpp
 *
 *  Created on: Mar 1, 2016
 *      Author: Pedro
 */

#include "Partitioning.h"

int s_recursive(int n,int k){
	if(k == 1 || k == n)
		return 1;
	else
		return s_recursive(n-1,k-1) + k*s_recursive(n-1,k);

}

int b_recursive(int n){
	int sum = 0;

	for(int k = 1; k <= n; k++)
		sum += s_recursive(n,k);

	return sum;
}

int s_dynamic(int n,int k){

	int * values = new int[k+1];

	if(n == 0 && k == 0)
		return 1;

	for(int i = 0; i <= k; i++)
		values[i] = i == 0 ? 1 : 0;

	int oldvalue;
	for(int i=1; i <= n; i++){
		for(int j=0;j<=k;j++){
			if(j==0|| j==1){
				values[j]=i;
				oldvalue=1;
			}
			else if(i == j)
				values[j] = 1;
			else {
				int temp = values[j];
				values[j] = oldvalue + values[j]*j;
				oldvalue = temp;
			}
		}
	}
	return values[k];
}

int b_dynamic(int n){


	//like s_dynamic with a few teaks
	int * values = new int[n+1];
	if(n == 0)
		return 1;

	for(int i = 0; i <= n; i++)
		values[i] = i == 0 ? 1 : 0;

	int oldvalue;

	for(int i=1; i <= n; i++){
		for(int j=0;j<=n;j++){
			if(j==0|| j==1){
				values[j]=j;
				oldvalue=1;
			}
			else if(i == j)
				values[j] = 1;
			else {
				int temp = values[j];
				values[j] = oldvalue + values[j]*j;
				oldvalue = temp;
			}
		}
	}

	//sums all values;
	int sum = 0;
	for(int i = 0; i <= n; i++)
		sum+=values[i];

	return sum;
}
