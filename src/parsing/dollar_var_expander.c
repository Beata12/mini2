/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_var_expander.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:31:17 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/17 07:48:19 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static char	*get_env_var_value(char *input_string, int *i,
		t_env_variable *env)
{
	char			*target_variable;
	t_env_variable	*target_list;

	target_variable = find_variable_name(&input_string[*i]);
	target_list = find_environment_variable(target_variable, env);
	*i += ft_strlen(target_variable);
	ft_free(target_variable);
	if (!target_list || !target_list->value)
		target_variable = ft_calloc(sizeof(char), 1);
	else
		target_variable = ft_strdup(target_list->value);
	return (target_variable);
}

static char	*substitute_special_cases(char *input_string,
		t_args *shell_data)
{
	int		i;
	char	*modified_string;

	modified_string = NULL;
	if (input_string[1] == '?')
	{
		i = process_question_mark(input_string);
		modified_string = ft_itoa(shell_data->exec_result);
	}
	else
	{
		i = 1;
		modified_string = get_env_var_value(input_string, &i,
				shell_data->env);
	}
	return (ft_strjoin(modified_string, &input_string[i]));
}

void	init_should_not_replace_vars(t_should_not_replace_vars *vars,
	char *input_string, char quote_status)
{
	vars->is_first_char_dollar = (input_string[0] == '$');
	vars->is_whitespace_or_empty = (is_whitespace(input_string[1])
			|| !input_string[1]);
	vars->is_quote_status_single_quote = (quote_status == '\'');
	vars->is_quote_status_valid = (quote_status
			&& (check_special_symbol(&input_string[1])
				|| track_quote(input_string[1])));
	vars->is_alnum_or_special_symbol = (!ft_isalnum(input_string[1])
			&& !track_quote(input_string[1])
			&& !check_special_symbol(&input_string[1])
			&& (input_string[1] != '?'));
	vars->is_quote_status_allowed = (!quote_status
			&& (check_special_symbol(&input_string[1])
				|| track_quote(input_string[1])));
}

static int	should_not_replace(char *input_string, char quote_status)
{
	t_should_not_replace_vars	vars;

	init_should_not_replace_vars(&vars, input_string, quote_status);
	if (vars.is_first_char_dollar && !vars.is_whitespace_or_empty
		&& !vars.is_quote_status_single_quote
		&& !vars.is_quote_status_valid && !vars.is_alnum_or_special_symbol)
	{
		if (vars.is_quote_status_allowed)
			return (1);
		else
			return (-1);
	}
	return (0);
}

void	expand_dollar_variables(char **input_string,
		char *quote_status, t_args *shell_data)
{
	int		i;
	char	*updated_string;

	i = should_not_replace(*input_string, *quote_status);
	if (i >= 0)
		updated_string = ft_strdup(&(*input_string)[i]);
	else
		updated_string = substitute_special_cases(*input_string, shell_data);
	if (!updated_string)
		memory_allocation_error();
	i = 0;
	while ((*input_string)[i])
	{
		is_open_quote((*input_string)[i], quote_status);
		i++;
	}
	ft_free(*input_string);
	*input_string = updated_string;
}
