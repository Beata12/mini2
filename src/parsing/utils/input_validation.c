
#include "../../../incl/minishell.h"

int	unvalid_quotes(char *input_string)
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

int	unvalid_bracket(char *input_string)
{
	int	i;
	int	dif;

	i = 0;
	dif = 0;
	if (missing_bracccet(input_string))
	{
		while (input_string[i])
		{
			if ((input_string[i] != ' ' && input_string[i] != ')'))
				dif = 1;
			{
				if (input_string[i] == ')')
					return (0);
				else if (dif == 0)
				{
					printf("minishell: \
                        syntax error near unexpected token ')' \n");
					return (1);
				}
				dif = 0;
			}
			i++;
		}
	}
	else
		return (1);
	return (0);
}

int	wrong_input(t_args *shell_data, char *input)
{
	(void)shell_data;
    // int pipe_error_flag;
	int	quote_error_flag;
	int	symbol_error_flag;
	// int	bracket_error_flag;

    // pipe_error_flag = 0;
	quote_error_flag = 0;
	symbol_error_flag = 0;
	// bracket_error_flag = 0;
    // pipe_error_flag = unvalid_pipe(input);
	quote_error_flag = unvalid_quotes(input);
	symbol_error_flag = unvalid_symbols(input);
	// bracket_error_flag = unvalid_bracket(input);
	// if (quote_error_flag || symbol_error_flag || bracket_error_flag)
	if (quote_error_flag || symbol_error_flag )
	{
		// shell_data->execution_result = 2;
		if (quote_error_flag)
			my_error((char *)&quote_error_flag, 39);
        // else if (pipe_error_flag)
        //     my_error((char *)&pipe_error_flag, shell_data->execution_result);
		else if (symbol_error_flag)
			my_error((char *)&symbol_error_flag, 2);
		// else if (bracket_error_flag)
		// 	my_error((char *)&bracket_error_flag, 19);
	}
	// else if (empty_input_flag(input))
	// 	shell_data->execution_result = 0;
	else
		return (0);
	return (1);
}
