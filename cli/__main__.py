import sys
import socket

from options import Options
from env import Env
from trantor import Trantor

def main_loop(env):
    prev_cmd = env.trantor.play()
    env.socket.send((prev_cmd + '\n').encode())
    while True:
        print('\n###New Loop')
        recv = env.socket.recv(1024).decode('utf-8')
        if recv == '':
            print('Disconnected by server')
            sys.exit(0)
        lines = recv.split('\n')
        for line in lines:
            if line == '':
                continue
            print('Received message: #' + line + '#')
            new_cmd = env.trantor.interpret_cmd(prev_cmd, line)
            if new_cmd != '' and new_cmd != None:
                env.trantor.messages.clear()
                print("Send: " + new_cmd)
                env.socket.send((new_cmd + '\n').encode())
                prev_cmd = new_cmd

def client(opts):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        # procedure for socket connection
        sock.connect((opts.hostname, opts.port))
        line = sock.recv(1024)
        sock.send('PLAYER\n'.encode())
        line = sock.recv(1024)
        begin_info = ('begin_info ' + opts.team + '\n').encode()
        sock.send(begin_info)
        begin_info = str(sock.recv(1024))

        # initialise environment
        try:
            env = Env(begin_info, sock)
        except Exception as inst :
            print(type(inst), ': ', inst)
            sys.exit(0)

        # read commands
        main_loop(env)
    except ConnectionRefusedError:
        print('Could not connect to ' + opts.hostname + ':' + str(opts.port))
        sys.exit(0)

def main():
    opts = Options()
    print('Equipe: ', opts.team, ', Hostname: ', opts.hostname, ', Port: ', opts.port)
    client(opts)

if __name__ == "__main__":
    main()
