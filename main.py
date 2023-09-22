import time

import config as cfg
from game import Interface
from mcs import MonteCarloSearch


game, AI = Interface(), MonteCarloSearch(cfg.step)

over = False
game.restart()
while not over:
    over = game.step(AI(game))
print("Game over\t\t Score:", game.score)
while True:
    game.check_quit()  # Game is over, wait to quit
