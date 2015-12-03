#include "cmd.h"

static char	*str_inventory(char *buf, t_list *inventory)
{
	sprintf(buf, "%d %d %d %d %d %d %d",
			nb_res_in_inventory(LINEMATE, inventory),
			nb_res_in_inventory(DERAUMERE, inventory),
			nb_res_in_inventory(SIBUR, inventory),
			nb_res_in_inventory(MENDIANE, inventory),
			nb_res_in_inventory(PHIRAS, inventory),
			nb_res_in_inventory(THYSTAME, inventory),
			nb_res_in_inventory(FOOD, inventory));
	return (buf);
}

int			gfx_pin(t_env *env, t_fd *fd, char *cmd)
{
	char			*to_send;
	int				num;
	t_trantorian	*trantor;
	char			buf[1024];

	sscanf(cmd, "pin %d\n", &num);
	trantor = &env->fds[num].trantor;
	if (env->fds[num].type != FD_CLIENT)
	{
		send_cmd_to_client(fd, MSG_KO);
		return (0);
	}
	asprintf(&to_send, "pin %d %d %d %s",
			num,
			trantor->pos_x,
			trantor->pos_y,
			str_inventory(buf, trantor->inventory));
	send_cmd_to_client(fd, to_send);
	free(to_send);
	return (1);
}
