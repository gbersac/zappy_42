# include "cmd.h"

int			ser_gauche(t_env *env, t_fd *fd, char *cmd)
{
	t_trantorian	*trantor;

	trantor = &(fd->trantor);
	switch (trantor->direction)
	{
		case LEFT:
			trantor->direction = DOWN;
			break ;
		case RIGHT:
			trantor->direction = UP;
			break ;
		case UP:
			trantor->direction = LEFT;
			break ;
		case DOWN:
			trantor->direction = RIGHT;
			break ;
	}
	send_cmd_to_client(fd, MSG_OK);
	env = NULL;
	cmd = NULL;
	return (0);
}
