#include "../inc/client.h"
#include "../../libft/inc/libft.h"

void	cmd(t_env *env, char *cmd, char *str)
{
	char	*ret;

	ft_putendl(cmd);
	if (str)
		ret = ft_strjoin(cmd, str);
	else
		ret = cmd;
	ft_listpushback(&env->buf_write, ret);
}