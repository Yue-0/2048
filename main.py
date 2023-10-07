from game import Interface
from mcs import MonteCarloSearch

STEP = 100

game, AI = Interface(), MonteCarloSearch(STEP)

over = False
game.restart()
while not over:
    over = game.step(AI(game))
print("Game over\t\t Score:", game.score)
while True:
    game.check_quit()  # Game is over, wait to quit
