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
	i = 0;
	to_send = gfx_ppo_str(trantor);
	send_cmd_to_graphics(env, to_send);
	free(to_send);
	env = NULL;
	cmd = NULL;
	return (0);
}
