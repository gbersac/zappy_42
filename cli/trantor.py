from enum import Enum

class Direction(Enum):
    NONEDIR = 0
    NORTH = 1
    EAST = 2
    SOUTH = 3
    WEST = 4

    def from_str(s):
        n = int(s[0])
        if n == 0:
            return Direction.NONEDIR
        if n == 1:
            return Direction.NORTH
        if n == 2:
            return Direction.EAST
        if n == 3:
            return Direction.SOUTH
        if n == 4:
            return Direction.WEST
        return Direction.NONEDIR

class Trantor:
    """ Trantorian is the player """

    def __init__(self, x, y, direction):
        self.x = x
        self.y = y
        self.direction = direction

    def play(self):
        return 'avance\n'

    def commit_cmd(self, cmd):
        pass

    def interpret_cmd(self, prev_cmd, new_cmd):
        if 'ko' in new_cmd:
            return self.play()
        if 'ok' in new_cmd:
            self.commit_cmd(prev_cmd)
            return self.play()
        if 'voir' in new_cmd:
            update_vision(new_cmd)
            return self.play()
