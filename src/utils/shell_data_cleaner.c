
#include "../../incl/minishell.h"
//zrobione
static void	free_token_array(t_token **token_array, int *array_size)
{
	int	i;

	i = 0;
	while (i < *array_size && (*token_array) && (*token_array)[i].word)
	{
		ft_free((*token_array)[i].word);
		i++;
	}
	if (*array_size)
		ft_free(*token_array);
	*token_array = NULL;
	*array_size = 0;
}
//zrobione
static void	free_command_array(t_args *shell_data)
{
	int	i;

	i = 0;
	while (i < shell_data->command_count && shell_data->command_array)
	{
		ft_free(shell_data->command_array[i].args);
		free_token_array(&shell_data->command_array[i].input_tokens, &shell_data->command_array[i].input_length);
		free_token_array(&shell_data->command_array[i].output_tokens, &shell_data->command_array[i].output_length);
		i++;
	}
	shell_data->command_count = 0;
}
//zrobione
void	free_command_resources(t_args *shell_data)
{
	if (shell_data->token_array && shell_data->token_count)
		free_token_array(&shell_data->token_array, &shell_data->token_count);
	if (shell_data->command_array && shell_data->command_count)
		free_command_array(shell_data);
	shell_data->command_index = 0;
}
