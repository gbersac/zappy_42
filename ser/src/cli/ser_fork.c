# include "cmd.h"
# include <unistd.h>

void		fork_player_egg(t_env *env)
{
	t_trantorian trant;

	init_trantorian(&trant, -1);
	trant.direction = rand() % 4;
	trant.laying = 1;
	printf("trant.id : %d\n", trant.id);
	printf("trant.team : %s\n", trant.team);
	ft_listpushback(&env->trant, &trant);
}

int			ser_fork(t_env *env, t_fd *fd, char *cmd)
{
	t_egg	*new_egg;

	cmd = NULL;
	new_egg = (t_egg*)malloc(sizeof(t_egg));
	new_egg->countdown = 0;
	// new_egg.team = fd->trantor.team;
	new_egg->team = NULL;
	new_egg->x = fd->trantor.pos_x;
	new_egg->y = fd->trantor.pos_y;
	new_egg->id = fd->fd;
	fd->trantor.laying = 1;
	printf("trantor laying status : %d\n", fd->trantor.laying);
	ft_listpushback(&env->egg, new_egg);
	return (0);
}
