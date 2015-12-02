#include "cmd.h"

void		send_msg_to_all_excpt_src(t_env *env, t_fd *fd, char *msg)
{
	int				i;
	char			*str;
	t_trantorian	*trant;

	i = 0;
	str = NULL;
	trant = &fd->trantor;
	/*str = ft_strjoin(str, ft_itoa(trant->pos_x));
	str = ft_strjoin(str, " ");
	str = ft_strjoin(str, ft_itoa(trant->pos_y));
	str = ft_strjoin(str, " ");
	str = ft_strjoin(str, trant->team);
	str = ft_strjoin(str, " ");
	str = ft_strjoin(str, msg);*/
	asprintf(&str, "%d %d %s %s", trant->pos_x, trant->pos_y, 
		trant->team, msg);
	while (i < env->maxfd)
	{
		// printf("")
		if (env->fds[i].type == FD_CLIENT && env->fds[i].fd != fd->fd)
			send_cmd_to_client(&env->fds[i], str);
		i++;
	}
}

int			ser_broadcast(t_env *env, t_fd *fd, char *cmd)
{
	char	**split;

	printf("cmd : %s\n", cmd);
	// env = NULL; fd = NULL; cmd = NULL;
	split = ft_strsplit(cmd, ' ');
	send_msg_to_all_excpt_src(env, fd, split[1]);
	send_cmd_to_client(fd, MSG_OK);
	return (0);
}
