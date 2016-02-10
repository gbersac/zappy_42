from enum import Enum
from resource import Inventory, Resource

class State(Enum):
    """ The state of the trantor (the action he is working on) """
    SEARCH_FOOD = 0

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
        self.inventory = Inventory()
        self.voir = None
        self.state = None

    def update_state(self):
        self.state = State.SEARCH_FOOD

    def play(self):
        # define what the trantor should do
        self.update_state()

        # if the trantor is looking for food
        if self.state == State.SEARCH_FOOD:
            if self.voir == None:
                return 'voir'
            elif self.voir[0].nb_food >= 1:
                return 'prend nourriture'
            else:
                return 'avance'
        return ''

    def commit_cmd(self, cmd):
        if 'avance' in cmd:
            self.voir = None
        if 'gauche' in cmd:
            self.voir = None
        if 'droite' in cmd:
            self.voir = None
        if 'prend ' in cmd:
            res = Resource.from_str(cmd[6:])
            self.inventory.add(res, 1)
            self.voir = None

    def update_vision(self, cmd):
        cmd = cmd[cmd.index('{') + 1:]
        cmd = cmd[:cmd.index('}')]
        cases = cmd.split(', ')
        self.voir = []
        for case in cases:
            new = Inventory.from_str(case)
            self.voir.append(new)

    def interpret_cmd(self, prev_cmd, new_cmd):
        if 'ko' in new_cmd:
            print('cmd ' + prev_cmd + ' is ko')
            return self.play()
        if 'ok' in new_cmd:
            print('cmd ' + prev_cmd + ' is ok')
            self.commit_cmd(prev_cmd)
            return self.play()
        if 'voir' in new_cmd:
            self.update_vision(new_cmd)
            return ''
