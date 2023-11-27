/* @Author: Yue lin */

#include <thread>

#include "game.hpp"

#define INF 0xFFFFFFFFFFFFFFFFULL

#define SEARCH(board) search(board, deep + 1, alpha, beta)

class AI
{
    public:
        AI(uint8);
        enum Action inference(Game);
    
    private:
        uint8 depth;
        ull weights[24][S][S];

        ull score(Game);
        ull search(Game, uint8, ull, ull);
};

AI::AI(uint8 deep): depth(deep << 1)
{
    ull p = 1;
    ull pow[S2];
    uint8 w = S2;
    uint8 temp[24][S][S], weight[3][S][S] = {
        15, 14, 13, 12, 8, 9, 10, 11, 7, 6, 5, 4, 0, 1, 2, 3,
        15, 14, 11, 3, 13, 12, 10, 2, 9, 8, 7, 1, 6, 5, 4, 0,
        15, 14, 13, 3, 12, 11, 10, 2, 9, 8, 7, 1, 6, 5, 4, 0
    };
    while(w)
    {
        pow[S2 - w--] = p; p <<= 4;
    }
    for(w = 0; w < 3; w++)
    {
        uint8 o = w << 3;
        for(p = 0; p < 4; tf::rot90(weight[w], 1))
        {
            FOR temp[o + p][i][j] = weight[w][i][j];
            tf::flip(weight[w], temp[o + (p++) + 4]);
        }
    }
    for(w = 0; w < 24; w++) FOR weights[w][i][j] = pow[temp[w][i][j]];
}

uint8 argmax(ull array[], const uint8 len)
{
    ull m = 0;
    uint8 size = 0;
    uint8 indexes[len];
    for(uint8 index = 0; index < len; index++)
        if(array[index] == m)
            indexes[size++] = index;
        else if(array[index] > m)
        {
            size = 0;
            m = array[index];
            indexes[size++] = index;;
        }
    return indexes[rand() % size];
}

ull AI::score(Game game)
{
    ull max = 0, sum = 0;
    for(uint8 w = 0; w < 24; w++)
    {
        FOR sum += weights[w][i][j] * game.board[i][j];
        if(sum > max) max = sum; sum = 0;
    }
    return max;
}

ull AI::search(Game game, uint8 deep = 0, ull alpha = 0, ull beta = INF)
{
    if(!deep)
    {
        std::thread searcher[4];
        ull scores[4] = {0, 0, 0, 0};
        for(uint8 action = 0; action < 4; action++)
            searcher[action] = std::thread(
                [=, &game, &scores]
                {
                    Game copy = game.copy();
                    if(copy.move((enum Action)action))
                        scores[action] = search(copy, 1) + 1;
                }
            );
        for(uint8 action = 0; action < 4; action++)
            searcher[action].join();
        return argmax(scores, 4);
    }
    if(deep == depth)
        return score(game);
    if(deep % 2)
    {
        ull min = INF;
        uint8 empty[S2][2];
        uint8 loop = game.empty(empty);
        for(uint8 fill = 2; fill; fill--)
            for(uint8 e = 0; e < loop; e++)
            {
                game.board[empty[e][0]][empty[e][1]] = fill; 
                min = std::min(SEARCH(game), min);
                game.board[empty[e][0]][empty[e][1]] = 0;
                if((beta = std::min(beta, min)) <= alpha)
                    return min;
            }
        return min;
    }
    else
    {
        ull max = 0;
        for(uint8 action = 0; action < 4; action++)
        {
            Game copy = game.copy();
            if(copy.move((enum Action)action))
            {
                max = std::max(SEARCH(copy), max);
                if(beta <= (alpha = std::max(alpha, max)))
                    break;
            }
        }
        return max;
    }
}

enum Action AI::inference(Game game)
{
    return (enum Action)search(game);
}
