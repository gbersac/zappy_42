#include "cmd.h"

int		gfx_plv(t_env *env, t_fd *fd, char *cmd)
{
	char			*to_send;
	int				num;
	t_trantorian	*trantor;

	printf("plv called\n");
	sscanf(cmd, "plv %d\n", &num);
	trantor = &env->fds[num].trantor;
	if (env->fds[num].type != FD_CLIENT)
	{
		send_cmd_to_client(fd, MSG_KO);
		return (0);
	}
	asprintf(&to_send, "plv %d %d",
			num,
			trantor->level);
	send_cmd_to_client(fd, to_send);
	free(to_send);
	return (1);
}
