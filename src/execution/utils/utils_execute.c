/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:32:06 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/14 16:55:33 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

void	wait_for_child_processes(t_args *shell_data)
{
	int	i;
	int	child_status;

	i = 0;
	child_status = 0;
	while (i < shell_data->command_count)
	{
		wait(&child_status);
		if (WIFEXITED(child_status))
			shell_data->exec_result = WEXITSTATUS(child_status);
		i++;
	}
}

void	initialize_pipes(t_args *shell_data, int **pipe_array)
{
	int	i;

	i = 0;
	while (i < shell_data->command_count - 1)
	{
		pipe_array[i] = ft_malloc(sizeof(int) * 2);
		pipe(pipe_array[i]);
		i++;
	}
}

void	close_pipe_descriptors(t_args *shell_data, int **pipe_array)
{
	int	i;

	i = 0;
	while (i < shell_data->command_count - 1)
	{
		close(pipe_array[i][0]);
		close(pipe_array[i][1]);
		ft_free(pipe_array[i]);
		i++;
	}
}

//tutaj
void	ft_execve(t_args *shell_data)
{
	char			*executable_path;
	char			**command_args;
	char			**envp_array;
	t_env_variable	*env_node;

	executable_path = NULL;
	printf("shell data %s", shell_data->env->env_name);
	envp_array = generate_envp_array(shell_data->env);
	command_args = shell_data->command_array[shell_data->command_index].args;
	env_node = find_env_var("PATH", shell_data->env);
	if (ft_strchr(command_args[0], '/') == NULL)
	{
		if (!env_node)
			exit_with_error(command_args[0], ": command not found", 127);
		executable_path = locate_file_in_path(command_args[0], env_node->value);
	}
	else
		executable_path = ft_strdup(command_args[0]);
	if (executable_path == NULL)
		exit_with_error(command_args[0], ": command not found", 127);
	execve(executable_path, command_args, envp_array);
	exit_with_error(command_args[0], ": command not found", 127);
	if (command_args[0] != NULL)
		exit_with_error(command_args[0], ": command not found", 127);
	free(envp_array);
	exit(0);
}
