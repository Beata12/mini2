
#include "../../incl/minishell.h"

static void	set_shlvl(t_args *shell_data)
{
	t_env_lst	*shlvl_node;
	int			shlvl;

	shlvl_node = find_env_node("SHLVL", shell_data->env);
	shlvl = ft_atoi(shlvl_node->val);
	if (shlvl == 999)
	{
		my_error("", 0);
		shlvl = 0;
	}
	ft_free(shlvl_node->val);
	shlvl_node->val = ft_itoa(shlvl + 1);
}

int	fill_str(char *s, t_env_lst **lst)
{
	int		divider_pos;
	int		err;
	char	*val;
	char	*name;

	err = 0;
	divider_pos = ft_strchr_pos(s, '=');
	if (divider_pos >= 0)
	{
		name = ft_substr(s, 0, divider_pos - 1);
		val = ft_strdup(&(s[divider_pos]));
		if (!val || !name)
			err = 1;
		ft_lstadd_env(lst, name, val);
	}
	else
	{
		name = ft_strdup((char *)s);
		val = NULL;
		if (!name)
			err = 1;
		ft_lstadd_env(lst, name, val);
	}
	return (err);
}

void	initialize_environment(t_args *shell_data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (fill_str(env[i], &shell_data->env))
		{
			clean_lst_env(&shell_data->env);
			alloc_err();
		}
		i++;
	}
	set_shlvl(shell_data);
}
