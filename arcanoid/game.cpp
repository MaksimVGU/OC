#include <iostream>
#include <cstring>

using namespace std;

const int BOARD_SIZE = 3;

char board[BOARD_SIZE][BOARD_SIZE];

void initBoard()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j] = '-';
        }
    }
}

void printBoard()
{
    cout << "  1 2 3" << endl;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        cout << i + 1 << " ";
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool isBoardFull()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == '-')
            {
                return false;
            }
        }
    }
    return true;
}

bool isWinner(char player)
{
    // Проверка строк
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        bool win = true;
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] != player)
            {
                win = false;
            }
        }
        if (win)
        {
            return true;
        }
    }

    // Проверка столбцов
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        bool win = true;
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[j][i] != player)
            {
                win = false;
            }
        }
        if (win)
        {
            return true;
        }
    }

    // Проверка диагоналей
    bool win = true;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i][i] != player)
        {
            win = false;
        }
    }
    if (win)
    {
        return true;
    }

    win = true;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i][BOARD_SIZE - i - 1] != player)
        {
            win = false;
        }
    }
    if (win)
    {
        return true;
    }

    return false;
}

int main()
{
    initBoard();
    char currentPlayer = 'X';

    while (true)
    {
        printBoard();

        // Получаем ход игрока
        int row, col;
        cout << "Ход игрока " << currentPlayer << ". Введите номер строки и столбца: ";
        cin >> row >> col;

        // Проверяем, что выбранные координаты действительны
        if (row < 1 || row > BOARD_SIZE || col < 1 || col > BOARD_SIZE)
        {
            cout << "Неверные координаты. Попробуйте еще раз." << endl;
            continue;
        }

        // Проверяем, что выбранная клетка не занята
        if (board[row - 1][col - 1] != '-')
        {
            cout << "Эта клетка уже занята. Попробуйте еще раз." << endl;
            continue;
        }

        // Выполняем ход
        board[row - 1][col - 1] = currentPlayer;

        // Проверяем, есть ли победитель
        if (isWinner(currentPlayer))
        {
            cout << "Игрок " << currentPlayer << " победил!" << endl;
            break;
        }

        // Проверяем, заполнена ли доска
        if (isBoardFull())
        {
            cout << "Ничья!" << endl;
            break;
        }

        // Меняем игрока
        if (currentPlayer == 'X')
        {
            currentPlayer = 'O';
        }
        else
        {
            currentPlayer = 'X';
        }
    }   

    printBoard();

    return 0;
}
 