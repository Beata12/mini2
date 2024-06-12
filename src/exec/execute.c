/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beata <beata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:46:36 by btvildia          #+#    #+#             */
/*   Updated: 2024/06/12 08:38:21 by beata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

void	execute(t_args *shell_data)
{
	int	i;
	int	**pipes;

	pipes = ft_malloc(sizeof(int *) * (shell_data->cmdarr_l - 1));
	i = return_builtin_num(shell_data->cmdarr[0].args[0]);
	if (shell_data->cmdarr_l == 1 && i != -1 && (shell_data->cmdarr[0].inp_l == 0)
		&& (shell_data->cmdarr[0].out_l == 0))
		shell_data->builtin[i].fn_ptr(shell_data);
	else
	{
		open_fds(shell_data, pipes);
		ft_piping(shell_data, pipes);
		close_fds(shell_data, pipes);
		wait_in_parent(shell_data);
	}
}

void	ft_piping(t_args *shell_data, int **pipes)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < shell_data->cmdarr_l)
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, child_signal);
			heredoc_loop(shell_data, i);
			if (i != 0)
				dup2(pipes[i - 1][0], 0);
			if (i != shell_data->cmdarr_l - 1)
				dup2(pipes[i][1], 1);
			close_fds(shell_data, pipes);
			open_input_files(shell_data, i);
			open_output_files(shell_data, i);
			shell_data->cmd_num = i;
			signal(SIGINT, SIG_DFL);
			ft_execute(shell_data);
			exit(shell_data->exit_status);
		}
		i++;
	}
}

void	ft_execute(t_args *shell_data)
{
	int	i;

	i = return_builtin_num(shell_data->cmdarr[shell_data->cmd_num].args[0]);
	if (i == -1)
		ft_execve(shell_data);
	else
		shell_data->builtin[i].fn_ptr(shell_data);
}
