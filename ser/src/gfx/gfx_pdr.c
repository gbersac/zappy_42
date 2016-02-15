#include "cmd.h"

int			gfx_pdr(t_env *env, int trantor_id, int ressource_number)
{
	char	*to_send;

	asprintf(&to_send, "pdr %d %d \n", trantor_id, ressource_number);
	send_cmd_to_graphics(env, to_send);
	return 1;
}

