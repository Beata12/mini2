
#include "../../incl/minishell.h"

static void	set_count(t_count *count)
{
	count->arg = 0;
	count->in = 0;
	count->out = 0;
}

void	alloc_cmd(t_count sizes, t_cmdarr *cmd)
{
	cmd->args = ft_malloc(sizeof(char *) * (sizes.arg + 1));
	cmd->inp = ft_malloc(sizeof(t_token) * sizes.in);
	cmd->out = ft_malloc(sizeof(t_token) * sizes.out);
	cmd->args[sizes.arg] = NULL;
	cmd->inp_l = sizes.in;
	cmd->out_l = sizes.out;
}

void	init_cmd(int c, int *t, t_args *shell_data)
{
	t_count	count;

	set_count(&count);
	while (shell_data->tokarr && *t < shell_data->tokarr_l && shell_data->tokarr[*t].word
		&& shell_data->tokarr[*t].type != T_PIPE)
	{
		if (shell_data->tokarr[*t].type == T_WORD)
			count.arg++;
		else
		{
			if (shell_data->tokarr[*t].type == T_RED_FROM
				|| shell_data->tokarr[*t].type == T_DLESS)
				count.in++;
			else if (shell_data->tokarr[*t].type == T_RED_TO
				|| shell_data->tokarr[*t].type == T_DGREAT)
				count.out++;
			if (shell_data->tokarr[*t].type == T_RED_FROM
				&& spec_symb(shell_data->tokarr[*t].word) == 2)
				count.out++;
			(*t)++;
		}
		(*t)++;
	}
	alloc_cmd(count, &shell_data->cmdarr[c]);
}

void	init_cmdarr(t_args *shell_data)
{
	int	c;
	int	t;

	t = -1;
	c = 1;
	while (++t < shell_data->tokarr_l)
	{
		if (shell_data->tokarr[t].type == T_PIPE)
			c++;
	}
	shell_data->cmdarr = ft_malloc(sizeof(t_cmdarr) * c);
	shell_data->cmdarr_l = c;
	c = -1;
	t = -1;
	while (++c < shell_data->cmdarr_l && ++t < shell_data->tokarr_l)
		init_cmd(c, &t, shell_data);
}
