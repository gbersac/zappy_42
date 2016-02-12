import re
import math

from direction import Direction

def incantation_call(level):
    return 'broadcast ready to launch incantation for level ' + str(level)

def incantation_ready(level):
    return 'broadcast i am here for incantation level ' + str(level)

class Message:
	def __init__(self, s):
		s = str(s)
		print(s)
		m = re.match(
			r"message ([0-9]+) ([0-9]+) ([0-9]+) ([0-9]+) ([0-9]+) (.+)",
			s)
		if m == None:
			print('Error invalid Message: #' + s + '#')
			return
		self.dest_x = int(m.group(1))
		self.dest_y = int(m.group(2))
		self.self_x = int(m.group(3))
		self.self_y = int(m.group(4))
		self.self_direction = Direction.from_str(m.group(5))
		self.message = m.group(6)

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

# The messageList is refreshed every time a trantor launch a new incantation
# see main_loop
class MessageList:
	def __init__(self):
		self.list = []

	def add_msg(self, s):
		msg = Message(s)
		if msg == None:
			print('Error parsing msg:', s)
			return
		self.list.append(msg)

	def clear(self):
		self.list = []

	def nb_same_msg(self, s):
		to_return = 0
		print('nb_same_msg')
		for msg in self.list:
			print(msg.message, '==', s)
			if hasattr(msg, 'message') and msg.message == s:
				to_return += 1
		return to_return

	def someone_to_join(self, level):
		s = incantation_call(level)
		for msg in self.list:
			if hasattr(msg, 'message') and msg.message == s[10:]:
				return msg
		return None

	def nb_of_trantor_ready_for_incantation(self, level):
		s = incantation_ready(level)[10:]
		print('nb_of_trantor_ready_for_incantation #' + s + '# total', self.nb_same_msg(s))
		return self.nb_same_msg(s)
