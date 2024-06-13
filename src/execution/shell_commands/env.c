/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beata <beata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 09:58:40 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/13 11:33:41 by beata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/execute.h"

// void	shell_env(t_args *shell_data)
// {
// 	t_env_lst	*env_iterator;

// 	env_iterator = shell_data->env; // Iterate through the environment list
// 	// Print environment variables in the format "name=value"
// 	while (env_iterator)
// 	{
// 		if (env_iterator->val) {
// 			printf("%s=%s\n", env_iterator->name, env_iterator->val);
// 		} else {
// 			printf("%s\n", env_iterator->name); // Print only the name if no value
// 		}
// 		env_iterator = env_iterator->next;
// 	}

// 	shell_data->exit_status = 0; // Set exit status to success (0)
// }

void	shell_env(t_args *shell_data)
{
	t_env_lst	*tmp;

	tmp = shell_data->env;
	if (!shell_data->export)
	{
		while (tmp)
		{
			if (tmp->val)
				printf("%s=%s\n", tmp->name, tmp->val);
			tmp = tmp->next;
		}
		shell_data->exit_status = 0;
		return ;
	}
	tmp = shell_data->export;
	while (tmp)
	{
		if (tmp->val)
			printf("declare -x %s=\"%s\"\n", tmp->name, tmp->val);
		else
			printf("declare -x %s\n", tmp->name);
		tmp = tmp->next;
	}
	shell_data->exit_status = 0;
}

// int shell_env(void)
// {
//     extern char **environ;
//     if (environ == NULL)
//     {
//         fprintf(stderr, "Error: environ is NULL\n");
//         return -1;
//     }

//     for (char **env = environ; *env != NULL; env++)
//     {
//         if (*env == NULL)
//         {
//             fprintf(stderr, "Warning: Null environment variable encountered\n");
//             continue;
//         }
//         printf("%s\n", *env);
//     }
//     return 0;
// }
