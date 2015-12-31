#include "cmd.h"

static char	*trantors_id_to_str(t_list *trantors)
{
	char			*to_return;
	char			*buf;
	t_trantorian	*trantor;

	to_return = "";
	while (trantors != NULL)
	{
		trantor = (t_trantorian*) trantors->data;
		printf("trantor->id [%s][%d]\n",to_return, trantor->id);
		asprintf(&buf, "%s %d ", to_return, trantor->id);
		to_return = buf;
		free(buf);
		trantors = trantors->next;
	}
	return (to_return);
}

int			gfx_pic(t_env *env, t_list *trantors)
{
	char			*to_send;
	char			*ids;
	t_trantorian	*first;

	if (trantors == NULL)
		printf("ERROR: gfx_pic trantors is NULL\n");
	first = (t_trantorian*) trantors->data;
	ids = trantors_id_to_str(trantors);
	asprintf(&to_send, "pic %d %d %d %s\n",
			first->pos_x,
			first->pos_y,
			first->level,
			ids);
	free(ids);
	printf("\e[0;31mto->[gfx]\e[0m %s\n", to_send);
	send_cmd_to_graphics(env, to_send);
	return (1);
}

