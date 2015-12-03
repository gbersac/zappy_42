#!/usr/bin/python
from subprocess import Popen, PIPE, STDOUT
import time
import fcntl
import os
import sys
import thread
import threading
import cmd
import shlex
# from threading  import Thread

# try:
#     from Queue import Queue, Empty
# except ImportError:
#     from queue import Queue, Empty  # python 3.x

ON_POSIX = 'posix' in sys.builtin_module_names

DEFAULT_PORT = 4242
NB_TEAMS = 2
PLAYER_IN_TEAM = 3
WORLD_WIDTH = 10
WORLD_HEIGHT = 10
ALLOWED_CLIENT_BEGIN = 5
TIME_DIVISOR = 5
TEAM_PREFIX = 't'

# the port to use for connecting the processes
port = DEFAULT_PORT
if len(sys.argv) >= 2:
	port = int(sys.argv[1])

# number of process created
nb_process = 0

# list of all the processes lauched in this program
progs = []

# mutex for thread
progs_lock = threading.Lock()

def teams_name():
	to_return = []
	for x in xrange(0, NB_TEAMS):
		to_return.append(TEAM_PREFIX + str(x))
	return to_return

# list of team name
teams = teams_name()

class Process(object):
	"""A zappy Process"""
	def __init__(self):
		pass

	def init(self, cmd):
		global nb_process
		args = shlex.split(cmd)
		self.p = Popen(args, stdout=PIPE, stdin=PIPE, stderr=STDOUT)
		self.id = nb_process
		nb_process += 1

	def send_cmd(self, cmd):
		self.p.stdin.write(cmd)

	def read(self):
		output = self.p.stdout
		fd = output.fileno()
		fl = fcntl.fcntl(fd, fcntl.F_GETFL)
		fcntl.fcntl(fd, fcntl.F_SETFL, fl | os.O_NONBLOCK)
		try:
			s = output.readline()
			while s != '':
				print("[%d] %s" % (self.id, s[:-1]))
				s = output.readline()
		except:
		    pass

def enqueue_output(out, queue):
    for line in iter(out.readline, b''):
        queue.put(line)
    out.close()

class Player(Process):
	"""A Player is a zappy player client"""

	def __init__(self, team):
		super(Process, self).__init__()
		cmd = ['./client', '-p', str(port), '-n', team, '-h', '127.0.0.1']
		self.init(' '.join(cmd))
		self.team = team

class Server(Process):
	"""A Server is a zappy server"""

	def __init__(self):
		super(Process, self).__init__()
		cmd = ['./serveur',
				'-p', str(port),
				'-x', str(WORLD_WIDTH),
				'-y', str(WORLD_HEIGHT),
				'-c', str(ALLOWED_CLIENT_BEGIN),
				'-t', str(TIME_DIVISOR),
				'-n', ' '.join(teams)]
		self.init(' '.join(cmd))

##################################### MAIN #####################################
# create processes
serveur = Server()
progs.append(serveur)
print '[0] server on port ', port
for team in teams:
	for x in xrange(0, PLAYER_IN_TEAM):
		player = Player(team)
		print '[%d] player in team %s' % (player.id, team)
		progs.append(player)
print ''

# read outputs of all the progs
def read_progs():
	global progs_lock, progs
	while True:
		for prog in progs:
			progs_lock.acquire(True)
			prog.read()
			progs_lock.release()
		time.sleep(0.01)

try:
	thr = threading.Thread(target = read_progs)
	thr.daemon = True
	thr.start()
except Exception as inst:
	print 'Cant open thread: ', inst
except:
   print "Error: unable to start thread"
time.sleep(0.5)

# read loop eval
class CommandInterface(cmd.Cmd):
	"""Command line argument utilities."""

	prompt = '>>> '

	def do_s(self, line):
		global progs, progs_lock
		id_prog = int(line[0])
		cmd = line[3:]
		progs_lock.acquire(True)
		prog = progs[id_prog]
		prog.send_cmd(cmd)
		progs_lock.release()

CommandInterface().cmdloop()
