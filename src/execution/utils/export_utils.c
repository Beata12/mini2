/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:12:16 by aneekhra          #+#    #+#             */
/*   Updated: 2024/06/14 10:54:20 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

static char	*get_variable_name(char *input_str)
{
	int		i;
	char	*var_name;

	i = 0;
	while (input_str[i] && (ft_isalnum(input_str[i])
			|| input_str[i] == '_'))
		i++;
	var_name = ft_substr(input_str, 0, i);
	if (!var_name)
		memory_allocation_error();
	return (var_name);
}

static int	is_variable_valid(char *variable_value, char *target_name)
{
	int	name_length;

	name_length = ft_strlen(target_name);
	if (variable_value[name_length] && variable_value[name_length] != '=')
		return (0);
	return (1);
}

static void	update_environment_variable(char *input_argument,
	t_args *shell_data)
{
	char			*name;
	t_env_variable	*env_node;
	int				seperator_pos;

	name = get_variable_name(input_argument);
	if (!is_variable_valid(input_argument, name))
	{
		handle_error(input_argument, shell_data, 1, 0);
		ft_free(name);
		return ;
	}
	env_node = find_env_var(name, shell_data->env);
	if (!env_node)
		process_and_store_env_var(input_argument, &shell_data->env);
	else
	{
		seperator_pos = get_char_position(input_argument, '=');
		if (seperator_pos >= 0)
		{
			if (env_node->value)
				ft_free(env_node->value);
			env_node->value = ft_strdup(&input_argument[seperator_pos + 1]);
		}
	}
	ft_free(name);
}

void	process_environment_variables(t_args *shell_data,
	char **input_arguments, int i)
{
	while (input_arguments[i])
	{
		update_environment_variable(input_arguments[i], shell_data);
		i++;
	}
}
// void	process_environment_variables(t_args *shell_data,
// 	char **input_arguments, int i)
// {
// 	char			*name;
// 	t_env_variable	*env_node;
// 	int				separator_position;

// 	while (input_arguments[i])
// 	{
// 		name = get_variable_name(input_arguments[i]);
// 		if (!is_variable_valid(input_arguments[i], name))
// 			return (handle_error(input_arguments[i], shell_data, 1, 0),
// 				ft_free(name));
// 		env_node = find_env_var(name, shell_data->env);
// 		if (!env_node)
// 			process_and_store_env_var(input_arguments[i], &shell_data->env);
// 		else
// 		{
// 			separator_position = get_char_position(input_arguments[i], '=');
// 			if (separator_position >= 0)
// 			{
// 				if (env_node->value)
// 					ft_free(env_node->value);
// 				env_node->value = ft_strdup(&input_arguments[i]
// 					[separator_position]);
// 			}
// 		}
// 		i++;
// 	}
// }

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