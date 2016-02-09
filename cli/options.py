import sys
import argparse

# Usage: ./client -n <team> -p <port> [-h <hostname>]
# -n nom d'equipe
# -p port
# -h nom de la machine par defaut c'est le localhost

class Options:
    """ A class containing the options selected by the user """

    def get_parser():
        parser = argparse.ArgumentParser(
                description='Player for the zappy',
                add_help=False)
        parser.add_argument('-n', help='nom d\'equipe', metavar='equipe',
                nargs=1, required=True)
        parser.add_argument('-p', help='port number', metavar='port', nargs=1,
                required=True, type=int)
        parser.add_argument('-h', help='host name default localhost',
                metavar='hostname', nargs=1, default=['127.0.0.1'])
        return parser

    def __init__(self):
        parser = Options.get_parser()
        parsed_args = parser.parse_args(sys.argv[1:])
        self.team = parsed_args.n[0]
        self.hostname = parsed_args.h[0]
        self.port = parsed_args.p[0]

