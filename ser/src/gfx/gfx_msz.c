#include "cmd.h"

int		gfx_msz(t_env *env, t_fd *fd, char *cmd)
{
	char	*to_send;

	asprintf(&to_send, "msz %d %d\n", env->map.width, env->map.height);
	send_cmd_to_client(fd, to_send);
	return 1;
	cmd = NULL;
}
