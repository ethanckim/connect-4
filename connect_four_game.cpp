/*
AUTHOR: Ethan Kim
ACKNOWLEDGEMENTS:
https://stackoverflow.com/questions/32770321/connect-4-check-for-a-win-algorithm/32771681
*/

#include <iostream>
#include <fstream>

using namespace std;

enum tile{empty, O, X};
const int WIN_LENGTH = 4;
const int MAX_ROW = 6;
const int MAX_COL = 7;
const int INDEX_SHIFT = 1;

void winCheck(tile board[MAX_ROW][MAX_COL], int row, int col,
              int & xConsec, int & oConsec, bool & xWins, bool & oWins)
{
    if (board[row][col] == X)
    {
        xConsec++;
        oConsec = 0;
    }
    else if (board[row][col] == O)
    {
        oConsec++;
        xConsec = 0;
    }
    else // if (board[row][col] == empty)
    {
        oConsec = 0;
        xConsec = 0;
    }

    if (xConsec >= WIN_LENGTH)
        xWins = true;
    else if (oConsec >= WIN_LENGTH)
        oWins = true;
}

void printBoard(tile board[MAX_ROW][MAX_COL])
{
    cout << "Board State:" << endl;
    for (int row = 0; row < MAX_ROW; row++)
    {
        for (int col = 0; col < MAX_COL; col++)
        {
            switch (board[row][col])
            {
                case empty:
                    cout << '_';
                    break;
                case O:
                    cout << 'O';
                    break;
                case X:
                    cout << 'X';
                    break;
            }
            cout << ' ';
        }
        cout << endl;
    }
}

int main()
{
    tile board[MAX_ROW][MAX_COL] = {empty};
    int tokensInRow[MAX_COL] = {0};
    int turnMove = 0;
    tile player = X;
    bool xWins = false, oWins = false;

    cout << "Welcome to Connect 4!" << endl
         << "Developed by Ethan Kim" << endl;

    do
    {
        // log
        cout << endl << "Current Player turn: ";
        if (player == X)
            cout << "X";
        else // if (player = O)
            cout << "O";
        cout << endl;
        printBoard(board);
        cout << endl << "Please enter the column to insert your token: ";
        cin >> turnMove;
        cout << endl;

        // read one turn, update board, and switch player
        int turnCol = turnMove - INDEX_SHIFT;
        int turnRow = MAX_ROW - INDEX_SHIFT - tokensInRow[turnCol]++;
        board[turnRow][turnCol] = player;
        if (player == X)
            player = O;
        else // (player == O)
            player = X;

        // check for a 4-in-a-row win
        for (int row = 0; row < MAX_ROW; row++)
        {
            int xInARow = 0, oInARow = 0;
            for (int col = 0; col < MAX_COL; col++)
                winCheck(board, row, col, xInARow, oInARow, xWins, oWins);
        }

        // check for a 4-in-a-column win
        for (int col = 0; col < MAX_COL; col++)
        {
            int xInACol = 0, oInACol = 0;
            for (int row = 0; row < MAX_ROW; row++)
                winCheck(board, row, col, xInACol, oInACol, xWins, oWins);
        }

        // check for 4 diagonal win from top left to bottom right
        for (int rowStart = 0; rowStart <= MAX_ROW - WIN_LENGTH; rowStart++)
        {
            int xInADiag = 0, oInADiag = 0;
            for (int row = rowStart, col = 0; row < MAX_ROW && col < MAX_COL; row++, col++)
                winCheck(board, row, col, xInADiag, oInADiag, xWins, oWins);
        }
        for (int colStart = 1; colStart <= MAX_COL - WIN_LENGTH; colStart++)
        {
            int xInADiag = 0, oInADiag = 0;
            for (int row = 0, col = colStart; row < MAX_COL && col < MAX_COL; row++, col++)
                winCheck(board, row, col, xInADiag, oInADiag, xWins, oWins);
        }

        // check for 4 diagonal win from top right to bottom left
        for (int rowStart = 0; rowStart <= MAX_ROW - WIN_LENGTH; rowStart++)
        {
            int xInADiag = 0, oInADiag = 0;
            for (int row = rowStart, col = MAX_COL - INDEX_SHIFT; row < MAX_COL && col >= 0; row++, col--)
                winCheck(board, row, col, xInADiag, oInADiag, xWins, oWins);
        }
        for (int colStart = MAX_COL - INDEX_SHIFT; colStart >= WIN_LENGTH; colStart--)
        {
            int xInADiag = 0, oInADiag = 0;
            for (int row = 0, col = colStart; row < MAX_COL && col >= 0; row++, col--)
                winCheck(board, row, col, xInADiag, oInADiag, xWins, oWins);
        }

    } while (!xWins && !oWins);

    cout << endl;
    printBoard(board);
    // output win status
    cout << endl;
    if (xWins)
        cout << "Player X has won.";
    else if (oWins)
        cout << "Player O has won.";
    else
        cout << "Neither player has won yet.";

    return 0;
}