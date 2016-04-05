/*
 * Sudoku.cpp
 *
 */

#include "Sudoku.h"

/** Inicia um Sudoku vazio.
 */
Sudoku::Sudoku()
{
	this->initialize();
}

/**
 * Inicia um Sudoku com um conteúdo inicial.
 * Lança excepção IllegalArgumentException se os valores
 * estiverem fora da gama de 1 a 9 ou se existirem números repetidos
 * por linha, coluna ou bloc 3x3.
 *
 * @param nums matriz com os valores iniciais (0 significa por preencher)
 */
Sudoku::Sudoku(int nums[9][9]){
	this->initialize();

	for (int i = 0; i < 9; i++)	{
		for (int j = 0; j < 9; j++){
			if (nums[i][j] != 0){
				int n = nums[i][j];
				numbers[i][j] = n;
				lineHasNumber[i][n] = true;
				columnHasNumber[j][n] = true;
				block3x3HasNumber[i / 3][j / 3][n] = true;
				countFilled++;
			}
		}
	}
}

void Sudoku::initialize(){
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			for (int n = 0; n < 10; n++){
				numbers[i][j] = 0;
				lineHasNumber[i][n] = false;
				columnHasNumber[j][n] = false;
				block3x3HasNumber[i / 3][j / 3][n] = false;
			}
		}
	}
	this->countFilled = 0;
}

/**
 * Obtem o conteúdo actual (só para leitura!).
 */
int** Sudoku::getNumbers(){
	int** ret = new int*[9];

	for (int i = 0; i < 9; i++){
		ret[i] = new int[9];

		for (int a = 0; a < 9; a++)
			ret[i][a] = numbers[i][a];
	}
	return ret;
}

/**
 * Verifica se o Sudoku já está completamente resolvido
 */
bool Sudoku::isComplete(){
	return countFilled == 9 * 9;
}

/**
 * Resolve o Sudoku.
 * Retorna indicação de sucesso ou insucesso (sudoku impossível).
 */
bool Sudoku::solve(){

	int bestX=1,bestY=1;
	if(isComplete()){
		return true;
	}
	choose_best(bestX,bestY);
	for(int i=1; i<10; i++){
		if (!columnHasNumber[bestY][i])
			if (!lineHasNumber[bestX][i])
				if (!block3x3HasNumber[bestX/3][bestY/3][i]) {
					numbers[bestX][bestY]=i;
					columnHasNumber[bestY][i] = true;
					lineHasNumber[bestX][i] = true;
					block3x3HasNumber[bestX/3][bestY/3][i] = true;
					countFilled++;
					bool check = solve();
					if(check)
						return isComplete();
					else{
						numbers[bestX][bestY]=0;
						columnHasNumber[bestY][i] = false;
						lineHasNumber[bestX][i] = false;
						block3x3HasNumber[bestX/3][bestY/3][i] = false;
						countFilled--;

					}
				}
	}
	return isComplete();
}

void Sudoku::choose_best(int & bestX, int & bestY){
	int best_n = 10;
	for(int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			if (numbers[i][j] == 0) {
				int number = 9;
				for (int a = 1; a < 10; a++)
					if (columnHasNumber[j][a])
						number--;
					else if (lineHasNumber[i][a])
						number--;
					else if (block3x3HasNumber[i/3][j/3][a])
						number--;
				if (number < best_n) {
					best_n = number;
					bestX = i;
					bestY = j;
				}
			}
		}
	return;
}
/**
 * Imprime o Sudoku.
 */
void Sudoku::print(){
	for (int i = 0; i < 9; i++){
		for (int a = 0; a < 9; a++)
			cout << this->numbers[i][a] << " ";

		cout << endl;
	}
}
