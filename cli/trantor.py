import message
import random

from enum import Enum
from resource import Inventory, Resource
from incantation import Incantation
from message import Message, MessageList
from direction import Direction

class State(Enum):
    """ The state of the trantor (the action he is working on) """
    SEARCH_FOOD = 0
    SEARCH_STONE = 1
    START_INCANTATION = 2
    JOIN_TRANTOR_FOR_INCANTATION = 3

class Trantor:
    """ Trantorian is the player """

    def __init__(self, x, y, direction, team):
        self.x = x
        self.y = y
        self.direction = direction
        self.inventory = Inventory()
        self.voir = None
        self.state = None
        self.level = 1
        self.team = team
        self.messages = MessageList()

    def up_level(self):
        self.level += 1
        print('new level: ', self.level)
        if self.level == 6: # to delete
            exit(0)

    def action_to_perform(self):
        """ define next actio to perform by the trantor """
        if self.inventory.nb_food < 4:
            return State.SEARCH_FOOD
        if self.messages.someone_to_join(self.team, self.level) != None:
            return State.JOIN_TRANTOR_FOR_INCANTATION
        if Incantation.is_trantor_ready(self):
            return State.START_INCANTATION
        return State.SEARCH_STONE

    def action_to_find_resource(self, res):
        if self.voir == None:
            return 'voir'
        elif self.voir[0].get_qt(res) >= 1:
            return 'prend ' + str(res)
        elif self.voir[2].get_qt(res) >= 1:
            return 'avance'
        elif len(self.voir) > 7 and self.voir[6].get_qt(res) >= 1:
            return 'avance'
        else:
            action = random.randint(1, 3)
            if action == 1:
                return 'gauche'
            elif action == 2:
                return 'droite'
            else:
                return 'avance'

    def stone_to_find(self):
        if self.voir == None:
            return None
        resources = Incantation.missing_resources(self)
        if resources == []:
            return None

        # first take the resources we can have imediately
        for res in resources:
            if self.voir[0].get_qt(res) > 0:
                return res
        return resources[0]

    def enough_trantor_for_incantation(self):
        if self.level == 1:
            return True
        incant = Incantation.incantation_to_level_up(self.level)
        trant_ready = self.messages.nb_of_trantor_ready_for_incantation(
                self.team, self.level) + 1
        print('enough_trantor_for_incantation: ', incant.nb_player, '<=', trant_ready)
        return incant.nb_player <= trant_ready

    # every branch of play must return a command, if not the player freeze
    # because the server won't send back a ok or ko command => the main_loop
    # recv will block indefinitely
    def play(self):
        # define what the trantor should do
        self.state = self.action_to_perform()
        print('action_to_perform: ', self.state)

        if self.state == State.SEARCH_FOOD:
            return self.action_to_find_resource(Resource.FOOD)

        # check number of food hold by this trantor (the food will
        # be decreased by the server without the client being notifed, refresh
        # inventory to check current state of food)
        if random.randint(1, 100) == 1:
            return 'inventaire'

        if self.state == State.SEARCH_STONE:
            if self.voir == None:
                return 'voir'
            res = self.stone_to_find()
            # self.action_to_perform evaluate if we have all required resources
            # so res should not be none
            if res == None:
                return 'inventaire'
            return self.action_to_find_resource(res)

        if self.state == State.JOIN_TRANTOR_FOR_INCANTATION:
            msg = self.messages.someone_to_join(self.team, self.level)
            action = msg.action_to_join_sender()
            if action == None:
                return message.message_to_cmd(
                        message.incantation_ready(self.team, self.level))
            else:
                return action

        if self.state == State.START_INCANTATION:
            if self.enough_trantor_for_incantation():
                return 'incantation'
            return message.message_to_cmd(
                    message.incantation_call(self.team, self.level))

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
            return None
        if 'incantation' in cmd[:11]:
            self.up_level()
            return 'inventaire'

    def update_vision(self, cmd):
        cmd = cmd[cmd.index('{') + 1:]
        cmd = cmd[:cmd.index('}')]
        cases = cmd.split(', ')
        self.voir = []
        for case in cases:
            new = Inventory.from_str(case)
            self.voir.append(new)

    def update_inventaire(self, cmd):
        cmd = cmd[11:]
        print('#' + cmd + '#')
        self.inventory = Inventory.from_str(cmd)

    def interpret_cmd(self, prev_cmd, new_cmd):
        if 'ko' in new_cmd[:2]:
            print('cmd ' + prev_cmd + ' is ko')
            return self.play()
        if 'ok' in new_cmd[:2]:
            print('cmd ' + prev_cmd + ' is ok')
            cmd = self.commit_cmd(prev_cmd)
            if cmd != None:
                return cmd
            else:
                return self.play()
        if 'voir ' in new_cmd[:6]:
            self.update_vision(new_cmd)
            return None
        if 'inventaire ' in new_cmd[:11]:
            self.update_inventaire(new_cmd)
            return None
        if 'message ' in new_cmd[:9]:
            self.messages.add_msg(new_cmd)
            return None
        if 'suc' in new_cmd[:3]:
            print('unknow command: ' + prev_cmd)
            return None
        if 'incantation' in new_cmd[:11]:
            self.up_level()
        if 'relaunch' in new_cmd[:9]:
            print('cmd ' + prev_cmd + ' is ok [relaunch]')
            cmd = self.commit_cmd(prev_cmd)
            if cmd != None:
                return cmd
            else:
                return self.play()
