import time

import config as cfg
from game import Interface
from mcs import MonteCarloSearch


game, AI = Interface(), MonteCarloSearch(cfg.step)

over = False
game.restart()
input()
while not over:
    t = time.time()
    over = game.step(AI(game))
    t += cfg.time - time.time()
    if t >= 0:
        time.sleep(t)  # Prevent too fast action
print("Game over\t\t Score:", game.score)
while True:
    game.check_quit()  # Game is over, wait to quit
