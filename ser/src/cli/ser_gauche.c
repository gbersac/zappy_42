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
	add_differed_msg(env, CMD_GAUCHE_TIME, fd, MSG_OK);
	i = 0;
	asprintf(&to_send, "ppo %d\n", trantor->id);
	send_cmd_to_graphics(env, to_send);
	free(to_send);
	env = NULL;
	cmd = NULL;
	return (0);
}
