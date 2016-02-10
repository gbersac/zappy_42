import re
from enum import Enum

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

    def from_int(s):
        n = int(s[0])
        if n == 0:
            return Resource.FOOD
        if n == 1:
            return Resource.LINEMATE
        if n == 2:
            return Resource.DERAUMERE
        if n == 3:
            return Resource.SIBUR
        if n == 4:
            return Resource.MENDIANE
        if n == 5:
            return Resource.PHIRAS
        if n == 6:
            return Resource.THYSTAME
        if n == 7:
            return Resource.EGG
        if n == 8:
            return Resource.PLAYER

    def from_str(s):
        if 'nourriture' in s:
            return Resource.FOOD
        if 'linemate' in s:
            return Resource.LINEMATE
        if 'deraumere' in s:
            return Resource.DERAUMERE
        if 'sibur' in s:
            return Resource.SIBUR
        if 'mendiane' in s:
            return Resource.MENDIANE
        if 'phiras' in s:
            return Resource.PHIRAS
        if 'thystame' in s:
            return Resource.THYSTAME
        if 'egg' in s:
            return Resource.EGG
        if 'player' in s:
            return Resource.PLAYER

    def __str__(self):
        if self.value == Resource.FOOD.value:
            return 'nourriture'
        return self.name.lower()

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

    def from_str(s):
        new = Inventory()
        m = re.match(
            r"([0-9]+) ([0-9]+) ([0-9]+) ([0-9]+) ([0-9]+) ([0-9]+) ([0-9]+)",
            s)
        new.nb_food = int(m.group(1))
        new.nb_linemate = int(m.group(2))
        new.nb_deraumere = int(m.group(3))
        new.nb_sibur = int(m.group(4))
        new.nb_mendiane = int(m.group(5))
        new.nb_phiras = int(m.group(6))
        new.nb_thystame = int(m.group(7))
        return new

    def from_nbrs(a, b, c, d, e, f, g):
        new = Inventory()
        new.nb_food = a
        new.nb_linemate = b
        new.nb_deraumere = c
        new.nb_sibur = d
        new.nb_mendiane = e
        new.nb_phiras = f
        new.nb_thystame = g
        return new

    def add(self, res, qt):
        if res == Resource.FOOD:
            self.nb_food += qt
        if res == Resource.LINEMATE:
            self.nb_linemate += qt
        if res == Resource.DERAUMERE:
            self.nb_deraumere += qt
        if res == Resource.SIBUR:
            self.nb_sibur += qt
        if res == Resource.MENDIANE:
            self.nb_mendiane += qt
        if res == Resource.PHIRAS:
            self.nb_phiras += qt
        if res == Resource.THYSTAME:
            self.nb_thystame += qt
        if res == Resource.EGG:
            self.nb_egg += qt
        if res == Resource.PLAYER:
            self.nb_player += qt

    def get_qt(self, res):
        if res == Resource.FOOD:
            return self.nb_food
        if res == Resource.LINEMATE:
            return self.nb_linemate
        if res == Resource.DERAUMERE:
            return self.nb_deraumere
        if res == Resource.SIBUR:
            return self.nb_sibur
        if res == Resource.MENDIANE:
            return self.nb_mendiane
        if res == Resource.PHIRAS:
            return self.nb_phiras
        if res == Resource.THYSTAME:
            return self.nb_thystame
        if res == Resource.EGG or res == Resource.PLAYER:
            return -1

    def __str__(self):
        return "foo {} lin {} der {} sib {} men {} phi {} thy {}".format(
                self.nb_food, self.nb_linemate, self.nb_deraumere,
                self.nb_sibur, self.nb_mendiane, self.nb_phiras,
                self.nb_thystame)
