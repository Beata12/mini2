
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
	init_tokarr(input_string, shell_data);
	while (input_string[++i])
	{
		if (space(input_string[i]))
			continue ;
		shell_data->tokarr[token_index].type = token_typizator(&input_string[i]);
		token_length = spec_symb(&input_string[i]);
		if (!token_length)
			token_length = pass_str(&input_string[i]);
		shell_data->tokarr[token_index].word = ft_substr(input_string, i, token_length--);
		i += token_length;
		token_index++;
	}
}

// cmdarr [{args - arr[char *],
// inp - arr[word - file, type - type red_inp/heredoc],
// out - arr[word - file, type - type red_out/append]}, {args, inp, out}];
static void	create_cmdarr(t_args *shell_data)
{
	int	c;
	int	t;

	init_cmdarr(shell_data);
	c = -1;
	t = 0;
	while (++c < shell_data->cmdarr_l)
	{
		fill_cmd(c, &t, shell_data);
		t++;
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
	split_tokens(processed_input, shell_data);
	token_status = token_order_check(shell_data);
	if (token_status >= 0)
	{
		if (!leave_heredoc(shell_data, token_status))
		{
			return(0);
		}
	}
	open_quotes(shell_data);
	if (token_status < 0)
		create_cmdarr(shell_data);
	shell_data->exit_status = 0;
	return (ft_free(processed_input), 1);
}

		// shell_data->exit_status = 2;