from warnings import warn
from argparse import ArgumentParser

from game import Interface
from mms import MiniMaxSearch
from mcs import MonteCarloSearch

arg = ArgumentParser()
arg.add_argument(
    "--size", default=4, type=int, help="Board size"
)
arg.add_argument(
    "--depth", default=2, type=int, help="Mini-Max search depth"
)
arg.add_argument(
    "--step", default=100, type=int, help="Monte Carlo search steps"
)
arg.add_argument(
    "--method", default="mcs", type=str, help="AI method, 'mcs' or 'mms'"
)
arg = arg.parse_args()
if arg.size <= 0:
    raise ValueError("size must be a positive integer.")
if arg.size > 4:
    warn(' '.join([
        "The board size is too large,",
        "you may encounter some errors."
    ]))
over, game = False, Interface(arg.size)
if arg.method.lower() == "mcs":
    if arg.step <= 0:
        raise ValueError("step must be a positive integer.")
    if arg.step > 400:
        warn(' '.join([
            "The search step is too large,",
            "so you may need to wait for a long time."
        ]))
    AI = MonteCarloSearch(arg.step)
elif arg.method.lower() == "mms":
    assert arg.size == 4, "When you select mms, size must be equal to 4."
    if arg.depth <= 0:
        raise ValueError("depth must be a positive integer.")
    if arg.depth > 3:
        warn(' '.join([
            "The search depth is too large,",
            "so you may need to wait for a long time."
        ]))
    AI = MiniMaxSearch(arg.depth)
else:
    raise TypeError(' '.join([
        "No method named {} was found.".format(arg.method),
        "Currently only 'mms' and 'mcs' are supported."
    ]))
game.restart()
while not over:
    over = game.step(AI(game))
print("Game over\t\t Score:", game.score)
while True:
    game.check_quit()  # Game is over, wait to quit
