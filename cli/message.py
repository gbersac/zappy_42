import re
import math

from direction import Direction

# All the messages should began by the team of the sender

def incantation_call(team, level):
    return ('{} ready to launch incantation for level {}'.
            format(team, str(level)))

def incantation_ready(team, level):
    return ('{} i am here for incantation level {}'.
            format(team, str(level)))

def message_to_cmd(msg):
    """ Change a simple message to a broadcast command. """
    return 'broadcast ' + msg

def trim_team(msg):
    split = msg.split(' ', 1)
    return split[1]

msg_reg = "message ([0-9]+) ([0-9]+) ([0-9]+) ([0-9]+) ([0-9]+) ([a-zA-Z0-9_]+) (.+)"

class Message:
    def __init__(self, s):
        m = re.match(msg_reg, s)
        if m == None:
            print('Error invalid Message: #' + s + '#')
            return
        self.dest_x = int(m.group(1))
        self.dest_y = int(m.group(2))
        self.self_x = int(m.group(3))
        self.self_y = int(m.group(4))
        self.self_direction = Direction.from_str(m.group(5))
        self.team = m.group(6)
        self.message = m.group(7)
        print('register message:', self.message)

    def action_to_join_sender(self):
        # calc diffs
        diff_x = math.fabs(self.self_x - self.dest_x)
        diff_y = math.fabs(self.self_y - self.dest_y)
        if diff_x == 0 and diff_y == 0: # if the user is on the case
            return None

        # choose direction to go
        dir_to_go = None
        if (diff_x != 0 and diff_x < diff_y) or diff_y == 0:
            if self.self_x > self.dest_x:
                dir_to_go = Direction.WEST
            elif self.self_x < self.dest_x:
                dir_to_go = Direction.EAST
        else:
            if self.self_y > self.dest_y:
                dir_to_go = Direction.SOUTH
            elif self.self_y < self.dest_y:
                dir_to_go = Direction.NORTH

        # compare dir_to_go and user direction
        if dir_to_go == self.self_direction:
            return 'avance'
        if dir_to_go == self.self_direction.on_left():
            return 'gauche'
        else:
            return 'droite'

        def __eq__(self, other):
            print(self.message, ' == ', other.message)
            return (isinstance(other, self.__class__)
                and self.message == other.message
                and self.team == self.team) or (
                isinstance(myvar, str) and self.message == other)

        def __ne__(self, other):
            return not self.__eq__(other)

# The messageList is refreshed every time a trantor launch a new incantation
# see main_loop
class MessageList:
    def __init__(self):
        self.list = []

    def add_msg(self, s):
        msg = Message(s)
        if msg == None or not hasattr(msg, 'message'):
            print('Error parsing msg:', s)
            return
        self.list.append(msg)

    def clear(self):
        self.list = []

    # check if the messages are in the same team
    def nb_same_msg(self, team, s):
        to_return = 0
        print('nb_same_msg list length', len(self.list))
        for msg in self.list:
            if s != None and msg.message == s:
                to_return += 1
        return to_return

    def someone_to_join(self, team, level):
        s = incantation_call(team, level)
        s = trim_team(s)
        for msg in self.list:
            if s != None and msg.message == s:
                return msg
        return None

    def nb_of_trantor_ready_for_incantation(self, team, level):
        s = incantation_ready(team, level)
        s = trim_team(s)
        return self.nb_same_msg(team, s)
