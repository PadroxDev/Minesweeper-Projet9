void clearInput();

int isFlag(char* input);

int validColumn(char* input, int relativeSize);

int validLine(char nbr1, char nbr2, int relativeSize);

int* validInput(char* input, int iWidth, int iHeight);

void convertToCoords(char nbr1, char nbr2, char tempLetter, int* result);

int isTool(char* input);

int quitGame();