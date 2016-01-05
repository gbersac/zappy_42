#include "cmd.h"

int		gfx_msz(t_env *env, t_fd *fd, char *cmd)
{
	char	*to_send;

	printf("msz called\n");

	asprintf(&to_send, "msz %d %d\n", env->map.width, env->map.height);
	printf("\e[0;31mto->[gfx]\e[0m %s\n", to_send);
	send_cmd_to_client(fd, to_send);
	free(to_send);
	return (1);
	cmd = NULL;
}
