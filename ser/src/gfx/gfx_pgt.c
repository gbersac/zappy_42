#include "cmd.h"

int			gfx_pgt(t_env *env, int trantor_id, int ressource_number)
{
	char	*to_send;

	asprintf(&to_send, "pgt %d %d \n", trantor_id, ressource_number);
	printf("\e[0;31mto->[gfx]\e[0m %s\n", to_send);
	send_cmd_to_graphics(env, to_send);
	return 1;
}

