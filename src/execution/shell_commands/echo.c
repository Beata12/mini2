/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beata <beata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:12:22 by aneekhra          #+#    #+#             */
/*   Updated: 2024/06/13 18:58:01 by beata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/execute.h"

static int	check_n_flag(t_args *shell_data, int *add_newline)
{
	int	i;
	int	j;

	i = 1;
	*add_newline = 1;  // Zakładamy dodanie nowej linii, jeśli nie znajdziemy flagi -n
	while (shell_data->command_array[shell_data->command_index].args[i])
	{
		if (shell_data->command_array[shell_data->command_index].args[i][0] != '-')
			break;
		j = 1;
		while (shell_data->command_array[shell_data->command_index].args[i][j] == 'n')
			j++;
		if (shell_data->command_array[shell_data->command_index].args[i][j])
			break;
		i++;
	}
	if (i > 1)
		*add_newline = 0;  // Flaga -n została znaleziona, więc nie dodajemy nowej linii
	return i;
}

void	shell_echo(t_args *shell_data)
{
	int	i;
	int	add_newline;

	i = check_n_flag(shell_data, &add_newline);
	while (shell_data->command_array[shell_data->command_index].args[i])
	{
		if (shell_data->command_array[shell_data->command_index].args[i + 1] != NULL)
			printf("%s ", shell_data->command_array[shell_data->command_index].args[i]);
		else
			printf("%s", shell_data->command_array[shell_data->command_index].args[i]);
		i++;
	}
	if (add_newline)
		printf("\n");
	shell_data->exec_result = 0;
}

// static int	check_n_flag(t_args *shell_data, int *newline_flag)
// {
// 	int	i;
// 	int	j;
// 	i = 1;
// 	while (shell_data->cmdarr[shell_data->cmd_num].args[i])
// 	{
// 		if (shell_data->cmdarr[shell_data->cmd_num].args[i][0] != '-')
// 			break ;
// 		j = 1;
// 		while (shell_data->cmdarr[shell_data->cmd_num].args[i][j] == 'n')
// 			j++;
// 		if (shell_data->cmdarr[shell_data->cmd_num].args[i][j])
// 			break ;
// 		i++;
// 	}
// 	if (i > 1)
// 		*newline_flag = 0;
// 	else
// 		*newline_flag = 1;
// 	return (i);
// }
// void	shell_echo(t_args *shell_data)
// {
// 	int	i;
// 	int	newline_flag;
// 	i = check_n_flag(shell_data, &newline_flag);
// 	while (shell_data->cmdarr[shell_data->cmd_num].args[i])
// 	{
// 		if (shell_data->cmdarr[shell_data->cmd_num].args[i + 1] != NULL)
// 			printf("%s ", shell_data->cmdarr[shell_data->cmd_num].args[i]);
// 		else
// 			printf("%s", shell_data->cmdarr[shell_data->cmd_num].args[i]);
// 		i++;
// 	}
// 	if (newline_flag)
// 		printf("\n");
// 	shell_data->exit_status = 0;
// }