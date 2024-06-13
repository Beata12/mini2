/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 09:58:48 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/13 20:56:31 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/execute.h"

void	shell_pwd(t_args *shell_data)
{
	char	*current_directory_path;

	current_directory_path = NULL;
	current_directory_path = getcwd(NULL, 0);
	if (!current_directory_path)
	{
		handle_error("getcwd failed", shell_data, 1, 0);
		return ;
	}
	printf("%s\n", current_directory_path);
	ft_free(current_directory_path);
	shell_data->exec_result = 0;
}
