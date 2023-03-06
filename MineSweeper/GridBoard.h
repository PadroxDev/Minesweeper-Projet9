typedef struct GridSlot {
	int x;
	int y;
	int bRevealed;
	int bFlag;
	int bBomb;
	int iBombs;
} GridSlot;


typedef struct Board {
	GridSlot* oGrid;
	int iWidth;
	int iHeight;
	int running;
} Board;

/// <summary>
/// Fill oGrid with default GridSlot values.
/// </summary>
/// <param name="oBoard"></param>
/// <param name="iWidth"></param>
/// <param name="iHeight"></param>
void initGrid(Board* oBoard, int iWidth, int iHeight);

/// <summary>
/// Return the value at the position x and y in oBoard.
/// </summary>
/// <param name="oBoard"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
GridSlot* getValue(Board* oBoard, int x, int y);

/// <summary>
/// Plants iQuantity bombs randomly on oBoard considering a safe zone around the startingX and startingY coordinate.
/// </summary>
/// <param name="oBoard"></param>
/// <param name="iQuantity"></param>
/// <param name="startingX"></param>
/// <param name="startingY"></param>
void plantBombs(Board* oBoard, int iQuantity, int startingX, int startingY);

/// <summary>
/// Set the number of bombs surrounding each slots of oBoard
/// </summary>
/// <param name="oBoard"></param>
void calculateSurroundingBombs(Board* oBoard);

/// <summary>
/// Dig into oBoard at the x and y coordinate.
/// </summary>
/// <param name="oBoard"></param>
/// <param name="x"></param>
/// <param name="y"></param>
void digAt(Board* oBoard, int x, int y);

/// <summary>
/// Handle splash removing recursively to reveal every slot surrounded by an empty.
/// </summary>
/// <param name="oBoard"></param>
/// <param name="oSlot"></param>
void recursiveReveal(Board* oBoard, GridSlot* oSlot);

/// <summary>
/// Set the terminal writing color to sColor
/// </summary>
/// <param name="sColor"></param>
void setTerminalColor(const char sColor[10]);

/// <summary>
/// Change the terminal color to sColor and print the number of bombs surrounding oSlot.
/// </summary>
/// <param name="oSlot"></param>
/// <param name="color"></param>
void printBombsCount(GridSlot* oSlot, char sColor[10]);

/// <summary>
/// Display the formated board.
/// </summary>
/// <param name="oBoard"></param>
void displayGrid(Board* oBoard);

/// <summary>
/// Reveal the entirely oBoard.
/// </summary>
/// <param name="oBoard"></param>
void revealGrid(Board* oBoard);

/// <summary>
/// Handle Loose
/// </summary>
void loose(Board* oBoard);

/// <summary>
/// Return the one-dimensional position from a two-dimensional coordinates grid.
/// </summary>
/// <param name="i"></param>
/// <param name="j"></param>
/// <param name="iWidth"></param>
/// <returns></returns>
int getArrayPosition(int i, int j, int iWidth);

void getTwoDimensionalPosition(Board* oBoard, int pos, int* coords);

/// <summary>
/// Return if the x & y coordinate is outside of the bounds of oBoard.
/// </summary>
/// <param name="oBoard"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
int isInBorder(Board* oBoard, int x, int y);