/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 06:36:10 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/17 07:48:24 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static char	*remove_extra_spaces(char *src)
{
	char	*result;

	result = NULL;
	initialize_trimmed_string(&result, src);
	process_string(src, result);
	return (result);
}

static void	expand_env_variables(char **input_string, t_args *shell_data)
{
	int		i;
	char	quote_status;
	char	**divided_strings;

	i = 0;
	quote_status = '\0';
	divided_strings = divide_and_store(*input_string, '$');
	while (divided_strings[i])
	{
		expand_dollar_variables(&divided_strings[i], &quote_status, shell_data);
		i++;
	}
	ft_free(*input_string);
	*input_string = combine_strings(divided_strings);
	free_string_array(divided_strings);
}

static void	split_tokens(char *input_string, t_args *shell_data)
{
	int	i;
	int	token_index;
	int	token_length;

	i = -1;
	token_index = 0;
	initialize_token_array(input_string, shell_data);
	while (input_string[++i])
	{
		if (is_whitespace(input_string[i]))
			continue ;
		shell_data->token_array[token_index].type
			= token_typizator(&input_string[i]);
		token_length = check_special_symbol(&input_string[i]);
		if (!token_length)
			token_length = skip_special_characters(&input_string[i]);
		shell_data->token_array[token_index].word = ft_substr(input_string,
				i, token_length--);
		i += token_length;
		token_index++;
	}
}

static void	create_and_fill_commands(t_args *shell_data)
{
	int	token_counter;
	int	command_counter;

	initialize_command_array(shell_data);
	token_counter = 0;
	command_counter = 0;
	while (command_counter < shell_data->command_count)
	{
		parse_and_fill_command(command_counter, &token_counter, shell_data);
		token_counter++;
		command_counter++;
	}
}

int	parse_input(char *input, t_args *shell_data)
{
	char	*processed_input;
	char	token_status;

	if (wrong_input(shell_data, input))
		return (0);
	processed_input = remove_extra_spaces(input);
	expand_env_variables(&processed_input, shell_data);
	split_tokens(processed_input, shell_data);
	token_status = validate_token_order(shell_data);
	if (token_status >= 0)
	{
		if (!handle_heredoc_tokens(shell_data, token_status))
			return (0);
	}
	remove_all_quotes(shell_data);
	if (token_status < 0)
		create_and_fill_commands(shell_data);
	shell_data->exec_result = 0;
	return (ft_free(processed_input), 1);
}
