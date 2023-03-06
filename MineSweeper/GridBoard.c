#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "GridBoard.h"
#include "Helper.h"
#include "Array.h"

// Define ANSI Color Codes
#define RED_ANSI_CODE "\033[0;31m"
#define GREEN_ANSI_CODE "\033[0;32m"
#define YELLOW_ANSI_CODE "\033[0;33m"
#define BLUE_ANSI_CODE "\033[0;34m"
#define PURPLE_ANSI_CODE "\033[0;35m"
#define CYAN_ANSI_CODE "\033[0;36m"
#define WHITE_ANSI_CODE "\033[0;37m"

void initGrid(Board* oBoard, int iWidth, int iHeight) {

	// Allocate memory for oBoard
	oBoard->iWidth = iWidth;
	oBoard->iHeight = iHeight;

	oBoard->oGrid = (GridSlot*)malloc(sizeof(GridSlot) * (oBoard->iWidth * oBoard->iHeight));

	if (oBoard->oGrid) { // If there is enough memore space

		for (int i = 0; i < oBoard->iWidth; i++) {
			for (int j = 0; j < oBoard->iHeight; j++) {
				int iPos = getArrayPosition(i, j, oBoard->iWidth);
				GridSlot* oSlot = &oBoard->oGrid[iPos];
				oSlot->x = i;
				oSlot->y = j;
				oSlot->bBomb = 0;
				oSlot->bRevealed = 0;
				oSlot->bFlag = 0;
				oSlot->iBombs = 0;
			}
		}
	}
}

GridSlot* getValue(Board* oBoard, int x, int y) {
	int iPos = getArrayPosition(x, y, oBoard->iWidth);
	return &oBoard->oGrid[iPos];
}

void arroundCases(Board* oBoard, Array* availablePositions, int x, int y) {
	for (int i = x - 1; i < x + 2; i++) {
		for (int j = y - 1; j < y + 2; j++) {
			if (isInBorder(oBoard, i, j)) {
				remove(availablePositions, getArrayPosition(i, j, oBoard->iWidth));
			}
		}
	}
}

void plantBombs(Board* oBoard, int iQuantity, int startingX, int startingY) {
	srand(time(NULL));

	Array availablePositions;
	initArray(&availablePositions, oBoard->iWidth * oBoard->iHeight);

	for (int i = 0; i < oBoard->iWidth; i++) {
		for (int j = 0; j < oBoard->iHeight; j++) {
			availablePositions.content[i * oBoard->iWidth + j] = getArrayPosition(i, j, oBoard->iWidth);
		}
	}

	arroundCases(oBoard, &availablePositions, startingX, startingY);

	for (int i = 0; i < iQuantity; i++) {
		int iRandPos = rand() % availablePositions.size;
		int coords[2];
		getTwoDimensionalPosition(oBoard, availablePositions.content[iRandPos], &coords);
		GridSlot* oSlot = getValue(oBoard, coords[0], coords[1]);
		oSlot->bBomb = 1;
		removeAt(&availablePositions, iRandPos);
	}

	cleanArray(&availablePositions);
}

void calculateSurroundingBombs(Board* oBoard) {
	for (int i = 0; i < oBoard->iWidth; i++) {
		for (int j = 0; j < oBoard->iHeight; j++) {
			GridSlot* oSlot = getValue(oBoard, i, j);
			if (!oSlot->bBomb) {
				for (int a = i - 1; a < i + 2; a++) {
					for (int b = j - 1; b < j + 2; b++) {
						GridSlot oSurroundingSlot = *getValue(oBoard, a, b);
						if (isInBorder(oBoard, a, b) && oSurroundingSlot.bBomb) {
							oSlot->iBombs++;
						}
					}
				}
			}
		}
	}
}

void digAt(Board* oBoard, int x, int y) {
	GridSlot* oSlot = getValue(oBoard, x, y);
	if (oSlot->bFlag) {
		printf("YOU CAN'T DIG WHERE THERE IS A FLAG UWUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU");
		return;
	}
	if (oSlot->bBomb) {
		loose(oBoard);
	}
	else if (oSlot->iBombs == 0) {
		recursiveReveal(oBoard, oSlot);
	}
	else {
		oSlot->bRevealed = 1;
	}
}

