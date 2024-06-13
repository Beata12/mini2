/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beata <beata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:12:16 by aneekhra          #+#    #+#             */
/*   Updated: 2024/06/13 14:09:32 by beata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	check_var_validity(char *var, char *name)
{
	int	n_l;

	n_l = ft_strlen(name);
	if (var[n_l] && var[n_l] != '=')
		return (0);
	return (1);
}

void	export_loop(t_args *shell_data, char **args, int i)
{
	char		*name;
	t_env_lst	*env_node;
	int			divider_pos;

	while (args[i])
	{
		name = cut_name(args[i]);
		if (!check_var_validity(args[i], name))
			return (handle_error(args[i], shell_data, 1, 0), ft_free(name));
		env_node = find_env_var(name, shell_data->env);
		if (!env_node)
			process_and_store_env_var(args[i], &shell_data->env);
		else
		{
			divider_pos = get_char_position(args[i], '=');
			if (divider_pos >= 0)
			{
				if (env_node->val)
					ft_free(env_node->val);
				env_node->val = ft_strdup(&args[i][divider_pos]);
			}
		}
		i++;
	}
}
// void	ft_env(t_args *shell_data)
// {
// 	t_env_lst	*tmp;

// 	tmp = shell_data->env;
// 	if (!shell_data->export)
// 	{
// 		while (tmp)
// 		{
// 			if (tmp->val)
// 				printf("%s=%s\n", tmp->name, tmp->val);
// 			tmp = tmp->next;
// 		}
// 		shell_data->exit_status = 0;
// 		return ;
// 	}
// 	tmp = shell_data->export;
// 	while (tmp)
// 	{
// 		if (tmp->val)
// 			printf("declare -x %s=\"%s\"\n", tmp->name, tmp->val);
// 		else
// 			printf("declare -x %s\n", tmp->name);
// 		tmp = tmp->next;
// 	}
// 	shell_data->exit_status = 0;
// }


// void	shell_export(t_args *shell_data)
// {
// 	char	**args;

// 	args = shell_data->cmdarr[shell_data->cmd_num].args;
// 	if (args[1] == NULL)
// 	{
// 		copy_list(shell_data->env, &shell_data->export);
// 		remove_one_node("_", &shell_data->export);
// 		tmp_sort_env(shell_data->export);
// 		shell_env(shell_data);
// 		clean_lst_env(&shell_data->export);
// 		shell_data->exit_status = 0;
// 	}
// 	else
// 		export_loop(shell_data, args, 1);
// }

// void	ft_unset(t_args *shell_data)
// {
// 	int		i;
// 	char	**rm_names;

// 	rm_names = shell_data->cmdarr[shell_data->cmd_num].args;
// 	if (rm_names[1] == NULL)
// 	{
// 		printf("minishell: unset: not enough arguments\n");
// 		shell_data->exit_status = 1;
// 		return ;
// 	}
// 	else
// 	{
// 		i = 1;
// 		while (rm_names[i] != NULL)
// 		{
// 			remove_one_node(rm_names[i], &shell_data->env);
// 			i++;
// 		}
// 	}
// 	shell_data->exit_status = 0;
// }
