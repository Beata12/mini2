/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env_initializer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:13:11 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/14 13:15:25 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	add_environment_variable(t_env_variable **env_list,
		char *env_name, char *env_value)
{
	t_env_variable	*new_env_var;
	t_env_variable	*current_node;

	new_env_var = ft_malloc(sizeof(t_env_variable));
	current_node = *env_list;
	if (!current_node)
		*env_list = new_env_var;
	else
	{
		while (current_node->next_env_var)
			current_node = current_node->next_env_var;
		current_node->next_env_var = new_env_var;
	}
	new_env_var->env_name = env_name;
	new_env_var->value = env_value;
	new_env_var->next_env_var = NULL;
}

t_env_variable	*find_env_var(char *name, t_env_variable *env_list)
{
	while (env_list)
	{
		if (ft_strlen(name) == ft_strlen(env_list->env_name)
			&& !ft_strncmp(name, env_list->env_name, ft_strlen(name)))
			return (env_list);
		env_list = env_list->next_env_var;
	}
	return (NULL);
}

static void	update_shell_level(t_args *shell_data)
{
	int				shell_level_count;
	t_env_variable	*shell_level_var;

	shell_level_var = find_env_var("SHLVL", shell_data->env);
	shell_level_count = ft_atoi(shell_level_var->value);
	if (shell_level_count == 999)
	{
		my_error("", 0);
		shell_level_count = 0;
	}
	ft_free(shell_level_var->value);
	shell_level_var->value = ft_itoa(shell_level_count + 1);
}

int	process_and_store_env_var(char *input_str, t_env_variable **env_list)
{
	int		split_index;
	int		error_flag;
	char	*env_value;
	char	*env_name;

	error_flag = 0;
	split_index = get_char_position(input_str, '=');
	if (split_index >= 0)
	{
		env_name = ft_substr(input_str, 0, split_index - 1);
		env_value = ft_strdup(&(input_str[split_index]));
		if (!env_value || !env_name)
			error_flag = 1;
		add_environment_variable(env_list, env_name, env_value);
	}
	else
	{
		env_name = ft_strdup((char *)input_str);
		env_value = NULL;
		if (!env_name)
			error_flag = 1;
		add_environment_variable(env_list, env_name, env_value);
	}
	return (error_flag);
}

void	initialize_environment(t_args *shell_data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (process_and_store_env_var(env[i], &shell_data->env))
		{
			clear_environment_list(&shell_data->env);
			memory_allocation_error();
		}
		i++;
	}
	update_shell_level(shell_data);
}
