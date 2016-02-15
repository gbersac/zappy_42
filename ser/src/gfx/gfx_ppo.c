#include "cmd.h"

int		gfx_ppo(t_env *env, t_fd *fd, char *cmd)
{
	char			*to_send;
	int				num;
	t_trantorian	*trantor;

//	printf("ppo called\n");
	sscanf(cmd, "ppo %d\n", &num);
	trantor = &env->fds[num].trantor;
	if (env->fds[num].type != FD_CLIENT)
	{
		send_cmd_to_client(fd, MSG_KO);
		return (0);
	}
	asprintf(&to_send, "ppo %d %d %d %d",
			num,
			trantor->pos_x,
			trantor->pos_y,
			direction_to_nbr(trantor->direction));
	send_cmd_to_client(fd, to_send);
	free(to_send);
	return (1);
}
