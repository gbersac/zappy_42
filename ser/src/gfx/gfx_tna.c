#include "cmd.h"

int		gfx_tna(t_env *env, t_fd *fd, char *cmd)
{
	char	*to_send;
	t_list	*iter;

	printf("tna called\n");
	iter = env->map.teams;
	while (iter != NULL)
	{
		asprintf(&to_send, "tna %s\n", iter->data);
		printf("\e[0;31mto->[gfx]\e[0m %s\n", to_send);
		send_cmd_to_client(fd, to_send);
		free(to_send);
		iter = iter->next;
	}
	return (1);
	cmd = NULL;
}
