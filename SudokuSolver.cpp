//Sudoku solving program, entry level
//Antoni Severini      12/3/15

#include<iostream>
using namespace std;

//Function prototypes****
bool FindEmptyCell(int grid[][9], int &row, int &col);
bool isSafe(int grid[][9], int row, int col, int num);
bool SolveSudoku(int grid[][9]);
bool checkRow(int grid[][9], int row, int num);
bool checkCol(int grid[][9], int col, int num);
bool checkSquare(int grid[][9], int boxStartRow, int boxStartCol, int num);
void printBoard(int grid[][9]);
void getPuzzle(int grid[][9]);

int main()
{
	int grid[9][9] = {0};
	getPuzzle(grid);
	if (SolveSudoku(grid) == true)
    {
        cout << endl << "Original puzzle top, answer bottom" << endl << endl;
		printBoard(grid);
    }
	else
		cout << ("No solution exists");

	return 0;
}

//Function definitions*****

//Takes user input and applies to Grid array
void getPuzzle(int grid[9][9])
{
    int x = 0;
    int y = 0;
    int num = 0;
    char add = ' ';

    cout << endl;
    cout << "Enter puzzle numbers in grid format" << endl;
    cout << "Use 1 threw 9 for X axis, left to right" << endl;
    cout << "Then 1 threw 9 for Y axis, top to bottom" << endl;
    cout << "Example: cell 1/1 = top left, cell 9/9 = bottom right" << endl << endl;
while (add != 'N')
{
    //Input X axis
    do
    {
    cout << "Input X axis (1 threw 9)" << endl;
    cin >> x;
    }
    while (x > 9);

    //Input Y axis
    do
    {
    cout << "Input Y axis (1 threw 9)" << endl;
    cin >> y;
    }
    while (y > 9);

    //Input number
    do
    {
        cout << "Enter number to fill cell " << x << "/" << y << " : " << endl;
        cin >> num;
    }
    while (num > 9);

    //Fill cell
    grid[x-1][y-1] = num;

    //Update loop read
    printBoard(grid);
    cout << endl << "Add entry? Y/N: " << endl << endl;
    cin >> add;
    add = toupper(add);

}//end outer loop
    printBoard(grid);
}//end main

//Prints out the board using Grid array
void printBoard(int nums2[9][9])
{
    for (int x = 0; x < 9; x++)
    {
        cout << "       ";
        for (int y = 0; y < 9; y++)
        {
            cout << nums2[y][x] << " ";
        }
        cout << endl;
    }

}

//Searches Grid array for empty cell
bool FindEmptyCell(int grid[9][9], int &row, int &col)
{
	for (row = 0; row < 9; row++)
		for (col = 0; col < 9; col++)
			if (grid[row][col] == 0)
				return true;
	return false;
}


//Try numbers 1-9 in all 0 (empty) cells
bool SolveSudoku(int grid[9][9])
{
	int row, col;

	//Complete when no zeros are found
	if (!FindEmptyCell(grid, row, col))
	return true; // success!

	for (int num = 1; num < 10; num++)
	{
		if (isSafe(grid, row, col, num))
		{
			grid[row][col] = num;

			if (SolveSudoku(grid))
				return true;

			//Reset cell to zero if no numbers can be added
			grid[row][col] = 0;
		}
	}
	return false;
}

//Check row for conflict
bool checkRow(int grid[][9], int row, int num)
{
	for (int col = 0; col < 9; col++)
		if (grid[row][col] == num)
			return true;
	return false;
}

//Check column for conflict
bool checkCol(int grid[9][9], int col, int num)
{
	for (int row = 0; row < 9; row++)
		if (grid[row][col] == num)
			return true;
	return false;
}

//Check 3x3 square for conflict
bool checkSquare(int grid[9][9], int boxStartRow, int boxStartCol, int num)
{
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (grid[row+boxStartRow][col+boxStartCol] == num)
				return true;
	return false;
}

//Check for conflict on board with new number
bool isSafe(int grid[9][9], int row, int col, int num)
{
	return !checkRow(grid, row, num) &&
		!checkCol(grid, col, num) &&
		!checkSquare(grid, row - row%3 , col - col%3, num);
}
