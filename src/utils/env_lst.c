
#include "../../incl/minishell.h"

// int	env_lst_len(t_env_variable *lst)
// {
// 	int	size;

// 	size = 0;
// 	while (lst)
// 	{
// 		lst = lst->next;
// 		size++;
// 	}
// 	return (size);
// }

void	ft_lstadd_env(t_env_variable **lst, char *name, char *val)
{
	t_env_variable	*node;
	t_env_variable	*head;

	node = ft_malloc(sizeof(t_env_variable));
	head = *lst;
	if (!head)
		*lst = node;
	else
	{
		while (head->next_env_var)
			head = head->next_env_var;
		head->next_env_var = node;
	}
	node->env_name = name;
	node->value = val;
	node->next_env_var = NULL;
}

void	free_environment_node(t_env_variable **env_list)
{
	t_env_variable	*next_node;

	next_node = (*env_list)->next_env_var;
	ft_free((*env_list)->env_name);
	if ((*env_list)->value)
		ft_free((*env_list)->value);
	ft_free(*env_list);
	*env_list = next_node;
}

//zrobione
void	clear_environment_list(t_env_variable **env_list)
{
	while ((*env_list))
		free_environment_node(env_list);
}
//export_utils
//zrobione
void	copy_environment_list(t_env_variable *env_list, t_env_variable **new_env_list)
{
	t_env_variable	*current_node;
	t_env_variable	*new_node;
	t_env_variable	*end_node;

	*new_env_list = NULL;
	current_node = env_list;
	while (current_node)
	{
		new_node = ft_malloc(sizeof(t_env_variable));
		new_node->env_name = ft_strdup(current_node->env_name);
		new_node->value = ft_strdup(current_node->value);
		new_node->next_env_var = NULL;
		if (!*new_env_list)
			*new_env_list = new_node;
		else
		{
			end_node = *new_env_list;
			while (end_node->next_env_var)
				end_node = end_node->next_env_var;
			end_node->next_env_var = new_node;
		}
		current_node = current_node->next_env_var;
	}
}
//zrobione
//dla unset i export
void	remove_env_var(char *target_variable, t_env_variable **env_list)
{
	t_env_variable	*current_node;
	t_env_variable	*previous_node;

	current_node = *env_list;
	previous_node = NULL;
	while (current_node)
	{
		if (ft_strncmp(current_node->env_name, target_variable, ft_strlen(target_variable)) == 0)
		{
			if (previous_node)
				previous_node->next_env_var = current_node->next_env_var;
			else
				*env_list = current_node->next_env_var;
			ft_free(current_node->env_name);
			ft_free(current_node->value);
			ft_free(current_node);
			return ;
		}
		previous_node = current_node;
		current_node = current_node->next_env_var;
	}
}

void	sort_environment_variables(t_env_variable *env_var)
{
	t_env_variable	*current_node;
	char		*name_to_swap;
	char		*value_to_swap;

	while (env_var)
	{
		current_node = env_var->next_env_var;
		while (current_node)
		{
			if (ft_strncmp(env_var->env_name, current_node->env_name, ft_strlen(env_var->env_name)) > 0)
			{
				name_to_swap = env_var->env_name;
				value_to_swap = env_var->value;
				env_var->env_name = current_node->env_name;
				env_var->value = current_node->value;
				current_node->env_name = name_to_swap;
				current_node->value = value_to_swap;
			}
			current_node = current_node->next_env_var;
		}
		env_var = env_var->next_env_var;
	}
}
