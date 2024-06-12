
#include "../../incl/minishell.h"

static char	*remove_extra_spaces(char *src)
{
	int		i;
	int		output_index;
	char	quote_status;
	char	*result;

	i = 0;
	output_index = 0;
	quote_status = '\0';
	result = NULL;
	initialize_trimmed_string(&result, src);
	// while (src[i])
	// {
	// 	quote_opened_type(src[i], &quote_status);
	// 	if (!(((is_whitespace(src[i]) && is_whitespace(src[i + 1])) || (is_whitespace(src[i]) && (!output_index
	// 						|| !src[i + 1]))) && !quote_status))
	// 		result[output_index++] = src[i];
	// 	i++;
	// }
	while (src[i])
	{
		is_open_quote(src[i], &quote_status);
		if (is_whitespace(src[i]) && is_whitespace(src[i + 1]) && !quote_status)
		{
			i++;
			continue;
		}
		if (is_whitespace(src[i]) && (!output_index || !src[i + 1]) && !quote_status)
		{
			i++;
			continue;
		}
		result[output_index++] = src[i];
		i++;
	}
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
	// while (1)
	// {
	//     if (!divided_strings[i])
	//         break;
	//     expand_dollar_variables(&divided_strings[i], &quote_status, shell_data);
	//     i++;
	// }
	while (divided_strings[i])
	{
		expand_dollar_variables(&divided_strings[i], &quote_status, shell_data);
		i++;
	}
	ft_free(*input_string);
	*input_string = combine_strings(divided_strings);
	free_string_array(divided_strings);
}

// static void	expand_env_variables(char **s, t_args *shell_data)
// {
// 	char	**dllr_arr;
// 	int		i;
// 	char	q;

// 	dllr_arr = split_save_divider(*s, '$');
// 	q = '\0';
// 	i = -1;
// 	while (dllr_arr[++i])
// 		dollar_value_subst(&dllr_arr[i], &q, shell_data);
// 	ft_free(*s);
// 	*s = arrjoin(dllr_arr);
// 	ft_free_array(dllr_arr);
// }


//ZROBIONE I DZIALA!!!!!!!!!!!!!!!!!!!!!!!!!!!!
static void	split_tokens(char *input_string, t_args *shell_data)
{
	int	i;
	int	token_index;
	int	token_length;

	i = -1;
	token_index = 0;
	initialize_token_array(input_string, shell_data);//nie działa poprawnie
	// init_tokarr(input_string, shell_data);
	while (input_string[++i])
	{
		if (is_whitespace(input_string[i]))
			continue ;
		shell_data->tokarr[token_index].type = token_typizator(&input_string[i]);
		token_length = check_special_symbol(&input_string[i]);//DZIAŁA!!!!!!!!!!!!1
		// token_length = spec_symb(&input_string[i]);
		if (!token_length)
			// token_length = pass_str(&input_string[i]);
			token_length = skip_special_characters(&input_string[i]);//DZIAŁA!!!!!!!!!!!!!!!!!!
		shell_data->tokarr[token_index].word = ft_substr(input_string, i, token_length--);
		i += token_length;
		token_index++;
	}
}

// cmdarr [{args - arr[char *],
// inp - arr[word - file, type - type red_inp/heredoc],
// out - arr[word - file, type - type red_out/append]}, {args, inp, out}];
static void	create_and_fill_commands(t_args *shell_data)
{
	int	token_counter;
	int	command_counter;

	initialize_command_array(shell_data);//SKONCNZONE i dziala
	token_counter = 0;
	command_counter = 0;
	while (command_counter < shell_data->cmdarr_l)
	{
		parse_and_fill_command(command_counter, &token_counter, shell_data);//tutaj
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
	expand_env_variables(&processed_input, shell_data);//ZROBIONE
	split_tokens(processed_input, shell_data);//ZROBIONE I Dziala
	token_status = validate_token_order(shell_data);// dzIALA NO LEAKS, ok
	// token_status = token_order_check(shell_data);
	if (token_status >= 0)
	{
		if (!handle_heredoc_tokens(shell_data, token_status))//ZROBIONE I DZIALA
			return(0);
	}
	remove_all_quotes(shell_data);// ZROBIONE I DZIALA
	if (token_status < 0)
		create_and_fill_commands(shell_data);//ROBIE TERAZ
	shell_data->exit_status = 0;
	return (ft_free(processed_input), 1);
}

		// shell_data->exit_status = 2;