
#include "../../incl/minishell.h"

static void	free_token_array(t_token **token_array, int *size)
{
	int	i;

	i = 0;
	while (i < *size && (*token_array) && (*token_array)[i].word)
	{
		ft_free((*token_array)[i].word);
		i++;
	}
	if (*size)
		ft_free(*token_array);
	*token_array = NULL;
	*size = 0;
}

static void	free_command_array(t_args *shell_data)
{
	int	i;

	i = 0;
	while (i < shell_data->cmdarr_l && shell_data->cmdarr)
	{
		ft_free(shell_data->cmdarr[i].args);
		free_token_array(&shell_data->cmdarr[i].inp, &shell_data->cmdarr[i].inp_l);
		free_token_array(&shell_data->cmdarr[i].out, &shell_data->cmdarr[i].out_l);
		i++;
	}
	shell_data->cmdarr_l = 0;
}

void	free_command_resources(t_args *shell_data)
{
	if (shell_data->tokarr && shell_data->tokarr_l)
		free_token_array(&shell_data->tokarr, &shell_data->tokarr_l);
	if (shell_data->cmdarr && shell_data->cmdarr_l)
		free_command_array(shell_data);
	shell_data->cmd_num = 0;
}
