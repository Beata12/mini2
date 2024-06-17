/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:16:01 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/17 07:48:42 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	validate_token_order(t_args *shell_data)
{
	int		i;
	t_token	*token_array;

	i = 0;
	token_array = shell_data->token_array;
	while (i < shell_data->token_count)
	{
		if (token_array[i].type == T_PIPE && ((i - 1) < 0 || (i
					+ 1) >= shell_data->token_count))
			return (my_error(token_array[i].word,
					shell_data->exec_result = 2), i);
		else if (token_array[i].type > 2 && (i + 1) >= shell_data->token_count)
			return (my_error("newline", 2), shell_data->exec_result = 2);
		else if (token_array[i].type > 2
			&& shell_data->token_array[i + 1].type > 1)
			return (my_error(token_array[i + 1].word,
					shell_data->exec_result = 2), i);
		i++;
	}
	return (-1);
}

static int	count_heredoc_tokens(t_args *shell_data, int end_index)
{
	int	i;
	int	heredoc_count;

	i = 0;
	heredoc_count = 0;
	while (i < end_index)
	{
		if (shell_data->token_count > i)
		{
			if (shell_data->token_array[i].type == T_DLESS)
			{
				if ((i + 1) < shell_data->token_count
					&& shell_data->token_array[i + 1].type == T_WORD)
				{
					heredoc_count++;
				}
			}
		}
		i++;
	}
	return (heredoc_count);
}

static void	process_heredoc_tokens(t_args *shell_data, int end_index,
	int heredoc_count)
{
	int	i;
	int	heredoc_index;

	shell_data->command_array = ft_malloc(sizeof(t_cmd_arr_str) * 1);
	shell_data->command_count = 1;
	allocate_command_memory((t_data_counter){
		.arg_count = 0,
		.input_count = heredoc_count,
		.output_count = 0
	}, shell_data->command_array);
	i = 0;
	heredoc_index = -1;
	while (i < end_index)
	{
		if (shell_data->token_array[i].type == T_DLESS)
		{
			heredoc_index++;
			set_redirection_type(
				&shell_data->command_array[0].input_tokens[heredoc_index],
				shell_data->token_array, &i);
		}
		i++;
	}
}

int	handle_heredoc_tokens(t_args *shell_data, int end_index)
{
	int	heredoc_count;

	heredoc_count = count_heredoc_tokens(shell_data, end_index);
	if (!heredoc_count)
		return (0);
	process_heredoc_tokens(shell_data, end_index, heredoc_count);
	return (heredoc_count);
}
