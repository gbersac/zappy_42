#include "cmd.h"

int		gfx_tna(t_env *env, t_fd *fd, char *cmd)
{
	char	*to_send;
	t_list	*iter;

	iter = env->map.teams;
	while (iter != NULL)
	{
		asprintf(&to_send, "tna %s\n", iter->data);
		send_cmd_to_client(fd, to_send);
		free(to_send);
		iter = iter->next;
	}
	return (1);
	cmd = NULL;
}
