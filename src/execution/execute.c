/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beata <beata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:12:31 by aneekhra          #+#    #+#             */
/*   Updated: 2024/06/13 19:00:51 by beata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

//zrobione
int	identify_builtin_command(char *builtin_command)
{
	if (!builtin_command)
		return (-1);
	else if (ft_strncmp(builtin_command, "pwd", 4) == 0)
		return (0);
	else if (ft_strncmp(builtin_command, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(builtin_command, "echo", 5) == 0)
		return (2);
	else if (ft_strncmp(builtin_command, "unset", 6) == 0)
		return (3);
	else if (ft_strncmp(builtin_command, "export", 7) == 0)
		return (4);
	else if (ft_strncmp(builtin_command, "env", 4) == 0)
		return (5);
	return (-1);
}
//zrobione
void	execute(t_args *shell_data)
{
	int	i;
	int	**pipe_array;

	pipe_array = ft_malloc(sizeof(int *) * (shell_data->command_count - 1));
	i = identify_builtin_command(shell_data->command_array[0].args[0]);
	if (shell_data->command_count == 1 && i != -1 && (shell_data->command_array[0].input_length == 0)
		&& (shell_data->command_array[0].output_length == 0))
		shell_data->builtin_cmds[i].fn_ptr(shell_data);
	else
	{
		initialize_pipes(shell_data, pipe_array);
		execute_pipeline(shell_data, pipe_array);
		close_pipe_descriptors(shell_data, pipe_array);
		wait_for_child_processes(shell_data);
	}
}
//zrobione
void	execute_pipeline(t_args *shell_data, int **pipe_array)
{
	int		i;
	pid_t	process_id;

	i = 0;
	while (i < shell_data->command_count)
	{
		process_id = fork();
		if (process_id == 0)
		{
			signal(SIGINT, handle_sigquit);
			process_all_heredocs(shell_data, i);
			if (i != 0)
				dup2(pipe_array[i - 1][0], 0);
			if (i != shell_data->command_count - 1)
				dup2(pipe_array[i][1], 1);
			close_pipe_descriptors(shell_data, pipe_array);
			setup_input_redirection(shell_data, i);
			setup_output_redirection(shell_data, i);
			shell_data->command_index = i;
			signal(SIGINT, SIG_DFL);
			ft_execute(shell_data);
			exit(shell_data->exec_result);
		}
		i++;
	}
}
//zrobione
void	ft_execute(t_args *shell_data)
{
	int	i;

	i = identify_builtin_command(shell_data->command_array[shell_data->command_index].args[0]);
	if (i == -1)
		ft_execve(shell_data);
	else
		shell_data->builtin_cmds[i].fn_ptr(shell_data);
}
