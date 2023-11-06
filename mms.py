import game

np = game.np


class MiniMaxSearch:
    """
    Mini-Max search algorithm.
    """
    def __init__(self, depth: int = 1):
        """
        Note: Currently only available for games with a board size of 4x4.
        :param depth: The actual search depth is 2 times this value. Default: 1.
        """
        weight = np.array([
            [[15, 14, 11, 3], [13, 12, 10, 2], [9, 8, 7, 1], [6, 5, 4, 0]],
            [[15, 14, 13, 3], [12, 11, 10, 2], [9, 8, 7, 1], [6, 5, 4, 0]],
            [[15, 14, 13, 12], [8, 9, 10, 11], [7, 6, 5, 4], [0, 1, 2, 3]]
        ])
        self.depth = depth << 1
        self.weights = np.zeros((24, 4, 4), np.uint64)
        for w in range(3):
            w8 = w << 3
            for r in range(4):
                self.weights[w8 + r] = np.rot90(weight[w], r)
                self.weights[w8 + r + 4] = np.flip(self.weights[w8 + r], 0)
        self.weights.resize((24, 16))
        self.weights = 16 ** self.weights

    def __call__(self, board: game.Game) -> int:
        """
        :param board: Game situation.
        :return: Best action.
        """
        return self.search(board.copy())

    def score(self, board: game.Game) -> int:
        """
        :param board: Game situation.
        :return: Score of game situation.
        """
        return np.max(np.sum(self.weights * board.log2, 1))

    def search(self, board: game.Game, depth: int = 0) -> int:
        """
        Search the current game situation.
        :param board: Game situation.
        :param depth: Current search depth.
        :return: If the current node is the initial, return the best action,
                 else, return the score for this node.
        """
        if depth == self.depth:
            return self.score(board)
        # TODO: Need pruning.
        if depth % 2:
            scores = []
            for y, x in np.array(np.where(board.board == 0)).T:
                board.board[y, x] = 2
                scores.append(self.search(board, depth + 1))
                board.board[y, x] = 0
            return min(scores)  # It seems impossible for scores to be empty
        else:
            scores = [-np.inf] * len(game.ACTIONS)
            for a, action in enumerate(game.ACTIONS):
                copy = board.copy()
                if copy.move(action).any():
                    scores[a] = self.search(copy, depth + 1)
            return max(scores) if depth else self.argmax(scores)

    @staticmethod
    def argmax(array: list) -> int:
        """
        Calculate the index of the maximum value of the list,
        if there are multiple maximum values, return a random one.
        """
        result, m = [], -np.inf
        for index, num in enumerate(array):
            if num == m:
                result.append(index)
            elif num > m:
                result, m = [index], num
        return game.choice(result)
