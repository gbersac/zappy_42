#include "cmd.h"

int	gfx_pie(t_env *env)
{
	char	*to_send;

	to_send = (char*)malloc(4);
	memcpy(to_send, "pie ", 4);
	send_cmd_to_graphics(env, to_send);
	return 1;
}
