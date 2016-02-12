import unittest

from direction import Direction
from message import Message

class TestDirection(unittest.TestCase):

    def t_one(self, dest_x, dest_y, self_x, self_y, self_dir, expected):
        print("\nFor dest_x {} dest_y {} self_x {} self_y {} self_dir {}".format(
            dest_x, dest_y, self_x, self_y, self_dir.name
        ))
        s = "message {} {} {} {} {} aaa\\".format(
            dest_x, dest_y, self_x, self_y, self_dir.value
        )
        m = Message(s)
        action = m.action_to_join_sender()
        print("Result {}, expected: {}".format(action, expected))
        self.assertTrue(expected == action)

    def test_action_to_join_sender(self):
        self.t_one(2, 2, 2, 2, Direction.NORTH, None)
        self.t_one(2, 2, 2, 5, Direction.SOUTH, 'avance')
        self.t_one(2, 2, 2, 5, Direction.WEST, 'gauche')
        self.t_one(2, 5, 4, 2, Direction.WEST, 'avance')
        self.t_one(2, 5, 4, 2, Direction.SOUTH, 'droite')
        #          3  5  7  5 4
        self.t_one(3, 5, 7, 5, Direction.SOUTH, 'droite')
        self.t_one(3, 5, 7, 5, Direction.WEST, 'avance')

if __name__ == '__main__':
    unittest.main()
