
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
		while (head->next)
			head = head->next;
		head->next = node;
	}
	node->name = name;
	node->val = val;
	node->next = NULL;
}

void	free_environment_node(t_env_variable **env_list)
{
	t_env_variable	*next_node;

	next_node = (*env_list)->next;
	ft_free((*env_list)->name);
	if ((*env_list)->val)
		ft_free((*env_list)->val);
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
		new_node->name = ft_strdup(current_node->name);
		new_node->val = ft_strdup(current_node->val);
		new_node->next = NULL;
		if (!*new_env_list)
			*new_env_list = new_node;
		else
		{
			end_node = *new_env_list;
			while (end_node->next)
				end_node = end_node->next;
			end_node->next = new_node;
		}
		current_node = current_node->next;
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
		if (ft_strncmp(current_node->name, target_variable, ft_strlen(target_variable)) == 0)
		{
			if (previous_node)
				previous_node->next = current_node->next;
			else
				*env_list = current_node->next;
			ft_free(current_node->name);
			ft_free(current_node->val);
			ft_free(current_node);
			return ;
		}
		previous_node = current_node;
		current_node = current_node->next;
	}
}

void	sort_environment_variables(t_env_variable *env_var)
{
	t_env_variable	*current_node;
	char		*name_to_swap;
	char		*value_to_swap;

	while (env_var)
	{
		current_node = env_var->next;
		while (current_node)
		{
			if (ft_strncmp(env_var->name, current_node->name, ft_strlen(env_var->name)) > 0)
			{
				name_to_swap = env_var->name;
				value_to_swap = env_var->val;
				env_var->name = current_node->name;
				env_var->val = current_node->val;
				current_node->name = name_to_swap;
				current_node->val = value_to_swap;
			}
			current_node = current_node->next;
		}
		env_var = env_var->next;
	}
}
