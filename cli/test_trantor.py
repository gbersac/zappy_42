import unittest
import message

from trantor import Trantor, State
from message import Message, MessageList
from resource import Inventory

class TestTrantor(unittest.TestCase):

    def new_trantor(level, inv):
        new = Trantor(0, 0, 0)
        new.level = level
        new.inventory = inv
        return new

    def test_action_to_perform(self):
        trantor = TestTrantor.new_trantor(2, Inventory.from_nbrs(5, 5, 5, 5, 5, 5, 5))
        trantor.messages.add_msg('message 0 0 0 0 0 ' + message.incantation_call(2)[10:])
        action = trantor.action_to_perform()
        self.assertTrue(action == State.JOIN_TRANTOR_FOR_INCANTATION)

class TestMessage(unittest.TestCase):

    def test_message(self):
        msg = Message("message 0 4 3 9 2 ready to launch incantation for level 2")
        self.assertTrue(msg.message != None)
        msg = Message("message 1 7 9 7 4 ready to launch incantation for level 2")
        self.assertTrue(msg.message != None)

if __name__ == '__main__':
    unittest.main()
