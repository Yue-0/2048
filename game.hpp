/* @Author: Yue lin */

#include <cstdlib>

#define S 4
#define S2 S * S
#define FOR for(uint8 i = 0; i < S; i++) for(uint8 j = 0; j < S; j++)

typedef unsigned int uint;
typedef unsigned char uint8;
typedef unsigned long long ull;

enum Action{LEFT, UP, RIGHT, DOWN};
uint POW[S2 + 2] = {0, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
                    2048, 4096, 8192, 16384, 32768, 65536, 131072};

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

        Game(){};
        Game copy();
        void fill();
        bool over();
        void restart();
        bool move(enum Action);
        void step(enum Action);
        uint8 empty(uint8 [][2]);
};

Game Game::copy()
{
    Game cp;
    cp.score = score;
    FOR cp.board[i][j] = board[i][j];
    return cp;
}

void Game::fill()
{
    uint8 xy[S2 - 2][2];
    uint8 size = empty(xy);
    uint8 index = rand() % size;
    board[xy[index][0]][xy[index][1]] = (rand() % 10? 1: 2);
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
                        score += POW[++line[left]];
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

uint8 Game::empty(uint8 coordinates[][2])
{
    uint len = 0;
    FOR if(!board[i][j])
    {
        coordinates[len][0] = i;
        coordinates[len++][1] = j;
    }
    return len;
}
