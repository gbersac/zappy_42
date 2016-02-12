from enum import Enum

# the map is indexed this way :
#  y
#  ^
# 2|
# 1|
# 0|------> x
#  0123456
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

    def on_left(self):
        if self == Direction.NONEDIR:
            return Direction.NONEDIR
        if self == Direction.NORTH:
            return Direction.WEST
        if self == Direction.EAST:
            return Direction.NORTH
        if self == Direction.SOUTH:
            return Direction.EAST
        if self == Direction.WEST:
            return Direction.SOUTH

    def on_right(self):
        if self == Direction.NONEDIR:
            return Direction.NONEDIR
        if self == Direction.NORTH:
            return Direction.EAST
        if self == Direction.EAST:
            return Direction.SOUTH
        if self == Direction.SOUTH:
            return Direction.WEST
        if self == Direction.WEST:
            return Direction.NORTH
