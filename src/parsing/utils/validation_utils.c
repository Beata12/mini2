
#include "../../../incl/minishell.h"

int	track_quote(char input_string)
{
	if (input_string == '\"')
		return ('\"');
	if (input_string == '\'')
		return ('\'');
	else
		return (0);
}

void	is_open_quote(char input_string, char *quote_flag)
{
	if ((track_quote(input_string)) && !*quote_flag)
		*quote_flag = input_string;
	else if ((track_quote(input_string)) && *quote_flag == input_string)
		*quote_flag = '\0';
}

void	my_error(char *s, int status)
{
	printf("minishell: ");
	// if (status == 19)
	// 	printf("syntax error unable to locate closing bracket\n");
	if (status == 2)
		printf("syntax error near unexpected token `%s'\n", s);
	if (status == 39)
		printf("syntax error unable to locate closing quotation\n");
	if (status == 0)
		printf("warning: shell level (1000) too high, resetting to 1\n");
}

int	missing_bracccet(char *input_string)
{
	int	i;
	int	open_bracket;
	int	closed_bracket;

	i = 0;
	open_bracket = 0;
	closed_bracket = 0;
	while (input_string[i])
	{
		if (input_string[i] == '(')
			open_bracket = 1;
		if (input_string[i] == ')' && open_bracket)
			closed_bracket = 1;
		i++;
	}
	if (open_bracket && closed_bracket)
		return (1);
	return (0);
}