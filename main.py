import time

import config as cfg
from game import Interface
from mcs import MonteCarloSearch


game, AI = Interface(), MonteCarloSearch(100)

over = False
game.restart()
while not over:
    t = time.time()
    over = game.step(AI(game))
    t += cfg.time - time.time()
    if t >= 0:
        time.sleep(t)
while True:
    game.check_quit()
