/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 08:12:12 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/14 11:16:20 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

int	calculate_trimmed_length(char *input_str)
{
	int				i;
	int				output_index;
	char			quote_status;
	unsigned char	flags;

	i = 0;
	output_index = 0;
	quote_status = '\0';
	while (input_str[i])
	{
		is_open_quote(input_str[i], &quote_status);
		flags = 0;
		flags |= (is_whitespace(input_str[i]) << 0);
		flags |= (is_whitespace(input_str[i + 1]) << 1);
		flags |= ((flags & 0x01) && (!output_index || !input_str[i + 1])) << 2;
		flags |= (((flags & 0x01) && (flags & 0x02)) || (flags & 0x04)) << 3;
		if (!((flags & 0x08) && !quote_status))
			output_index++;
		i++;
	}
	return (output_index);
}

void	initialize_trimmed_string(char **result_str, char *input_str)
{
	int		output_index;

	if (!input_str)
		return ;
	output_index = calculate_trimmed_length(input_str);
	*result_str = (char *)ft_calloc(sizeof(char), output_index + 1);
	if (!*result_str)
		memory_allocation_error();
}

int	is_whitespace(char input_string)
{
	if (input_string == ' ' || input_string == '\t')
		return (1);
	return (0);
}

int	check_special_symbol(char *input_string)
{
	if (*input_string == '|')
		return (1);
	if (*input_string == '<' && (*(input_string + 1) == '<'
			|| *(input_string + 1) == '>'))
		return (2);
	if (*input_string == '>' && *(input_string + 1) == '>')
		return (2);
	return (0);
}

//TO JEST DLA PARSINGU I EXEkucji
// ONE NIE BEDA TUTAJ ALE NA RAZIE SA
char	*find_variable_name(char *input_string)
{
	int		i;
	char	*variable_name;

	i = 0;
	while (1)
	{
		if (!input_string[i] || !(ft_isalnum(input_string[i])
				|| input_string[i] == '_'))
			break ;
		i++;
	}
	while (input_string[i] && (ft_isalnum(input_string[i])
			|| input_string[i] == '_'))
		i++;
	variable_name = ft_substr(input_string, 0, i);
	if (!variable_name)
		memory_allocation_error();
	return (variable_name);
}

t_env_variable	*find_environment_variable(char *name, t_env_variable *env)
{
	while (env)
	{
		if (ft_strlen(name) == ft_strlen(env->env_name) && !ft_strncmp(name,
				env->env_name, ft_strlen(name)))
			return (env);
		env = env->next_env_var;
	}
	return (NULL);
}

// void	initialize_trimmed_string(char **result_str, char *input_str)
// {
// 	int		i;
// 	char	quote_status;
// 	int		output_index;
// 	int		is_current_space;
// 	int		is_next_space;
// 	int		is_start_or_end_space;
// 	int		should_skip_space;
// 	i = 0;
// 	output_index = 0;
// 	is_current_space = 0;
// 	is_next_space = 0;
// 	is_start_or_end_space = 0;
// 	should_skip_space = 0;
// 	quote_status = '\0';
// 	if (!input_str)
// 		return ;
// 	while (input_str[i])
// 	{
// 		is_open_quote(input_str[i], &quote_status);
// 		is_current_space = is_whitespace(input_str[i]);
// 		is_next_space = is_whitespace(input_str[i + 1]);
// 		is_start_or_end_space = (is_current_space && (!output_index
// 					|| !input_str[i + 1]));
// 		should_skip_space = (is_current_space && is_next_space)
// 			|| is_start_or_end_space;
// 		if (!(should_skip_space && !quote_status))
// 			output_index++;
// 		i++;
// 	}
// 	*result_str = (char *)ft_calloc(sizeof(char), output_index + 1);
// 	if (!*result_str)
// 		memory_allocation_error();
// }
// void	initialize_trimmed_string(char **result_str, char *input_str)
// {
// 	int		i;
// 	char	quote_status;
// 	int		output_index;
// 	int		is_current_space = 0;
// 	int		is_next_space = 0;
// 	int		is_start_or_end_space = 0;
// 	int		should_skip_space = 0;
// 	i = 0;
// 	output_index = 0;
// 	quote_status = '\0';
// 	if (!input_str)
// 		return ;
// 	while (input_str[i])
// 	{
// 		is_open_quote(input_str[i], &quote_status);
// 		is_current_space = is_whitespace(input_str[i]);
// 		is_next_space = is_whitespace(input_str[i + 1]);
// 		is_start_or_end_space = (is_current_space && (!output_index 
//|| !input_str[i + 1]));
// 		should_skip_space = (is_current_space && is_next_space) 
//|| is_start_or_end_space;
// 		if (!(should_skip_space && !quote_status))
// 			output_index++;
// 		i++;
// 	}
// 	// while (input_str[i])
// 	// {
// 	// 	is_open_quote(input_str[i], &quote_status);
// 	// 	if (!(((is_whitespace(input_str[i]) && is_whitespace(input_str[i + 1]))
//|| (is_whitespace(input_str[i]) && (!output_index
// 	// 						|| !input_str[i + 1]))) && !quote_status))
// 	// 		output_index++;
// 	// 	i++;
// 	// }
// 	*result_str = (char *)ft_calloc(sizeof(char), output_index + 1);
// 	if (!*result_str)
// 		memory_allocation_error();
// }
// int	is_whitespace(char input_string)
// {
// 	if (input_string == ' ' || input_string == '\t')
// 		return (1);
// 	return (0);
// }
// int	check_special_symbol(char *input_string)
// {
// 	if (*input_string == '|')
// 		return 1;
// 	if (*input_string == '<' && (*(input_string + 1) == '<'
//|| *(input_string + 1) == '>'))
// 	    return 2;
// 	if (*input_string == '>' && *(input_string + 1) == '>')
// 	    return 2;
// 	return 0;
// 	// if (*input_string == '|')
// 	// 	return (1);
// 	// else if (*input_string == '>')
// 	// {
// 	// 	if (*(input_string + 1) && *(input_string + 1) == '>')
// 	// 		return (2);
// 	// 	return (1);
// 	// }
// 	// else if (*input_string == '<')
// 	// {
// 	// 	if ((*(input_string + 1) && *(input_string + 1) == '<')
//|| (*(input_string + 1) && *(s + 1) == '>'))
// 	// 		return (2);
// 	// 	return (1);
// 	// }
// 	// return (0);
// }
// //TO JEST DLA PARSINGU I EXEkucji
// // ONE NIE BEDA TUTAJ ALE NA RAZIE SA
// char	*find_variable_name(char *input_string)
// {
// 	int		i;
// 	char	*variable_name;

// 	i = 0;
// 	while (1)
// 	{
// 	    if (!input_string[i] || !(ft_isalnum(input_string[i])
//|| input_string[i] == '_'))
// 	        break;
// 	    i++;
// 	}
// 	while (input_string[i] && (ft_isalnum(input_string[i])
//|| input_string[i] == '_'))
// 		i++;
// 	variable_name = ft_substr(input_string, 0, i);
// 	if (!variable_name)
// 		memory_allocation_error();
// 	return (variable_name);
// }

// t_env_variable	*find_environment_variable(char *name, t_env_variable *env)
// {
// 	while (env)
// 	{
// 		if (ft_strlen(name) == ft_strlen(env->env_name) && !ft_strncmp(name,
// 				env->env_name, ft_strlen(name)))
// 			return (env);
// 		env = env->next_env_var;
// 	}
// 	return (NULL);
// }