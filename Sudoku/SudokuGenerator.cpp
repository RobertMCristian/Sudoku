#include "SudokuGenerator.h"
#include <algorithm>
#include <iostream>

// constructorul clasei sudoku_generator
SudokuGenerator::SudokuGenerator(int difficultyLevel){	
	m_board.resize(9, std::vector<int>(9));
	solveSudoku(0, 0, 0);
	m_solvedBoard = m_board;
	m_missingValues = 0;
	m_emptySquares = (35 + difficultyLevel * 10);
	auto vec = generateRandomPermutation(81);
	removeNumbersFromBoard(vec, 0);


	std::cout << "Missing values: " << m_missingValues << '\n';
	for(int i = 0; i < 9; ++i){
		for(int j = 0; j < 9; ++j) std::cout << m_solvedBoard[i][j] << ' ';
		std::cout << '\n';
	}
}
// functia care returneaza tabla de sudoku
std::vector<std::vector<int>> SudokuGenerator::getBoard(){
	return m_board;
}
// functia care verifica daca jocul este finalizat
bool SudokuGenerator::isGameFinished(){
	return std::equal(m_board.begin(), m_board.end(), m_solvedBoard.begin(), m_solvedBoard.end());
}
// functia care seteaza valoarea la o anumita pozitie
void SudokuGenerator::setValueAt(int row, int col, int value){
	m_board[row][col] = value;
}
// functia care rezolva complet jocul
void SudokuGenerator::solve(){
	m_board = m_solvedBoard;
}
// functia care rezolva o singura pozitie din joc
void SudokuGenerator::solveAt(int row, int col){
	if(row <= 0 || row >= 9 || col <= 0 || col >= 9) return;
	int valueAt = m_solvedBoard[row][col];
	m_board[row][col] = valueAt;
}
// functia care elimina numerele din tabla de joc
bool SudokuGenerator::removeNumbersFromBoard(const std::vector<int>& removeOrder, int index){
	if(m_missingValues >= m_emptySquares) return true;
	for(int i = index; i < removeOrder.size(); ++i){
		int row = (removeOrder[i] - 1) / 9, col = (removeOrder[i] - 1) % 9;
		int valueSaved = m_board[row][col];
		if(valueSaved == 0) continue;
		m_board[row][col] = 0;
		auto copyBoard = m_board;
		if(solveSudoku(0, 0, 0) == 1){
			++m_missingValues;
			return removeNumbersFromBoard(removeOrder, index + 1);
		}
		m_board = copyBoard;
		m_board[row][col] = valueSaved;
	}
	return false;
}
// functia care rezolva tabla de sudoku
int SudokuGenerator::solveSudoku(int row, int col, int solutions){
	if(row == 8 && col == 9){
		return solutions + 1;
	}

	if(col == 9){
		col = 0;
		++row;
	}

	if(m_board[row][col] != 0) return solveSudoku(row, col + 1, solutions);

	std::vector<int> possibleValues = generateRandomPermutation(9);
	for(auto& value: possibleValues){
		if(isSafe(value, row, col)){
			m_board[row][col] = value;
			solutions = solveSudoku(row, col + 1, solutions);
		}
		if(solutions > 1) return solutions;
	}
	m_board[row][col] = 0;
	return solutions;
}
// functia care verifica daca o valoare poate fi plasata intr-o anumita pozitie
bool SudokuGenerator::isSafe(int value, int row, int col){
	for(int i = 0; i < 9; ++i){
		if(m_board[row][i] == value) return false;
	}

	for(int i = 0; i < 9; ++i){
		if(m_board[i][col] == value) return false;
	}

	int gridX = col - col % 3, gridY = row - row % 3;
	for(int i = 0; i < 3; ++i){
		for(int j = 0; j < 3; ++j){
			if(m_board[gridY + i][gridX + j] == value) return false;
		}
	}
	return true;
}
// functia care genereaza o permutare random a valorilor
std::vector<int> SudokuGenerator::generateRandomPermutation(int vectorSize){
	std::vector<int> values(vectorSize);
	int n = 0;
	std::generate(values.begin(), values.end(), [&n](){ return ++n; });
	std::shuffle(values.begin(), values.end(), m_rd);
	return values;
}
