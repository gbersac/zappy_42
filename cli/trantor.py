from enum import Enum
from resource import Inventory, Resource
from incantation import Incantation

class State(Enum):
    """ The state of the trantor (the action he is working on) """
    SEARCH_FOOD = 0
    SEARCH_STONE = 1
    START_INCANTATION = 2

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
        self.level = 1

    def action_to_perform(self):
        """ define next actio to perform by the trantor """
        print(self.inventory)
        if self.inventory.nb_food < 4:
            return State.SEARCH_FOOD

        if Incantation.is_trantor_ready(self):
            return State.START_INCANTATION

        return State.SEARCH_STONE

    def action_to_find_resource(self, res):
        if self.voir == None:
            return 'voir'
        elif self.voir[0].get_qt(res) >= 1:
            return 'prend ' + str(res)
        else:
            return 'avance'

    def stone_to_find(self):
        return Resource.LINEMATE

    def play(self):
        # define what the trantor should do
        self.state = self.action_to_perform()
        print('action_to_perform: ', self.state)

        # if the trantor is looking for food
        if self.state == State.SEARCH_FOOD:
            return self.action_to_find_resource(Resource.FOOD)

        # if the trantor is looking for the stones to trigger invocation
        if self.state == State.SEARCH_STONE:
            res = self.stone_to_find()
            return self.action_to_find_resource(Resource.LINEMATE)

        # if it is time to start an incantation
        if self.state == State.START_INCANTATION:
            print('START_INCANTATION')
            return 'incantation'

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
            return 'inventaire'
        if 'incantation ' in cmd:
            self.level += 1
            return 'inventaire'

    def update_vision(self, cmd):
        cmd = cmd[cmd.index('{') + 1:]
        cmd = cmd[:cmd.index('}')]
        cases = cmd.split(', ')
        self.voir = []
        for case in cases:
            new = Inventory.from_str(case)
            self.voir.append(new)

    def interpret_cmd(self, prev_cmd, new_cmd):
        if 'ko' in new_cmd[2:]:
            print('cmd ' + prev_cmd + ' is ko')
            return self.play()
        if 'ok' in new_cmd[2:]:
            print('cmd ' + prev_cmd + ' is ok')
            cmd = self.commit_cmd(prev_cmd)
            if cmd != None:
                return cmd
            else:
                return self.play()
        if 'voir' in new_cmd:
            self.update_vision(new_cmd)
            return ''
