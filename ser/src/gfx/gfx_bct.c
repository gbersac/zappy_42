#include "cmd.h"

int		gfx_bct(t_env *env, t_fd *fd, char *cmd)
{
	char	*to_send;

	to_send = (char*)malloc(4);
	memcpy(to_send, "pex ", 4);
	send_cmd_to_client(fd, to_send);
	return 1;
env = NULL; cmd = NULL;
}

