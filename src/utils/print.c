/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beata <beata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:05:31 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/06/12 08:35:52 by beata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	print_cmds(t_args *shell_data)
{
	int	c;
	int	i;

	c = -1;
	printf("%s---------PRINT CMDS------------%s", GREEN, RE);
	printf("len cmds:%d\n\n", shell_data->cmdarr_l);
	while (++c < shell_data->cmdarr_l)
	{
		printf("cmd N: %d\nargs: ", c);
		i = -1;
		while (shell_data->cmdarr[c].args[++i] != NULL)
			printf("(%s), ", shell_data->cmdarr[c].args[i]);
		i = -1;
		printf("\ninp: ");
		while (++i < shell_data->cmdarr[c].inp_l)
			printf("{t: %i, w: %s},", shell_data->cmdarr[c].inp[i].type, \
				shell_data->cmdarr[c].inp[i].word);
		i = -1;
		printf("\nout: ");
		while (++i < shell_data->cmdarr[c].out_l)
			printf("{t: %i, w: %s},", shell_data->cmdarr[c].out[i].type, \
				shell_data->cmdarr[c].out[i].word);
		printf("\n%s-------------------------%s\n", GREEN, RE);
	}
}

void	print_env(t_env_lst *env)
{
	while (env)
	{
		printf("%s%s = %s%s%s\n", YELLOW, env->name, GREEN, env->val, RE);
		env = env->next;
	}
}
