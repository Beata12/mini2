/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:12:22 by aneekhra          #+#    #+#             */
/*   Updated: 2024/06/12 21:12:26 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

static int	handle_n_flag(t_args *shell_data, int *n_line)
{
	int	i;
	int	j;

	i = 1;
	while (shell_data->cmdarr[shell_data->cmd_num].args[i])
	{
		if (shell_data->cmdarr[shell_data->cmd_num].args[i][0] != '-')
			break ;
		j = 1;
		while (shell_data->cmdarr[shell_data->cmd_num].args[i][j] == 'n')
			j++;
		if (shell_data->cmdarr[shell_data->cmd_num].args[i][j])
			break ;
		i++;
	}
	if (i > 1)
		*n_line = 0;
	else
		*n_line = 1;
	return (i);
}

void	ft_echo(t_args *shell_data)
{
	int	i;
	int	n_line;

	i = handle_n_flag(shell_data, &n_line);
	while (shell_data->cmdarr[shell_data->cmd_num].args[i])
	{
		if (shell_data->cmdarr[shell_data->cmd_num].args[i + 1] != NULL)
			printf("%s ", shell_data->cmdarr[shell_data->cmd_num].args[i]);
		else
			printf("%s", shell_data->cmdarr[shell_data->cmd_num].args[i]);
		i++;
	}
	if (n_line)
		printf("\n");
	shell_data->exit_status = 0;
}
