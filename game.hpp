/* @Author: Yue lin */

#include <vector>
#include <cstdlib>

#define S 4
#define FOR for(uint8 i = 0; i < S; i++) for(uint8 j = 0; j < S; j++)

typedef unsigned int uint;
typedef unsigned char uint8;
typedef unsigned long long ull;
typedef std::vector<uint8> Vector;
typedef std::vector<Vector> Matrix;

enum Action{LEFT, UP, RIGHT, DOWN};

namespace tf
{
    void rot90(uint8 matrix[S][S], uint8 num)
    {
        uint8 temp[S][S];
        switch(num % 4)
        {
            case 0:
                return;
            case 1:
                FOR temp[i][j] = matrix[j][S - i - 1]; break;
            case 3:
                FOR temp[i][j] = matrix[S - j - 1][i]; break;
            case 2:
                FOR temp[i][j] = matrix[S - i - 1][S - j - 1];
        }
        FOR matrix[i][j] = temp[i][j];
    }

    void flip(uint8 matrix[S][S], uint8 result[S][S])
    {
        FOR result[i][j] = matrix[i][S - j - 1];
    }
}

class Game
{
    public:
        ull score;
        uint8 board[S][S];
        uint8 moved[S][S];
        uint pow[S * S + 1];

        Game();
        Game copy();
        void fill();
        bool over();
        void restart();
        Matrix empty();
        bool move(enum Action);
        void step(enum Action);
};

Game::Game()
{
    int p2 = 2;
    pow[0] = 0;
    for(uint p = 1; p < S * S + 1; p++)
    {
        pow[p] = p2; p2 <<= 1;
    }
    restart();
}

Game Game::copy()
{
    Game cp;
    FOR cp.board[i][j] = board[i][j];
    return cp;
}

void Game::fill()
{
    Matrix coordinates = empty();
    Vector coordinate = coordinates[rand() % coordinates.size()];
    board[coordinate[0]][coordinate[1]] = 1;  // TODO: Fill 2 with 10% probability
}

bool Game::over()
{
    FOR if(!board[i][j])
        return false;
    for(uint8 i = 1; i < S; i++)
        for(uint8 j = 0; j < S; j++)
            if(board[i][j] == board[i - 1][j] || board[j][i] == board[j][i - 1])
                return false;
    return true;
}

void Game::restart()
{
    score = 0;
    FOR board[i][j] = moved[i][j] = 0;
    fill(); fill();
}

Matrix Game::empty()
{
    Matrix coordinates;
    FOR if(!board[i][j])
    {
        Vector coordinate(2);
        coordinate[0] = i;
        coordinate[1] = j;
        coordinates.push_back(coordinate);
    }
    return coordinates;
}

bool Game::move(enum Action action)
{
    bool mv = false;
    if(action == LEFT)
    {
        FOR moved[i][j] = 0;
        for(uint8 row = 0; row < S; row++)
        {
            uint8 left = 0;
            uint8* line = board[row];
            for(uint8 right = 1; right < S; right++)
                if(line[right])
                    if(line[left] == line[right])
                    {
                        mv = true;
                        line[right] = 0;
                        score += pow[++line[left]];
                        moved[row][right] = right - (left++) + 1;
                    }
                    else
                    {
                        if(line[left]) left++;
                        line[left] = line[right];
                        if(right > left)
                        {
                            mv = true;
                            line[right] = 0;
                            moved[row][right] = right - left + 1;
                        }
                    }
        }
    }
    else
    {
        tf::rot90(board, action);
        mv = move(LEFT);
        tf::rot90(moved, 4 - action);
        tf::rot90(board, 4 - action);
    }
    return mv;
}

void Game::step(enum Action action)
{
    if(move(action))
        fill();
}
