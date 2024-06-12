
#include "../../incl/minishell.h"

int	pass_quoted_str(char *s, char *q)
{
	int	i;

	i = 0;
	i++;
	while (s[i] && s[i] != *q)
		i++;
	quote_opened_type(s[i], q);
	return (i);
}

int	pass_str(char *s)
{
	int		i;
	char	q;

	q = '\0';
	i = 0;
	while (s[i] && !spec_symb(&s[i]) && !space(s[i]))
	{
		quote_opened_type(s[i], &q);
		if (q)
		{
			i++;
			while (s[i] && s[i] != q)
				i++;
			quote_opened_type(s[i], &q);
		}
		i++;
	}
	return (i);
}

//ZROBIONE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void	initialize_token_array(char *input_string, t_args *shell_data)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	// while (input_string[++i])
	// {
	// 	if (!is_whitespace(input_string[i]))
	// 	{
	// 		if (check_special_symbol(&input_string[i]) && check_special_symbol(&input_string[i]) == 2)
	// 			i++;
	// 		else
	// 			i += skip_special_characters(&input_string[i]) - 1;
	// 		len++;
	// 	}
	// }
	while (input_string[++i])
	{
		if (is_whitespace(input_string[i]))
			continue ;
		if (check_special_symbol(&input_string[i]))
		{
			if (check_special_symbol(&input_string[i]) == 2)
				i++;
		}
		else
			i += skip_special_characters(&input_string[i]) - 1;
		len++;
	}
	shell_data->tokarr = ft_malloc(sizeof(t_token) * len);
	shell_data->tokarr_l = len;
}

// void	init_tokarr(char *s, t_args *shell_data)
// {
// 	int		len;
// 	int		i;

// 	len = 0;
// 	i = -1;
// 	while (s[++i])
// 	{
// 		if (space(s[i]))
// 			continue ;
// 		if (spec_symb(&s[i]))
// 		{
// 			if (spec_symb(&s[i]) == 2)
// 				i++;
// 		}
// 		else
// 			i += pass_str(&s[i]) - 1;
// 		len++;
// 	}
// 	shell_data->tokarr = ft_malloc(sizeof(t_token) * len);
// 	shell_data->tokarr_l = len;
// }

//ZROBIONE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
t_token_types	token_typizator(char *input_string)
{
	if (*input_string == '|')
		return (T_PIPE);
	else if (*input_string == *(input_string + 1) && *input_string == '<')
		return (T_DLESS);
	else if (*input_string == '<')
		return (T_RED_FROM);
	else if (*input_string == *(input_string + 1) && *input_string == '>')
		return (T_DGREAT);
	else if (*input_string == '>')
		return (T_RED_TO);
	else
		return (T_WORD);
}

//ZROBIONE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int	skip_special_characters(char *input_string)
{
	int		i;
	char	quote_status;

	i = 0;
	quote_status = '\0';
	while (input_string[i] && !check_special_symbol(&input_string[i]) && !is_whitespace(input_string[i]))
	{
		is_open_quote(input_string[i], &quote_status);
		if (quote_status)
		{
			i++;
			while (input_string[i] && input_string[i] != quote_status)
				i++;
			is_open_quote(input_string[i], &quote_status);
		}
		i++;
	}
	return (i);
}

// //arg - &s[i] ptr on needed str part
// t_type	token_typizator(char *s)
// {
// 	if (*s == '|')
// 		return (T_PIPE);
// 	else if (*s == *(s + 1) && *s == '<')
// 		return (T_HEREDOC);
// 	else if (*s == '<')
// 		return (T_RED_INP);
// 	else if (*s == *(s + 1) && *s == '>')
// 		return (T_APPEND);
// 	else if (*s == '>')
// 		return (T_RED_OUT);
// 	else
// 		return (T_WORD);
// }
