
#include "../../incl/minishell.h"

static void	clean_tokarr(t_token **arr, int *len)
{
	int	i;

	i = -1;
	while (++i < *len && (*arr) && (*arr)[i].word)
		ft_free((*arr)[i].word);
	if (*len)
		ft_free(*arr);
	*arr = NULL;
	*len = 0;
}

static void	clean_cmdarr(t_args *shell_data)
{
	int	i;

	i = -1;
	while (++i < shell_data->cmdarr_l && shell_data->cmdarr)
	{
		ft_free(shell_data->cmdarr[i].args);
		clean_tokarr(&shell_data->cmdarr[i].inp, &shell_data->cmdarr[i].inp_l);
		clean_tokarr(&shell_data->cmdarr[i].out, &shell_data->cmdarr[i].out_l);
	}
	shell_data->cmdarr_l = 0;
}

void	clean_command_data(t_args *shell_data)
{
	if (shell_data->tokarr && shell_data->tokarr_l)
		clean_tokarr(&shell_data->tokarr, &shell_data->tokarr_l);
	if (shell_data->cmdarr && shell_data->cmdarr_l)
		clean_cmdarr(shell_data);
	shell_data->cmd_num = 0;
}
