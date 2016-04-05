/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
using namespace std;



Labirinth::Labirinth(int values[10][10]){
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			labirinth[i][j]=values[i][j];
}


void Labirinth::initializeVisited(int x, int y){
	for (int i = 0; i < 10; i++)
		for (int a = 0; a < 10; a++)
			visited[i][a] = false;
	visited[y][x] = true;
}




void  Labirinth::printLabirinth(){
	for (int i = 0; i < 10; i++){
		for (int a = 0; a < 10; a++)
			cout << labirinth[i][a] << " ";

		cout << endl;
	}
}

bool Labirinth::findGoal(int x, int y)
{
	initializeVisited(x, y);
	foundTheSolution = false;
	findGoal_rec(x, y);
	return foundTheSolution;
}

bool Labirinth::findGoal_rec(int x, int y) {
	if (labirinth[x][y] == EXIT) {
		foundTheSolution = true;
		return foundTheSolution;
	}
	visited[x][y] = true;
	if (labirinth[x-1][y] != 0 && visited[x-1][y] == false)
		if (findGoal_rec(x-1,y) == EXIT)
			return foundTheSolution;
	if (labirinth[x+1][y] != 0 && visited[x+1][y] == false)
		if (findGoal_rec(x+1,y) == EXIT)
			return foundTheSolution;
	if (labirinth[x][y-1] != 0 && visited[x][y-1] == false)
		if (findGoal_rec(x,y-1) == EXIT)
			return foundTheSolution;
	if (labirinth[x][y+1] != 0 && visited[x][y+1] == false)
		if (findGoal_rec(x,y+1) == EXIT)
			return foundTheSolution;
	return foundTheSolution;
}
