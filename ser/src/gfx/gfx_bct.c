#include "cmd.h"

char	*gfx_bct_str(t_env *env, int x, int y)
{
	t_square	*sq;
	char		*to_send;
	char		*inventory_str;

	sq = get_square(env, x, y);
	inventory_str = inventory_to_str(&sq->content);
	asprintf(&to_send, "bct %d %d %s",
			x, y,
			inventory_str);
	return (to_send);
}

int		gfx_bct_call(t_env *env, t_fd *fd, int x, int y)
{
	char		*to_send;
<<<<<<< HEAD

	to_send = gfx_bct_str(env, x, y);
	send_cmd_to_client(fd, to_send);
	free(to_send);
=======
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

	printf("%s\n", to_send);
	send_cmd_to_client(fd, to_send);
>>>>>>> bd513116d8b551ceee607b7df53a94940d50e019
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
