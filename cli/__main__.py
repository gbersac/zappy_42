import sys
import socket

from options import Options
from env import Env
from trantor import Trantor

def main_loop(env):
    while True:
        line = env.socket.recv(1024)
        if line == b'':
            print('Disconnected by server')
            sys.exit(0)
        else:
            print('Received message: ', line)

def client(opts):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        # procedure for client connection
        client.connect((opts.hostname, opts.port))
        line = client.recv(1024)
        client.send('PLAYER\n'.encode())
        line = client.recv(1024)
        begin_info = ('begin_info ' + opts.team + '\n').encode()
        client.send(begin_info)
        begin_info = str(client.recv(1024))

        # initialise environment
        try:
            env = Env(begin_info, client)
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
