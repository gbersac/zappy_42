# include "cmd.h"

int					ser_connect_nbr(t_env *env, t_fd *fd, char *cmd)
{
	t_trantorian	*t;
	t_list			*tmp;
	int				cnt_trants_available;
	int				cnt_trants_reserved;
	char			*msg;

	cmd = NULL;
	cnt_trants_available = 0;
	cnt_trants_reserved = 0;
	tmp = env->trant;
	while (tmp)
	{
		t = (t_trantorian*)tmp->data;
		if (t->id == -1)
			cnt_trants_available++;
		else if (t->id > -1)
			cnt_trants_reserved++;
		tmp = tmp->next;
	}
	asprintf(&msg, "available: %d, reserved: %d", cnt_trants_available, cnt_trants_reserved);
	send_cmd_to_client(fd, msg);
	return (0);
}
