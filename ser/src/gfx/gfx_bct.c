#include "cmd.h"

int		gfx_bct_call(t_env *env, t_fd *fd, int x, int y)
{
	char		*to_send;
	t_inventory	*inventory;
	t_square	*sq;

	sq = get_square(env, x, y);
	inventory = &sq->content;
	asprintf(&to_send, "bct %d %d %d %d %d %d %d %d %d", x, y,
			nb_res_in_inventory(inventory, FOOD),
			nb_res_in_inventory(inventory, LINEMATE),
			nb_res_in_inventory(inventory, DERAUMERE),
			nb_res_in_inventory(inventory, SIBUR),
			nb_res_in_inventory(inventory, MENDIANE),
			nb_res_in_inventory(inventory, PHIRAS),
			nb_res_in_inventory(inventory, THYSTAME));
	send_cmd_to_client(fd, to_send);
	return (1);
}

int		gfx_bct(t_env *env, t_fd *fd, char *cmd)
{
	int		x;
	int		y;

	sscanf(cmd, "bct %d %d\n", &x, &y);
	gfx_bct_call(env, fd, x, y);
	return (1);
}
