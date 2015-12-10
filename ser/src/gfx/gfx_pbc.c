#include "cmd.h"

int	gfx_pbc(t_env *env, t_fd *fd, char *msg)
{
	char	*to_send;

	asprintf(&to_send, "pbc %d %s",
			fd->trantor.id,
			msg);
	send_cmd_to_graphics(env, to_send);
	free(to_send);
	return (1);
}

