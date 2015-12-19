#include "cmd.h"

int		gfx_sst(t_env *env, t_fd *fd, char *cmd)
{
	char	*to_send;

	env->map.time_d = ft_atoi(ft_strrchr(cmd, ' '));
	to_send = (char*)malloc(4);
	asprintf(&to_send, "sgt %d\n", env->map.time_d);
	send_cmd_to_client(fd, to_send);
	return (1);
}

