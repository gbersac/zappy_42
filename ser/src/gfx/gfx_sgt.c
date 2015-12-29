#include "cmd.h"

int		gfx_sgt(t_env *env, t_fd *fd, char *cmd)
{
	char	*to_send;

	printf("sgt called\n");
	to_send = (char*)malloc(4);
	asprintf(&to_send, "sgt %d\n", env->map.time_d);

	send_cmd_to_client(fd, to_send);
	return (1);
	cmd = NULL;
}
