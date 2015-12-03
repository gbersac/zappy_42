#include "cmd.h"

int		gfx_pin(t_env *env, t_fd *fd, char *cmd)
{
	char			*to_send;
	int				num;
	t_trantorian	*trantor;

	sscanf(cmd, "pin %d\n", &num);
	trantor = &env->fds[num].trantor;
	if (env->fds[num].type != FD_CLIENT)
	{
		send_cmd_to_client(fd, MSG_KO);
		return (0);
	}
	asprintf(&to_send, "pin %d %d %d %s",
			num,
			trantor->pos_x,
			trantor->pos_y,
			resources_to_str(trantor->inventory));
	send_cmd_to_client(fd, to_send);
	free(to_send);
	return (1);
}
