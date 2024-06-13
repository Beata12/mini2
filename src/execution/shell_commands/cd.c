/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beata <beata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:58:35 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/13 09:57:32 by beata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/execute.h"

void shell_cd(t_args *shell_data)
{
	char *target_path = NULL;
	t_env_lst *home_node = NULL;

	if (shell_data->cmdarr[shell_data->cmd_num].args[1] == NULL)
	{
		// Handle 'cd' without arguments
		home_node = find_env_node("HOME", shell_data->env);
		if (home_node)
			target_path = ft_strdup(home_node->val);
		else
		{
			ft_error_return("", shell_data, 1, 1);
			return;
		}
	}
	else// Handle 'cd' with arguments
		target_path = ft_strdup(shell_data->cmdarr[shell_data->cmd_num].args[1]);
	if (chdir(target_path) == -1)
		ft_error_return(target_path, shell_data, 1, 0);
	else
		shell_data->exit_status = 0;
	ft_free(target_path);
}
