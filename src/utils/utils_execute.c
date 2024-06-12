/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beata <beata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:54:09 by btvildia          #+#    #+#             */
/*   Updated: 2024/06/12 08:35:43 by beata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	wait_in_parent(t_args *shell_data)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (i < shell_data->cmdarr_l)
	{
		wait(&status);
		if (WIFEXITED(status))
			shell_data->exit_status = WEXITSTATUS(status);
		i++;
	}
}

void	open_fds(t_args *shell_data, int **pipes)
{
	int	i;

	i = 0;
	while (i < shell_data->cmdarr_l - 1)
	{
		pipes[i] = ft_malloc(sizeof(int) * 2);
		pipe(pipes[i]);
		i++;
	}
}

void	close_fds(t_args *shell_data, int **pipes)
{
	int	i;

	i = 0;
	while (i < shell_data->cmdarr_l - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		ft_free(pipes[i]);
		i++;
	}
}

int	return_builtin_num(char *cmd)
{
	if (!cmd)
		return (-1);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (0);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		return (2);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (3);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (4);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (5);
	return (-1);
}


void	ft_execve(t_args *shell_data)
{
	char		*path;
	char		**cmds;
	char		**envp;
	t_env_lst	*env;

	path = NULL;
	envp = convert_env(shell_data->env);
	cmds = shell_data->cmdarr[shell_data->cmd_num].args;
	env = find_env_node("PATH", shell_data->env);
	if (ft_strchr(cmds[0], '/') == NULL)
	{
		if (!env)
			ft_error_exit(cmds[0], ": command not found", 127);
		path = find_path(cmds[0], env->val);
	}
	else
		path = ft_strdup(cmds[0]);
	if (path == NULL)
		ft_error_exit(cmds[0], ": command not found", 127);
	execve(path, cmds, envp);
	if (cmds[0] != NULL)
		ft_error_exit(cmds[0], ": command not found", 127);
	exit(0);
}

