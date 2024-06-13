/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beata <beata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:12:09 by aneekhra          #+#    #+#             */
/*   Updated: 2024/06/13 19:19:21 by beata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"
//zrobione
void	initialize_builtins(t_args *shell_data)
{
	int i;
	int	num_builtins ;

	i = 0;
	num_builtins  = 6;
	shell_data->builtin_cmds = ft_malloc(sizeof(t_builtin) * (num_builtins  + 1));
	// shell_data->builtin[0].name = "pwd";
	// shell_data->builtin[0].fn_ptr = ft_pwd;
	// shell_data->builtin[1].name = "cd";
	// shell_data->builtin[1].fn_ptr = ft_cd;
	// shell_data->builtin[2].name = "echo";
	// shell_data->builtin[2].fn_ptr = ft_echo;
	// shell_data->builtin[3].name = "unset";
	// shell_data->builtin[3].fn_ptr = ft_unset;
	// shell_data->builtin[4].name = "export";
	// shell_data->builtin[4].fn_ptr = ft_export;
	// shell_data->builtin[5].name = "env";
	// shell_data->builtin[5].fn_ptr = ft_env;
	// shell_data->builtin[6].name = NULL;
	// shell_data->builtin[6].fn_ptr = NULL;
	t_builtin builtins[] = {
        {"pwd", shell_pwd},
        {"cd", shell_cd},
        {"echo", shell_echo},
        {"unset", shell_unset},
        {"export", shell_export},
        {"env", shell_env},
        {NULL, NULL} // Zakończenie tablicy
    };

    while (i <= num_builtins)
	{
        shell_data->builtin_cmds[i] = builtins[i];
        i++;
    }
}