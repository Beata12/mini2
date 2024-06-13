/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beata <beata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 09:58:42 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/13 18:51:13 by beata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/execute.h"

int shell_exit(t_args *shell_data, char *user_input)
{
	if (ft_strcmp("exit", shell_data->command_array[0].args[0]) == 0)
	{
		ft_free(user_input);
		printf("exit\n");
		if (!shell_data->command_array[0].args[1])
			exit(shell_data->exec_result);
		else if (shell_data->command_array[0].args[1]
			&& !ft_isdigit_loop(shell_data->command_array[0].args[1]))
			exit_with_error("exit: ", "numeric argument required", 2);
		else if (ft_isdigit_loop(shell_data->command_array[0].args[1])
			&& shell_data->command_array[0].args[2])
			return (handle_error("", shell_data, 1, 0), 1);
		else if (shell_data->command_array[0].args[1])
			exit(ft_atoi(shell_data->command_array[0].args[1]));
	}
	return (0);
}

// int shell_exit(t_args *shell_data)
// {
//     // Free memory allocated for each argument
//     if (args != NULL) {
//         for (int i = 0; args[i].value2 != NULL; i++) {
//             free(args[i].value2);
//         }
//         //free(args);
//     }
//     exit(0);
// }


// int	shell_exit(t_args *shell_data, char *input)
// {
// 	if (ft_strcmp("exit", shell_data->cmdarr[0].args[0]) == 0)
// 	{
// 		ft_free(input);
// 		printf("exit\n");
// 		if (!shell_data->cmdarr[0].args[1])
// 			exit(shell_data->exit_status);
// 		else if (shell_data->cmdarr[0].args[1]
// 			&& !ft_isdigit_loop(shell_data->cmdarr[0].args[1]))
// 			exit_with_error("exit: ", "numeric argument required", 2);
// 		else if (ft_isdigit_loop(shell_data->cmdarr[0].args[1])
// 			&& shell_data->cmdarr[0].args[2])
// 			return (handle_error("", shell_data, 1, 0), 1);
// 		else if (shell_data->cmdarr[0].args[1])
// 			exit(ft_atoi(shell_data->cmdarr[0].args[1]));
// 	}
// 	return (0);
// }

