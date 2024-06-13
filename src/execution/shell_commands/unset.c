/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beata <beata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 09:51:48 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/13 18:58:14 by beata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/execute.h"

void	shell_unset(t_args *shell_data)
{
	int		i;
	char	**rm_names;

	rm_names = shell_data->command_array[shell_data->command_index].args;
	if (rm_names[1] == NULL)
	{
		printf("minishell: unset: not enough arguments\n");
		shell_data->exec_result = 1;
		return ;
	}
	else
	{
		i = 1;
		while (rm_names[i] != NULL)
		{
			remove_env_var(rm_names[i], &shell_data->env);
			i++;
		}
	}
	shell_data->exec_result = 0;
}