void recursiveReveal(Board* oBoard, GridSlot* oSlot) {
	if (oSlot->bRevealed) return;
	oSlot->bRevealed = 1;
	if (oSlot->iBombs > 0) {
		return;
	}
	else {
		for (int a = oSlot->x - 1; a < oSlot->x + 2; a++) {
			for (int b = oSlot->y - 1; b < oSlot->y + 2; b++) {
				if (isInBorder(oBoard, a, b)) {
					GridSlot* oToSpread = getValue(oBoard, a, b);
					recursiveReveal(oBoard, oToSpread);
				}
			}
		}
	}
}

void setTerminalColor(const char sColor[10]) {
	printf("%s", sColor);
}

void printBombsCount(GridSlot* oSlot, char sColor[10]) {
	setTerminalColor(sColor);
	printf(" %d ", oSlot->iBombs);
}

void displayGrid(Board* oBoard) {
	printf("\n");
	Repeat(' ', 4);
	Repeat('|', 1);
	Repeat(' ', 1);
	int iAsciiBase = 65;
	for (int k = 0; k < oBoard->iWidth; k++) {
		printf("%c  ", iAsciiBase + k);
	}
	printf("\n");
	Repeat('-', 4);
	Repeat('+', 1);
	Repeat('-', oBoard->iWidth * 3 - 1);
	printf("\n");

	for (int i = 0; i < oBoard->iWidth; i++) {
		printf(i + 1 > 9 ? " %d |" : " %d  |", i + 1);

		for (int j = 0; j < oBoard->iHeight; j++) {
			GridSlot* oSlot = getValue(oBoard, i, j);
			if (oSlot->bRevealed) {
				if (oSlot->bBomb) {
					printf("%s %c ", WHITE_ANSI_CODE, '*');
				}
				else if (oSlot->iBombs > 0) {
					char* colorCode;

					switch (oSlot->iBombs) {
					case 1:
						colorCode = BLUE_ANSI_CODE;
						break;
					case 2:
						colorCode = GREEN_ANSI_CODE;
						break;
					case 3:
						colorCode = RED_ANSI_CODE;
						break;
					case 4:
						colorCode = YELLOW_ANSI_CODE;
						break;
					case 5:
						colorCode = CYAN_ANSI_CODE;
						break;
					case 6:
						colorCode = PURPLE_ANSI_CODE;
						break;
					case 7:
						colorCode = BLUE_ANSI_CODE;
						break;
					case 8:
						colorCode = YELLOW_ANSI_CODE;
						break;
					default:
						colorCode = WHITE_ANSI_CODE;
						break;
					}
					printBombsCount(oSlot, colorCode);
				}
				else {
					printf(" %c ", ' ');
				}
			}
			else {
				if (oSlot->bFlag) {
					printf(" %c ", 'F');
				}
				else {
					printf(" %c ", '.');
				}
			}
			setTerminalColor(WHITE_ANSI_CODE);
		}
		printf("\n");
	}
}

void revealGrid(Board* oBoard) {
	for (int i = 0; i < oBoard->iWidth; i++) {
		for (int j = 0; j < oBoard->iHeight; j++) {
			GridSlot* oSlot = getValue(oBoard, i, j);
			oSlot->bRevealed = 1;
		}
	}
}

void loose(Board* oBoard) {
	system("cls");
	revealGrid(oBoard);
	printf("You lost!");
}

int getArrayPosition(int i, int j, int iWidth) {
	return i * iWidth + j;
}

void getTwoDimensionalPosition(Board* oBoard, int pos, int* coords) {
	coords[1] = pos % oBoard->iWidth;
	coords[0] = (pos - coords[1]) / oBoard->iWidth;
}

int isInBorder(Board* oBoard, int x, int y) {
	return (x >= 0 && x < oBoard->iWidth && y >= 0 && y < oBoard->iHeight);
}