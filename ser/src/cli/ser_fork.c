# include "cmd.h"
# include <unistd.h>

int			ser_fork(t_env *env, t_fd *fd, char *cmd)
{
	t_egg	*new_egg;
	char	*msg;

	cmd = NULL;
	new_egg = (t_egg*)malloc(sizeof(t_egg));
	new_egg->countdown = -1;
	printf("ser_fork team %s\n", fd->trantor.team);
	new_egg->team = fd->trantor.team;
	new_egg->x = fd->trantor.pos_x;
	new_egg->y = fd->trantor.pos_y;
	new_egg->id_trantor = fd->fd;
	fd->trantor.laying = 1;
	ft_listpushback(&env->egg, new_egg);
	add_differed_msg(env, CMD_FORK_TIME, fd, MSG_OK);
	asprintf(&msg, "pfk %d", fd->trantor.id);
	send_cmd_to_graphics(env, msg);
	free(msg);
	return (0);
}
