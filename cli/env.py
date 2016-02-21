from trantor import Trantor, Direction

class Env:
    def __init__(self, begin_info, socket, team):
        split = begin_info.split()
        if len(split) < 2:
            print("Error: connexion to server refused")
        self.trantor = Trantor(team)
        self.socket = socket
