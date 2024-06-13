/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 09:51:48 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/13 20:56:36 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/execute.h"

void	shell_unset(t_args *shell_data)
{
	int		i;
	char	**variables_to_unset;

	variables_to_unset = shell_data->command_array
	[shell_data->command_index].args;
	if (variables_to_unset[1] == NULL)
	{
		printf("minishell: unset: not enough arguments\n");
		shell_data->exec_result = 1;
		return ;
	}
	else
	{
		i = 1;
		while (variables_to_unset[i] != NULL)
		{
			remove_env_var(variables_to_unset[i], &shell_data->env);
			i++;
		}
	}
	shell_data->exec_result = 0;
}
