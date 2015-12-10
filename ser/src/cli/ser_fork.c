# include "cmd.h"

int			ser_fork(t_env *env, t_fd *fd, char *cmd)
{
	t_egg	new_egg;

	cmd = NULL;
	new_egg.countdown = (42 / env->map.time_d);
	new_egg.team = fd->trantor.team;
	new_egg.x = fd->trantor.pos_x;
	new_egg.y = fd->trantor.pos_y;
	ft_listpushback(&env->egg, &new_egg);
	return (0);
}
