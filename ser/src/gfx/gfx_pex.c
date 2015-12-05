#include "cmd.h"

int	gfx_pex(t_env *env, t_fd *fd)
{
	char	*to_send;

	asprintf(&to_send, "pex %d\n", fd->trantor.id);
	send_cmd_to_graphics(env, to_send);
	return 1;
}

