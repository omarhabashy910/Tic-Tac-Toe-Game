#include <iostream>
#include <string>
using namespace std;

class Player
{
private:
    char symbol;
    string name;

public:
    Player(char sym = 'X', string n = "Player X") : symbol(sym), name(n) {}
    char getSymbol() const { return symbol; }
    string getName() const { return name; }
};

class Board
{
private:
    char grid[5][5];
    int filledCells;

public:
    Board() : filledCells(0)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                grid[i][j] = ' ';
            }
        }
    }
    void drawBoard() const
    {
        cout << "-------------------------" << endl;
        for (int i = 0; i < 5; i++)
        {
            cout << "| ";
            for (int j = 0; j < 5; j++)
            {
                cout << grid[i][j] << " | ";
            }
            cout << endl
                 << "------------------------" << endl;
        }
    }
    bool isValidMove(int row, int col) const
    {
        return (row >= 0 && row < 5 && col >= 0 && col < 5 && grid[row][col] == ' ');
    }
    void makeMove(int row, int col, char symbol)
    {
        if (isValidMove(row, col))
        {
            grid[row][col] = symbol;
            filledCells++;
        }
    }

    bool checkWin(char symbol) const
    {
        // check rows
        for (int i = 0; i < 5; i++)
        {
            if (grid[i][0] == symbol && grid[i][1] == symbol && grid[i][2] == symbol && grid[i][3] == symbol && grid[i][4] == symbol)
            {
                return true;
            }
        }
        // checl Columns
        for (int i = 0; i < 5; i++)
        {
            if (grid[0][i] == symbol && grid[1][i] == symbol && grid[2][i] == symbol && grid[3][i] == symbol && grid[4][i] == symbol)
            {
                return true;
            }
        }
        if (grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol && grid[3][3] == symbol && grid[4][4] == symbol)
        {
            return true;
        }
        if (grid[0][4] == symbol && grid[1][3] == symbol && grid[2][2] == symbol && grid[3][1] == symbol && grid[4][0] == symbol)
        {
            return true;
        }
        return false;
    }
    bool isFull() const
    {
        return filledCells == 25;
    }
    int getFilledCellsCount() const
    {
        return filledCells;
    }
};

class TicTacToe
{
private:
    Board board;
    Player players[2];
    int currentPlayerIndex;
public:
    TicTacToe() : currentPlayerIndex(0)
    {
        players[0] = Player('X' , "Player X");
        players[1] = Player('Y' , "Player Y");      
    }
    Player& getCurrentPlayer()
    {
        return players[currentPlayerIndex];
    }
    void switchTurn()
    {
        currentPlayerIndex = (currentPlayerIndex + 1) % 2;
    }
    void play()
    {
        int row , col;
        cout << "Welcome to Tic-Tac-Toe Game!" << endl;
        while(!board.isFull())
        {
            board.drawBoard();
            Player& currentPlayer = getCurrentPlayer();
            while(true)
            {
                cout << currentPlayer.getName() << " (" << currentPlayer.getSymbol() << ") , enter row (1 - 5) and column(1 - 5): ";
                cin >> row >> col;
                row-- , col --;
                if(board.isValidMove(row , col))
                {
                    break;
                }else
                {
                    cout << "Invalid move . try again" << endl;
                }
            }
            board.makeMove(row , col , currentPlayer.getSymbol());
            if(board.checkWin(currentPlayer.getSymbol()))
            {
                board.drawBoard();
                cout << currentPlayer.getName() << " wins!" << endl;
                return;
            }
            switchTurn();
        }
        board.drawBoard();
        cout << "It's a draw!" << endl;
    }
};

int main()
{
    TicTacToe game;
    game.play();
    
    return 0;
}