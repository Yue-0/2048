import game


class MonteCarloSearch:
    def __init__(self, step: int):
        self.step = step

    def __call__(self, board: game.Game) -> int:
        value, results, scores = 0, [], self.simulate(board)
        for action in scores:
            score = scores[action]
            score = sum(score) / len(score) if score else 0
            if score == value:
                results.append(action)
            elif score > value:
                value, results = score, [action]
        return game.choice(results)

    def simulate(self, board: game.Game) -> dict:
        step = 0
        result = dict(zip(game.ACTIONS, ([], [], [], [])))
        while step < self.step:
            copy = board.copy()
            action = game.choice(game.ACTIONS)
            if copy.move(action):
                step += 1
                copy.fill(action)
                while not copy.over:
                    game.Interface.check_quit()
                    copy.step(game.choice(game.ACTIONS))
                result[action].append(self.score(copy))
        return result

    @staticmethod
    def score(board: game.Game) -> int:
        return board.score
