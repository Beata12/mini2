/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_var_expander.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:31:17 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/14 13:38:00 by bmarek           ###   ########.fr       */
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

// static int	should_not_replace(char *input_string, char quote_status)
// {
// 	int	is_first_char_dollar;
// 	int	is_whitespace_or_empty;
// 	int	is_quote_status_single_quote;
// 	int	is_quote_status_valid;
// 	int	is_alnum_or_special_symbol;
// 	int	is_quote_status_allowed;
// 	is_first_char_dollar = (input_string[0] == '$');
// 	is_whitespace_or_empty = (is_whitespace(input_string[1])
// 			|| !input_string[1]);
// 	is_quote_status_single_quote = (quote_status == '\'');
// 	is_quote_status_valid = (quote_status
// 			&& (check_special_symbol(&input_string[1])
// 				|| track_quote(input_string[1])));
// 	is_alnum_or_special_symbol = (!ft_isalnum(input_string[1])
// 			&& !track_quote(input_string[1])
// 			&& !check_special_symbol(&input_string[1])
// 			&& (input_string[1] != '?'));
// 	is_quote_status_allowed = (!quote_status
// 			&& (check_special_symbol(&input_string[1])
// 				|| track_quote(input_string[1])));
// 	if (is_first_char_dollar && !is_whitespace_or_empty
// 		&& !is_quote_status_single_quote
// 		&& !is_quote_status_valid && !is_alnum_or_special_symbol)
// 	{
// 		if (is_quote_status_allowed)
// 			return (1);
// 		else
// 			return (-1);
// 	}
// 	return (0);
// }
// finds part with env_var name in *s, updates *i
//(to pass back in strjoin)
// return env_var value
// static char	*find_replace_env_var
//(char *s, int *i, t_env_lst *env)
// {
// 	char		*find;
// 	t_env_lst	*target;
// 	find = cut_name(&s[*i]);
// 	target = find_env_node(find, env);
// 	*i += ft_strlen(find);
// 	ft_free(find);
// 	if (!target || !target->val)
// 		find = ft_calloc(sizeof(char), 1);
// 	else
// 		find = ft_strdup(target->val);
// 	return (find);
// }
// question sign $? or $?blahd
// return i from which copy str
// static int	question_case(char *s)
// {
// 	if (s[2])
// 		return (2);
// 	else
// 		return (ft_strlen(s));
// }
// static int	not_replace_cases(char *s, char q)
// {
// 	if (s[0] != '$')
// 		return (0);
// 	else if (space(s[1]) || !s[1] || q == '\'' 
//|| (q && (spec_symb(&s[1])
// 				|| quote(s[1]))))
// 		return (0);
// 	else if (!ft_isalnum(s[1]) && !quote(s[1]) 
//&& !spec_symb(&s[1]) && (s[1] != '?'))
// 		return (0);
// 	else if (!q && (spec_symb(&s[1]) || quote(s[1])))
// 		return (1);
// 	return (-1);
// }
// static char	*replace_cases(char *s, t_args *shell_data)
// {
// 	char	*subst;
// 	int		i;
// 	subst = NULL;
// 	if (s[1] == '?')
// 	{
// 		i = question_case(s);
// 		subst = ft_itoa(shell_data->exit_status);
// 	}
// 	else
// 	{
// 		i = 1;
// 		subst = find_replace_env_var(s, &i, shell_data->env);
// 	}
// 	return (ft_strjoin(subst, &s[i]));
// }
// String with one dollar (from splited arr) passed in arg
// void	dollar_value_subst(char **s, char *q, 
//t_args *shell_data)
// {
// 	int		i;
// 	char	*new;
// 	i = not_replace_cases(*s, *q);
// 	if (i >= 0)
// 		new = ft_strdup(&(*s)[i]);
// 	else
// 		new = replace_cases(*s, shell_data);
// 	if (!new)
// 		alloc_err();
// 	i = -1;
// 	while ((*s)[++i])
// 		quote_opened_type((*s)[i], q);
// 	ft_free(*s);
// 	*s = new;
// }