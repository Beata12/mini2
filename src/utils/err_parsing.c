
#include "../../incl/minishell.h"

int	token_order_check(t_args *shell_data)
{
	int		i;
	t_token	*arr;

	i = -1;
	arr = shell_data->tokarr;
	while (++i < shell_data->tokarr_l)
	{
		if (arr[i].type == T_PIPE && ((i - 1) < 0 || (i
					+ 1) >= shell_data->tokarr_l))
			return (my_error(arr[i].word, shell_data->exit_status = 2), i);
		else if (arr[i].type > 2 && (i + 1) >= shell_data->tokarr_l)
			return (my_error("newline", 2), shell_data->exit_status = 2);
		else if (arr[i].type > 2 && shell_data->tokarr[i + 1].type > 1)
			return (my_error(arr[i + 1].word, shell_data->exit_status = 2), i);
	}
	return (-1);
}
// int	unvalid_quotes(char *input_string)
// {
// 	int	i;
// 	int	single_quote_flag;
// 	int	double_quote_flag;

// 	i = 0;
// 	single_quote_flag = 0;
// 	double_quote_flag = 0;
// 	while (input_string[i])
// 	{
// 		if (input_string[i] == '\'' && !double_quote_flag)
// 			single_quote_flag = (single_quote_flag + 1) % 2;
// 		if (input_string[i] == '\"' && !single_quote_flag)
// 			double_quote_flag = (double_quote_flag + 1) % 2;
// 		i++;
// 	}
// 	if (single_quote_flag || double_quote_flag)
// 		return (1);
// 	return (0);
// }
// static int	unvalid_quotes(char *s)
// {
// 	int	i;
// 	int	single_q;
// 	int	double_q;

// 	single_q = 0;
// 	double_q = 0;
// 	i = -1;
// 	while (s[++i])
// 	{
// 		if (s[i] == '\'' && !double_q)
// 			single_q = (single_q + 1) % 2;
// 		if (s[i] == '\"' && !single_q)
// 			double_q = (double_q + 1) % 2;
// 	}
// 	return (single_q || double_q);
// }


// static int	unvalid_symbols(char *input_string)
// {
// 	char	quote_status;

// 	quote_status = '\0';
// 	while (*input_string)
// 	{
// 		is_open_quote(*input_string, &quote_status);
// 		if ((*input_string == '&' || *input_string == ';'
// 				|| *input_string == '\\') && !quote_status)
// 			return (*input_string);
// 		input_string++;
// 	}
// 	return (0);
// }

// void	my_error(char *s, int status)
// {
// 	printf("minishell: ");
// 	if (status == 2)
// 		printf("syntax error near unexpected token `%s'\n", s);
// 	if (status == 39)
// 		printf("syntax error unable to locate closing quotation\n");
// 	if (status == 0)
// 		printf("warning: shell level (1000) too high, resetting to 1\n");
// }

// int	wrong_input(t_args *shell_data, char *input)
// {
// 	(void)shell_data;
//     // int pipe_error_flag;
// 	int	quote_error_flag;
// 	int	symbol_error_flag;
// 	// int	bracket_error_flag;

//     // pipe_error_flag = 0;
// 	quote_error_flag = 0;
// 	symbol_error_flag = 0;
// 	// bracket_error_flag = 0;
//     // pipe_error_flag = unvalid_pipe(input);
// 	quote_error_flag = unvalid_quotes(input);
// 	symbol_error_flag = unvalid_symbols(input);
// 	// bracket_error_flag = unvalid_bracket(input);
// 	// if (quote_error_flag || symbol_error_flag || bracket_error_flag)
// 	if (quote_error_flag || symbol_error_flag )
// 	{
// 		// shell_data->execution_result = 2;
// 		if (quote_error_flag)
// 			my_error((char *)&quote_error_flag, 39);
//         // else if (pipe_error_flag)
//         //     my_error((char *)&pipe_error_flag, shell_data->execution_result);
// 		else if (symbol_error_flag)
// 			my_error((char *)&symbol_error_flag, 2);
// 		// else if (bracket_error_flag)
// 		// 	my_error((char *)&bracket_error_flag, 19);
// 	}
// 	// else if (empty_input_flag(input))
// 	// 	shell_data->execution_result = 0;
// 	else
// 		return (0);
// 	return (1);
// }
// int	wrong_input(t_args *shell_data, char *input)
// {
// 	int	err_quote;
// 	int	err_symb;

// 	err_quote = 0;
// 	err_symb = 0;
// 	err_quote = not_closed_quotes(input);
// 	err_symb = not_valid_symbols(input);
// 	if (err_quote || err_symb)
// 	{
// 		shell_data->exit_status = 2;
// 		if (err_quote)
// 			my_error((char *)&err_quote, 39);
// 		else if (err_symb)
// 			my_error((char *)&err_symb, shell_data->exit_status);	
// 	}
// 	else if (empty_str(input))
// 		shell_data->exit_status = 0;
// 	else
// 		return (0);
// 	return (1);
// }
