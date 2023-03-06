#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "GridBoard.h"
#include "Array.h"
#include "Helper.h"
#include "Input.h"

#define GRID_SIZE 20 // Replace based on input doing malloc()

const double BOMBS_RATIO = 4.8484848484;

int getBombCountFromRatio(Board* oBoard) {
	return (int)ceil((oBoard->iWidth * oBoard->iHeight) / BOMBS_RATIO);
}

int main() {
	Board oBoard;
	oBoard.running = 1;

	// Initialize the Board Instance
	initGrid(&oBoard, GRID_SIZE, GRID_SIZE);
	displayGrid(&oBoard);

	// First Input
	printf("\nWhat is your move ? ('M' for the list of moves) > ");
	char input[5];
	scanf_s("%s", input, 5);

	int* move = validInput(input, oBoard.iWidth, oBoard.iHeight);
	while (move[0] == -1) {
		system("cls");
		displayGrid(&oBoard);
		clearInput();
		printf("\nEnter a valid input ! ('M' for the list of moves) > ");
		scanf_s("%s", input, 5);
		free(move);
		move = validInput(input, oBoard.iWidth, oBoard.iHeight);
	}
	system("cls");

	// Plant the bombs
	int startingX = move[0];
	int startingY = move[1];
	free(move);
	int bombCount = getBombCountFromRatio(&oBoard);
	plantBombs(&oBoard, bombCount, startingX, startingY);
	calculateSurroundingBombs(&oBoard);

	// Dig at the player first inputs
	digAt(&oBoard, startingX, startingY);

	// Gameloop
	while (oBoard.running) {

		displayGrid(&oBoard);

		// Input Management
		printf("\nWhat is your move ? ('M' for the list of moves) > ");
		char input[5];
		scanf_s("%s", input, 5);

		move = validInput(input, oBoard.iWidth, oBoard.iHeight);
		while (move[0] == -1) {
			system("cls");
			displayGrid(&oBoard);
			clearInput();
			printf("\nEnter a valid input ! ('M' for the list of moves) > ");
			scanf_s("%s", input, 5);
			free(move);
			move = validInput(input, oBoard.iWidth, oBoard.iHeight);
		}

		//system("cls");

		// Display the grid
		displayGrid(&oBoard);

		if (isTool(input)) {
		}
		else {
			if (isFlag(input)) {
				GridSlot* oSlot = getValue(&oBoard, move[0], move[1]);
				oSlot->bFlag = !oSlot->bFlag;
			}
			else {
				printf("\nDig at x: %d & y: %d", move[0], move[1]);
				digAt(&oBoard, move[0], move[1]);
			}
		}
		free(move);
	}

	free(oBoard.oGrid);

	return 0;
}