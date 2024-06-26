/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:12:16 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/17 07:48:01 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

static int	unvalid_quotes(char *input_string)
{
	int	i;
	int	single_quote_flag;
	int	double_quote_flag;

	i = 0;
	single_quote_flag = 0;
	double_quote_flag = 0;
	while (input_string[i])
	{
		if (input_string[i] == '\'' && !double_quote_flag)
			single_quote_flag = (single_quote_flag + 1) % 2;
		if (input_string[i] == '\"' && !single_quote_flag)
			double_quote_flag = (double_quote_flag + 1) % 2;
		i++;
	}
	if (single_quote_flag || double_quote_flag)
		return (1);
	return (0);
}

static int	unvalid_symbols(char *input_string)
{
	char	quote_status;

	quote_status = '\0';
	while (*input_string)
	{
		is_open_quote(*input_string, &quote_status);
		if ((*input_string == '&' || *input_string == ';'
				|| *input_string == '\\') && !quote_status)
			return (*input_string);
		input_string++;
	}
	return (0);
}

static int	check_bracket_error(char *input_string)
{
	int	i;
	int	dif;

	i = 0;
	dif = 0;
	while (input_string[i])
	{
		if ((input_string[i] != ' ' && input_string[i] != ')'))
			dif = 1;
		if (input_string[i] == ')')
			return (0);
		else if (dif == 0)
		{
			printf("minishell: syntax error near unexpected token ')' \n");
			return (1);
		}
		dif = 0;
		i++;
	}
	return (0);
}

int	unvalid_bracket(char *input_string)
{
	if (missing_bracccet(input_string))
		return (check_bracket_error(input_string));
	else
		return (1);
}

int	wrong_input(t_args *shell_data, char *input)
{
	int	quote_error_flag;
	int	symbol_error_flag;

	(void)shell_data;
	quote_error_flag = 0;
	symbol_error_flag = 0;
	quote_error_flag = unvalid_quotes(input);
	symbol_error_flag = unvalid_symbols(input);
	if (quote_error_flag || symbol_error_flag)
	{
		if (quote_error_flag)
			my_error((char *)&quote_error_flag, 39);
		else if (symbol_error_flag)
			my_error((char *)&symbol_error_flag, 2);
	}
	else if (*input == ' ' || *input == '\t')
		printf("");
	else if (ft_strlen(input) == 1)
		printf("command not found\n");
	else
		return (0);
	return (1);
}
