# include "cmd.h"

int					ser_connect_nbr(t_env *env, t_fd *fd, char *cmd)
{
	char	*msg;

	asprintf(&msg, "%s %d", CMD_CONNECT_NBR,
			available_connexion(env, fd->trantor.team));
	send_cmd_to_client(fd, msg);
	return (0);
	cmd = NULL;
}
