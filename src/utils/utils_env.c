
#include "../../incl/minishell.h"

// cut env name from str
char	*cut_name(char *s)
{
	int		i;
	char	*name;

	i = 0;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	name = ft_substr(s, 0, i);
	if (!name)
		memory_allocation_error();
	return (name);
}

// takes name and returns node with name:val pair, or NULL
// t_env_lst *find_env_var(const char *target_name, t_env_lst *env_list)
// {
//     size_t name_len;
	
// 	name_len = ft_strlen(target_name);
//     while (env_list)
//     {
//         if (name_len == ft_strlen(env_list->name) && !ft_strncmp(target_name, env_list->name, key_len))
//             return env_list;
//         env_list = env_list->next;
//     }
//     return NULL;
// }
//ZROBIONE
t_env_variable	*find_env_var(char *name, t_env_variable *env_list)
{
	while (env_list)
	{
		if (ft_strlen(name) == ft_strlen(env_list->env_name) && !ft_strncmp(name,
				env_list->env_name, ft_strlen(name)))
			return (env_list);
		env_list = env_list->next_env_var;
	}
	return (NULL);
}

//ZMIENIONE 
char **generate_envp_array(t_env_variable *env_list)
{
	int				i;
	char			**env_array;
	t_env_variable	*current_env;

	i = 0;
	current_env = env_list;
	while (current_env)
	{
		i++;
		current_env = current_env->next_env_var;
	}
	env_array = ft_malloc(sizeof(char *) * (i + 1));
	i = 0;
	current_env = env_list;
	while (current_env)
	{
		env_array[i] = ft_strjoin(current_env->env_name, "=");
		if (current_env->value)
			env_array[i] = ft_strjoin(env_array[i], current_env->value);
		i++;
		current_env = current_env->next_env_var;
	}
	env_array[i] = NULL;
	return env_array;
}

// char	**convert_env(t_env_lst *env)
// {
// 	t_env_lst	*tmp;
// 	char		**envp;
// 	int			i;

// 	i = 0;
// 	tmp = env;
// 	while (tmp)
// 	{
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	envp = ft_malloc(sizeof(char *) * (i + 1));
// 	i = 0;
// 	tmp = env;
// 	while (tmp)
// 	{
// 		envp[i] = ft_strjoin(tmp->name, "=");
// 		if (tmp->val)
// 			envp[i] = ft_strjoin(envp[i], tmp->val);
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	envp[i] = NULL;
// 	return (envp);
// }