// void	interpret_msg(t_env *env, char *get)
// {
// 	if (ft_strnequ(get, MSG_WELCOME, ft_strlen(MSG_WELCOME)))
// 	{
// 		ft_listpushback(&env->buf_write, ft_strjoin(env->teamname, "\n"));
// 		env->last_cmd = strdup(MSG_WELCOME);
// 	}
// 	else if (ft_strnequ(get, MSG_DEAD, ft_strlen(MSG_DEAD)))
// 		player_dies(env, get);
// 	else if (ft_strnequ(get, MSG_BROADCAST, ft_strlen(MSG_BROADCAST)))
// 	{
// 		ft_printf("Get a broadcast : <%s>\n", get);
// 		// des trucs
// 	}
// 	else if (ft_strnequ(get, MSG_OK, ft_strlen(MSG_OK)))
// 	{
// 		valid_last_action(env);
// 		handle_action(env);
// 	}
// 	else if (ft_strnequ(get, MSG_KO, ft_strlen(MSG_KO)))
// 	{
// 		ft_printf("Last action fail\n");
// 		handle_action(env);
// 	}
// }

int cmd_welcome(t_env *env, char *cmd)
{

}
