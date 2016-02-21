import sys
import socket

from options import Options
from env import Env
from trantor import Trantor

def main_loop(env):
    prev_cmd = env.trantor.play()
    env.socket.send((prev_cmd + '\n').encode())
    buf = ''
    while True:
        recv = env.socket.recv(1024).decode('utf-8')
        if recv == '':
            print('Disconnected by server')
            sys.exit(0)
        recv = buf + recv
        recv = recv.replace('\x00', '')
        lines = recv.split('\n')
        for i in range(len(lines) - 1):
            line = lines[i]
            if line == '' or line == '\x00':
                continue
            new_cmd = env.trantor.interpret_cmd(prev_cmd, line)
            if new_cmd != '' and new_cmd != None:
                env.trantor.messages.clear()
                env.socket.send((new_cmd + '\n').encode())
                prev_cmd = new_cmd
        if lines[-1] != '\x00':
            buf = lines[-1]
        else:
            buf = ''

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
            env = Env(begin_info, sock, opts.team)
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
