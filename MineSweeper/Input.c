#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char RULES[] = "\nRules Of Minesweeper :\nYou dispose of a fully hidden board with cases, each case can or cannot be containing a bomb.\nThe goal of the game is to find all the bombs without trigering them. You triger a bomb by clicking on a case that hides one.\nWhen you click on a Case, it will reveal what it\'s hiding.\nThe case will usually reveal a number, which corresponds to the number of bombs in the 8 surrounding cases.\nThe case can also reveal an empty sapce, which means that the 8 surrounding cases don\'t contain any bomb.\n";
const char MOVES[] = "\nTo get the list of Move : 'M'\nTo Print the Rules : 'R'\nTo Discorver a Case: '(colomn)(line)', example : 'C7'\nTo Place a Flag : 'F(colomn)(line)', exmaple : 'FE8'\nTo Quit : 'Q'\n";

void clearInput() {
    while (getchar() != '\n');
}

int isFlag(char* input) {
    if (input[0] == 70 || input[0] == 102) {
        if ((65 <= input[1] && input[1] <= 90) || (97 <= input[1] && input[1] <= 122)) {
            return 1;
        }
    }
    return 0;
}

int validColumn(char* input, int relativeSize) {
    int flag = isFlag(input);
    if ((65 <= input[flag] && input[flag] <= 64 + relativeSize) || (97 <= input[flag] && input[flag] <= 96 + relativeSize)) {
        return 1;
    }
    return 0;
}

int validLine(char nbr1, char nbr2, int relativeSize) {
    nbr1 -= 48;
    nbr2 -= 48;
    int nbr = nbr1 * 10 + nbr2;
    printf("\n%d", nbr);
    return nbr <= relativeSize;
}

void convertToCoords(char nbr1, char nbr2, char tempLetter, int* result) {
    char letter = toupper(tempLetter);
    result[0] = (((nbr1 - 48) * 10 + (nbr2 - 48)) - 1);
    result[1] = letter - 65;
}

int* validInput(char* input, int iWidth, int iHeight) {
    int* result = (int*)malloc(sizeof(int) * 2);;
    if (result) {
        if (strlen(input) == 1) {
            if ((tolower(*input) == 'm' || tolower(*input) == 'r' || tolower(*input) == 'q')) {
                result[0] = 1;
                return result;
            }
        }
        if (validColumn(input, iWidth)) {
            if (isFlag(input)) {
                if (strlen(input) == 3) {
                    if (validLine('0', input[2], iHeight)) {
                        convertToCoords('0', input[2], input[1], result);
                        return result;
                    }
                }
                else if (strlen(input) == 4) {
                    if (validLine(input[2], input[3], iHeight)) {
                        convertToCoords(input[2], input[3], input[1], result);
                        return result;
                    }
                }
            }
            else {
                if (strlen(input) == 2) {
                    if (validLine('0', input[1], iHeight)) {
                        convertToCoords('0', input[1], input[0], result);
                        return result;
                    }
                }
                else if (strlen(input) == 3) {
                    if (validLine(input[1], input[2], iHeight)) {
                        convertToCoords(input[1], input[2], input[0], result);
                        return result;
                    }
                }
            }
        }
        result[0] = -1;
        return result;
    }
    return NULL;
}

int isTool(char* input) {
    if (strlen(input) == 1) {
        if (tolower(*input) == 'm') {
            printf("%s", MOVES);
            return 1;
        }
        else if (tolower(*input) == 'r') {
            printf("%s", RULES);
            return 1;
        }
        else if (tolower(*input) == 'q') {
            quitGame();
            return 1;
        }
    }
    return 0;
}

int quitGame() {
    char quit[1];
    while (1) {
        printf("Do you want to Quit the Game ? (Y/N) > ");
        clearInput();
        scanf_s("%s", &quit, 2);
        if (tolower(*quit) == 'n') {
            printf("\nGame Continues\n");
            return 1;
        }
        else if (tolower(*quit) == 'y') {
            printf("\nThank you for playing ! GAME OVER.\n\n");
            exit(0);
        }
    }
}