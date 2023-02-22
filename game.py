from time import sleep
from random import choice

import numpy as np
import pygame as pg

ACTIONS = (LEFT, UP, RIGHT, DOWN) = tuple(range(4))


class Game:
    """
    2048 game.
    """
    def __init__(self, n: int = 4):
        """
        :param n: The board size will be n x n.
        """
        self.n = n
        self.score = 0
        self.board = np.zeros((n, n), np.uint32)

    def __str__(self):
        return "\n".join(["\t".join(map(str, line)) for line in self.board])

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

    def move(self, action: int) -> bool:
        """
        Move the board once.
        :param action: Direction of movement, must be one of ACTIONS.
        :return: Whether it can be moved.
        """
        if action == LEFT:
            moved = False
            for line in self.board:
                left = 0
                for right in range(1, self.n):
                    if line[right]:
                        if line[right] == line[left]:
                            moved = True
                            line[right] = 0
                            line[left] <<= 1
                            self.score += line[left]
                            left += 1
                        else:
                            if line[left]:
                                left += 1
                            line[left] = line[right]
                            if right > left:
                                moved = True
                                line[right] = 0
        else:
            self.board = np.rot90(self.board, action)
            moved = self.move(LEFT)
            self.board = np.rot90(self.board, -action)
        return moved

    def step(self, action: int) -> None:
        """
        Perform an action.
        """
        if self.move(action):
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
                 name: str = "2048"):
        """
        :param n: Same as n of Game. Default: 4.
        :param pad: Distance between adjacent cells. Default: 10.
        :param size: Interface size. Default: 100.
        :param name: Interface name. Default: '2048'
        """
        pg.init()
        self.pad = pad
        self.size = size
        pg.display.set_caption(name)
        super(Interface, self).__init__(n)
        self.font = pg.font.Font("font.ttf", pad * 4)
        self.colors = eval(open("color.json").read())
        pg.display.set_icon(pg.image.load("icon.jpeg"))
        self.interface = pg.display.set_mode((n * size + (n + 1) * pad,) * 2)
        self.interface.fill(self.colors["BG"])

    def step(self, action: int, pause: float = 0.1) -> bool:
        """
        :param action: Action to be performed.
        :param pause: Time interval to move to fill. Default: 0.1. Unit: s.
        :return: Whether the game is over.
        """
        if self.move(action):
            self.update()
            sleep(pause)
            self.fill(action)
            self.update()
        return self.over

    def update(self) -> None:
        """
        Update game interface.
        No animation effect temporarily >_< !
        """
        y = self.pad
        self.check_quit()
        for line in self.board:
            x = self.pad
            for number in map(str, line):
                pg.draw.rect(
                    self.interface,
                    self.colors["background"][number],
                    (x, y, self.size, self.size)
                )
                if number != "0":
                    number = self.font.render(
                        number, True, self.colors["number"][number]
                    )
                    self.interface.blit(
                        number,
                        (x + (self.size - number.get_width()) // 2,
                         y + (self.size - self.pad * 4) // 2)
                    )
                x += self.size + self.pad
            y += self.size + self.pad
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
    game.restart()
    ACTIONS = {pg.K_w: UP, pg.K_s: DOWN, pg.K_a: LEFT, pg.K_d: RIGHT}
    while not over:
        for e in pg.event.get():
            if e.type == pg.QUIT:
                pg.quit()
                exit()
            if e.type == pg.KEYDOWN and e.key in ACTIONS:
                over = game.step(ACTIONS[e.key])
