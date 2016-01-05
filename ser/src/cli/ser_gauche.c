# include "cmd.h"

int			ser_gauche(t_env *env, t_fd *fd, char *cmd)
{
	t_trantorian	*trantor;
	int				i;
	char			*to_send;

	trantor = &(fd->trantor);
	switch (trantor->direction)
	{
		case NORTH:
			trantor->direction = WEST;
			break ;
		case EAST:
			trantor->direction = NORTH;
			break ;
		case SOUTH:
			trantor->direction = EAST;
			break ;
		case WEST:
			trantor->direction = SOUTH;
			break;
		default:
			break;
	}
	send_cmd_to_client(fd, MSG_OK);
	i = 0;
	asprintf(&to_send, "ppo %d\n", trantor->id);
	while (i < env->maxfd)
	{
		if (env->fds[i].type == FD_GRAPHIC)
			gfx_ppo(env, &env->fds[i], to_send);
		i++;
	}
	free(to_send);
	env = NULL;
	cmd = NULL;
	return (0);
}
