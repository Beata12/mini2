/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file_access.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:12:40 by aneekhra          #+#    #+#             */
/*   Updated: 2024/06/16 16:37:01 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

int	manage_file_access(char *file_path, int file_flags)
{
	int	file;

	file = 0;
	if (file_flags == 0)
		file = open(file_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (file_flags == 1)
		file = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (file_flags == 2)
		file = open(file_path, O_RDONLY, 0644);
	else if (file_flags == 3)
		file = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file < 0)
		exit_with_error(file_path, ": No such file or directory", 1);
	return (file);
}

void	execute_heredoc(t_args *shell_data, int command_index, int input_index)
{
	char	*delimiter;
	char	*user_input;
	int		heredoc_file;

	delimiter = shell_data->command_array[command_index].input_tokens
	[input_index].word;
	heredoc_file = manage_file_access("/tmp/heredoc_tmp", 3);
	while (1)
	{
		user_input = readline("heredoc> ");
		if (!user_input || ft_strcmp(user_input, delimiter) == 0)
		{
			free(user_input);
			break ;
		}
		write(heredoc_file, user_input, ft_strlen(user_input));
		write(heredoc_file, "\n", 1);
		free(user_input);
	}
	close(heredoc_file);
}

void	process_all_heredocs(t_args *shell_data, int command_index)
{
	int	input_index;

	input_index = 0;
	while (input_index < shell_data->command_array[command_index].input_length)
	{
		if (shell_data->command_array[command_index].input_tokens
			[input_index].type == T_DLESS)
			execute_heredoc(shell_data, command_index, input_index);
		input_index++;
	}
}

void	setup_input_redirection(t_args *shell_data, int command_index)
{
	int	input_index;
	int	file;

	input_index = 0;
	while (input_index < shell_data->command_array[command_index].input_length)
	{
		if (shell_data->command_array[command_index].input_tokens
			[input_index].type == T_DLESS)
			file = manage_file_access("/tmp/heredoc_tmp", 2);
		else
			file = manage_file_access(shell_data->command_array
				[command_index].input_tokens[input_index].word, 2);
		dup2(file, 0);
		close(file);
		input_index++;
	}
}

void	setup_output_redirection(t_args *shell_data, int command_index)
{
	int	input_index;
	int	file;

	input_index = 0;
	while (input_index < shell_data->command_array[command_index].output_length)
	{
		if (shell_data->command_array[command_index].output_tokens
			[input_index].type == T_DGREAT)
			file = manage_file_access(shell_data->command_array
				[command_index].output_tokens[input_index].word, 0);
		else
			file = manage_file_access(shell_data->command_array
				[command_index].output_tokens[input_index].word, 1);
		dup2(file, 1);
		close(file);
		input_index++;
	}
}
