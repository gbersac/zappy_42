#include "cmd.h"

int		gfx_bct_call(t_env *env, t_fd *fd, int x, int y)
{
	char		*to_send;
	t_list		*inventory;
	t_square	*sq;

	sq = get_square(env, x, y);
	inventory = sq->content;
	asprintf(&to_send, "bct %d %d %d %d %d %d %d %d %d", x, y,
			nb_res_in_inventory(FOOD, inventory),
			nb_res_in_inventory(LINEMATE, inventory),
			nb_res_in_inventory(DERAUMERE, inventory),
			nb_res_in_inventory(SIBUR, inventory),
			nb_res_in_inventory(MENDIANE, inventory),
			nb_res_in_inventory(PHIRAS, inventory),
			nb_res_in_inventory(THYSTAME, inventory));
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
