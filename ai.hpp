/* @Author: Yue lin */

#include "game.hpp"

#define S2 S * S
#define INF 0xFFFFFFFFFFFFFFFFULL

namespace find
{
    ull max(ull array[], uint8 len)
    {
        ull m = array[0];
        for(uint8 i = 1; i < len; i++)
            m = std::max(array[i], m);
        return m;
    }

    uint8 argmax(ull array[], uint8 len)
    {
        ull m = 0;
        Vector indexes;
        for(uint8 index = 0; index < len; index++)
            if(array[index] == m)
                indexes.push_back(index);
            else if(array[index] > m)
            {
                indexes.clear();
                m = array[index];
                indexes.push_back(index);
            }
        return indexes[rand() % indexes.size()];
    }
}

class AI
{
    public:
        AI(uint8);
        enum Action inference(Game);
    
    private:
        uint8 depth;
        ull weights[24][S][S];

        ull score(Game);
        ull search(Game, uint8);
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

ull AI::search(Game game, uint8 deep = 0)
{
    // No prune
    if(deep == depth)
        return score(game);
    if(deep % 2)
    {
        ull min = INF;
        for(Vector empty: game.empty())
        {
            game.board[empty[0]][empty[1]] = 1;
            min = std::min(search(game, deep + 1), min);
            game.board[empty[0]][empty[1]] = 0;
        }
        return min;
    }
    else
    {
        ull scores[4] = {0, 0, 0, 0};
        for(uint8 action = 0; action < 4; action++)
        {
            Game copy = game.copy();
            if(copy.move((enum Action)action))
                scores[action] = search(copy, deep + 1);
        }
        return deep? find::max(scores, 4): find::argmax(scores, 4);
    }
}

enum Action AI::inference(Game game)
{
    return (enum Action)search(game.copy());
}
