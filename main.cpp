/* @Author: Yue lin */

#include "window.hpp"

#define START int main(){
#define THE Window().show();
#define GAME return 0;}

START THE GAME

// int main()
// {
//     AI ai(4);
//     Game game;
//     uint8 max;
//     double ave_score = 0, ave_max = 0;
//     for(int rnd = 1; rnd <= 100; rnd++)
//     {
//         srand(rnd);
//         game.restart();
//         while(!(game.over()))
//         {
//             max = 0;
//             game.step(ai.inference(game));
//             FOR max = std::max(game.board[i][j], max);
//             printf("\r%d:\tMax = %d,\tScore = %lld", rnd, POW[max], game.score);
//         }
//         printf("\r%d:\tMax = %d,\tScore = %lld\n", rnd, POW[max], game.score);
//         ave_max += POW[max];
//         ave_score += game.score * 1e-2;
//     }
//     std::cout << "Max(ave) = " << ave_max * 1e-2 << "\t Score(ave) = " << ave_score << std::endl;
// }
