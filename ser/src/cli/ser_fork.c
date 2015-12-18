# include "cmd.h"
# include <unistd.h>

int			ser_fork(t_env *env, t_fd *fd, char *cmd)
{
	t_egg	*new_egg;

	cmd = NULL;
	new_egg = (t_egg*)malloc(sizeof(t_egg));
	new_egg->countdown = 0;
	new_egg->team = fd->trantor.team;
	new_egg->x = fd->trantor.pos_x;
	new_egg->y = fd->trantor.pos_y;
	new_egg->id = fd->fd;
	fd->trantor.laying = 1;
	ft_listpushback(&env->egg, new_egg);
	printf("ser_fork number of eggs %d\n", ft_listcnt(env->egg));
	return (0);
}
