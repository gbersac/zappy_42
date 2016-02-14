from trantor import Trantor, Direction

class Env:
    def __init__(self, begin_info, socket, team):
        split = begin_info.split()
        if len(split) < 4:
            raise Exception('Invalid begin info: ' + begin_info)
        x = int(split[1])
        y = int(split[2])
        direction = Direction.from_str(split[3])
        num_str = split[4].partition('\\n')[0]
        self.available_connection = int(num_str)
        self.trantor = Trantor(x, y, direction, team)
        self.socket = socket
