class Resource(Enum):
    FOOD = 0
    LINEMATE = 1
    DERAUMERE = 2
    SIBUR = 3
    MENDIANE = 4
    PHIRAS = 5
    THYSTAME = 6
    EGG = 7
    PLAYER = 8

    def from_str(s):
        n = int(s[0])
        if n == 0:
            return FOOD
        if n == 1:
            return LINEMATE
        if n == 2:
            return DERAUMERE
        if n == 3:
            return SIBUR
        if n == 4:
            return MENDIANE
        if n == 5:
            return PHIRAS
        if n == 6:
            return THYSTAME
        if n == 7:
            return EGG
        if n == 8:
            return PLAYER

class Inventory(object):

    def __init__(self):
        super(Inventory, self).__init__()
        self.nb_food = 0
        self.nb_linemate = 0
        self.nb_deraumere = 0
        self.nb_sibur = 0
        self.nb_mendiane = 0
        self.nb_phiras = 0
        self.nb_thystame = 0

    def add(self, res, qt):
        if res == FOOD:
            self.nb_food += qt
        if res == LINEMATE:
            self.nb_linemate += qt
        if res == DERAUMERE:
            self.nb_deraumere += qt
        if res == SIBUR:
            self.nb_sibur += qt
        if res == MENDIANE:
            self.nb_mendiane += qt
        if res == PHIRAS:
            self.nb_phiras += qt
        if res == THYSTAME:
            self.nb_thystame += qt
        if res == EGG:
            self.nb_egg += qt
        if res == PLAYER:
            self.nb_player += qt
