#include "cmd.h"

void		send_msg_to_all_excpt_src(t_env *env, t_fd *fd, char *msg)
{
	int				i;
	char			*str;
	t_trantorian	*trant;

	i = 0;
	str = NULL;
	trant = &fd->trantor;
/*	asprintf(&str, "%s %d %d %d %s %s",
			CMD_BROADCAST,
			rand() % 8 + 1,
			trant->pos_x,
			trant->pos_y,
			trant->team,
			msg);*/
	asprintf(&str, "%s %d %d %d %s %s",
			CMD_BROADCAST,
			get_sound_dir(fd->trantor, *trant, env->map),
			trant->pos_x,
			trant->pos_y,
			trant->team,
			msg);
	while (i < env->maxfd)
	{
		if (env->fds[i].type == FD_CLIENT && env->fds[i].fd != fd->fd)
			send_cmd_to_client(&env->fds[i], str);
		i++;
	}
	free(str);
}

int			ser_broadcast(t_env *env, t_fd *fd, char *cmd)
{
	char	*msg;

	msg = cmd + strlen(CMD_BROADCAST) + 1;
	send_msg_to_all_excpt_src(env, fd, msg);
	gfx_pbc(env, fd, msg);
	send_cmd_to_client(fd, MSG_OK);
	return (0);
}
