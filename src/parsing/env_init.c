
#include "../../incl/minishell.h"

static void	set_shlvl(t_args *shell_data)
{
	t_env_lst	*shlvl_node;
	int			shlvl;

	shlvl_node = find_env_var("SHLVL", shell_data->env);
	shlvl = ft_atoi(shlvl_node->val);
	if (shlvl == 999)
	{
		my_error("", 0);
		shlvl = 0;
	}
	ft_free(shlvl_node->val);
	shlvl_node->val = ft_itoa(shlvl + 1);
}

int	process_and_store_env_var(char *input_str, t_env_lst **env_list)
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
		ft_lstadd_env(env_list, env_name, env_value);
	}
	else
	{
		env_name = ft_strdup((char *)input_str);
		env_value = NULL;
		if (!env_name)
			error_flag = 1;
		ft_lstadd_env(env_list, env_name, env_value);
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
	set_shlvl(shell_data);
}
