from time import sleep
from random import choice

import numpy as np
import pygame as pg

ACTION = ("left ", "up   ", "right", "down ")
ACTIONS = (LEFT, UP, RIGHT, DOWN) = tuple(range(len(ACTION)))


class Game:
    """
    2048 game.
    """
    def __init__(self, n: int = 4):
        """
        :param n: The board size will be n x n. Default: 4.
        """
        self.n = n
        self.score = 0
        self.board = np.zeros((n, n), np.uint32)

    def __str__(self):
        return '\n'.join(['\t'.join(map(str, line)) for line in self.board])

    @property
    def over(self) -> bool:
        """
        :return: Whether the game is over.
        """
        if 0 in self.board:
            return False
        for i in range(1, self.n):
            for j in range(self.n):
                if self.board[i, j] == self.board[i - 1, j]:
                    return False
                if self.board[j, i] == self.board[j, i - 1]:
                    return False
        return True

    def copy(self):
        """
        :return: A copy of the game.
        """
        copy = Game(self.n)
        copy.board = self.board.copy()
        return copy

    def fill(self, action: int = None) -> None:
        """
        Fill a 2 on the board.
        :param action: Last action, it will feel the filling position.
                       Default: None.
        """
        if action == LEFT:
            board = self.board[:, 1:]
        elif action == UP:
            board = self.board[1:, :]
        elif action == DOWN:
            board = self.board[:-1, :]
        elif action == RIGHT:
            board = self.board[:, :-1]
        else:
            board = self.board
        board[tuple(choice(np.array(np.where(board == 0)).T))] = 2

    def move(self, action: int) -> np.ndarray:
        """
        Move the board once.
        :param action: Direction of movement, must be one of ACTIONS.
        :return: The distance moved by each grid.
        """
        if action == LEFT:
            moved = np.zeros_like(self.board, np.uint8)
            for row, line in enumerate(self.board):
                left = 0
                for right in range(1, self.n):
                    if line[right]:
                        if line[right] == line[left]:
                            line[right] = 0
                            line[left] <<= 1
                            self.score += line[left]
                            moved[row, right] = right - left + 1
                            left += 1
                        else:
                            if line[left]:
                                left += 1
                            line[left] = line[right]
                            if right > left:
                                line[right] = 0
                                moved[row, right] = right - left + 1
        else:
            self.board = np.rot90(self.board, action)
            moved = np.rot90(self.move(LEFT), -action)
            self.board = np.rot90(self.board, -action)
        return moved

    def step(self, action: int) -> None:
        """
        Perform an action.
        """
        if self.move(action).any():
            self.fill(action)

    def restart(self) -> None:
        """
        Restart the game.
        """
        self.score = 0
        self.board *= 0
        for _ in range(2):
            self.fill()


class Interface(Game):
    """
    2048 game interface.
    """
    def __init__(self,
                 n: int = 4,
                 pad: int = 10,
                 size: int = 100,
                 name: str = "2048",
                 speed: float = 0.1):
        """
        :param n: Same as n of Game. Default: 4.
        :param pad: Distance between adjacent cells. Default: 10.
        :param size: Interface size. Default: 100.
        :param name: Interface name. Default: '2048'.
        :param speed: The speed at which the grid moves, between 0 and 1.
                      A larger value means a faster speed. Default: 0.1.
        """
        pg.init()
        self.dp = speed
        self.pad = pad
        self.size = size
        pg.display.set_caption(name)
        super(Interface, self).__init__(n)
        self.font = pg.font.Font("font.ttf", pad * 4)
        self.colors = eval(open("color.json").read())
        pg.display.set_icon(pg.image.load("icon.jpeg"))
        self.interface = pg.display.set_mode((n * size + (n + 1) * pad,) * 2)

    def step(self, action: int) -> bool:
        """
        :param action: Action to be performed.
        :return: Whether the game is over.
        """
        board = self.board.copy()
        print("Action: {}".format(ACTION[action]), end="\tScore: ")
        if (moved := self.move(action)).any():
            board, self.board = self.board, board
            for progress in np.arange(0, 1, self.dp):
                self.update(action, moved, progress)
            sleep(self.dp)
            self.board = board
            self.fill(action)
            self.update()
            print(self.score)
        else:
            print(self.score, "\t Cannot moved")
        return self.over

    def clear(self) -> None:
        """
        Clear interface.
        """
        d = self.pad + self.size
        self.interface.fill(self.colors["BG"])
        for x in range(self.n):
            for y in range(self.n):
                pg.draw.rect(
                    self.interface,
                    self.colors["background"]['0'],
                    (self.pad + x * d, self.pad + y * d, self.size, self.size)
                )

    def update(self,
               action: int = None,
               moved: np.ndarray = None,
               progress: float = 0) -> None:
        """
        Update game interface.
        :param action: direction of movement. Default: None.
        :param moved: The distance moved by each grid. Default: None.
        :param progress: Movement progress, between 0 and 1. Default: 0.
        """
        y = self.pad
        self.clear()
        self.check_quit()
        dxy = self.size + self.pad
        if moved is None:
            moved = np.zeros_like(self.board, np.uint8)
        for r, line in enumerate(self.board):
            x = self.pad
            for c, number in enumerate(map(str, line)):
                if number != '0':
                    dx, dy = 0, 0
                    if moved[r, c]:
                        if action % 2:
                            dy = int(dxy * progress * np.sign(action - 1.5))
                        else:
                            dx = int(dxy * progress * np.sign(action - 1.5))
                    pg.draw.rect(
                        self.interface,
                        self.colors["background"][number],
                        (x + dx, y + dy, self.size, self.size)
                    )
                    number = self.font.render(
                        number, True, self.colors["number"][number]
                    )
                    x0 = x + (self.size - number.get_width()) // 2
                    y0 = y + (self.size - number.get_height()) // 2
                    self.interface.blit(number, (x0 + dx, y0 + dy))
                x += dxy
            y += dxy
        pg.display.update()

    def restart(self) -> None:
        """
        Restart the game.
        """
        super().restart()
        self.update()

    @staticmethod
    def check_quit():
        """
        Check whether to quit.
        """
        for event in pg.event.get():
            if event.type == pg.QUIT:
                pg.quit()
                exit()


# human play
if __name__ == "__main__":
    over = False
    game = Interface()
    inputs = {
        pg.K_UP: UP,
        pg.K_DOWN: DOWN,
        pg.K_LEFT: LEFT,
        pg.K_RIGHT: RIGHT
    }
    game.restart()
    while not over:
        for e in pg.event.get():
            if e.type == pg.QUIT:
                pg.quit()
                exit()
            if e.type == pg.KEYDOWN and e.key in inputs:
                game.step(inputs[e.key])
                over = game.over
    print("Game over\t\t Score:", game.score)
    while True:
        game.check_quit()
