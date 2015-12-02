#include "cmd.h"

int		gfx_bct_call(t_env *env, t_fd *fd, int x, int y)
{
	char	*to_send;

	asprintf(&to_send, "bct %d %d %s", x, y, square_to_str(env, x, y));
	printf("%s\n", to_send);
	send_cmd_to_client(fd, to_send);
	return 1;
}

int		gfx_bct(t_env *env, t_fd *fd, char *cmd)
{
	int		x;
	int		y;

	sscanf(cmd, "bct %d %d\n", &x, &y);
	gfx_bct_call(env, fd, x, y);
	return 1;
}
