#include "cmd.h"

int		gfx_mct(t_env *env, t_fd *fd, char *cmd)
{
	int		x;
	int		y;

	y = 0;
	while (y < env->map.height)
	{
		x = 0;
		while (x < env->map.width)
		{
			gfx_bct_call(env, fd, x, y);
			++x;
		}
		++y;
	}
	return 1;
	cmd = NULL;
}

