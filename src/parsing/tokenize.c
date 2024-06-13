
#include "../../incl/minishell.h"

// int	pass_quoted_str(char *s, char *q)
// {
// 	int	i;

// 	i = 0;
// 	i++;
// 	while (s[i] && s[i] != *q)
// 		i++;
// 	is_open_quote(s[i], q);
// 	// quote_opened_type(s[i], q);
// 	return (i);
// }

// int	pass_str(char *s)
// {
// 	int		i;
// 	char	q;

// 	q = '\0';
// 	i = 0;
// 	while (s[i] && !check_special_symbol(&s[i]) && !is_whitespace(s[i]))
// 	// while (s[i] && !spec_symb(&s[i]) && !is_whitespace(s[i]))
// 	{
// 		is_open_quote(s[i], &q);
// 		// quote_opened_type(s[i], &q);
// 		if (q)
// 		{
// 			i++;
// 			while (s[i] && s[i] != q)
// 				i++;
// 			is_open_quote(s[i], &q);
// 			// quote_opened_type(s[i], &q);
// 		}
// 		i++;
// 	}
// 	return (i);
// }

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
	shell_data->token_array = ft_malloc(sizeof(t_token) * len);
	shell_data->token_count = len;
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

//ZROBIONE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int	validate_token_order(t_args *shell_data)
{
	int		i;
	t_token	*token_array;

	i = 0;
	token_array = shell_data->token_array;
	// while (i < shell_data->tokarr_l)
	// {
	// 	if ((i + 1) >= shell_data->tokarr_l && token_array[i].type == T_PIPE)
	// 		return (my_error(token_array[i].word, shell_data->execution_result = 2), i);
	// 	else if ((i + 1) >= shell_data->tokarr_l && token_array[i].type > 2)
	// 		return (my_error("newline", 2), shell_data->execution_result = 2);
	// 	else if (token_array[i].type > 2 && shell_data->tokarr[i + 1].type > 1)
	// 		return (my_error(token_array[i + 1].word, shell_data->execution_result = 2), i);
	// 	i++;
	// }
	while (i < shell_data->token_count)
	{
		if (token_array[i].type == T_PIPE && ((i - 1) < 0 || (i
					+ 1) >= shell_data->token_count))
			return (my_error(token_array[i].word, shell_data->exec_result = 2), i);
		else if (token_array[i].type > 2 && (i + 1) >= shell_data->token_count)
			return (my_error("newline", 2), shell_data->exec_result = 2);
		else if (token_array[i].type > 2 && shell_data->token_array[i + 1].type > 1)
			return (my_error(token_array[i + 1].word, shell_data->exec_result = 2), i);
		i++;
	}
	return (-1);
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


//UTILS TOKENIZATION
//ZROBIONE I DZIAŁA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int	handle_heredoc_tokens(t_args *shell_data, int end_index)
{
	int	i;
	int	heredoc_index;
	int	heredoc_count;

	// Inicjalizacja liczników
	i = 0;
	heredoc_count = 0;

	// Zliczanie ilości heredoc
	while (i < end_index)
	{
	    // Sprawdź, czy indeks i jest w zakresie tokarr
	    if (shell_data->token_count > i) 
	    {
	        // Sprawdź, czy aktualny token jest heredoc (T_DLESS)
	        if (shell_data->token_array[i].type == T_DLESS)
	        {
	            // Sprawdź, czy następny token istnieje i jest typu T_WORD
	            if ((i + 1) < shell_data->token_count && shell_data->token_array[i + 1].type == T_WORD)
	                heredoc_count++;
	        }
	    }
	    i++;
	}
	// while (i < end_index)
	// {
	// 	if ((shell_data->tokarr_l > i) && shell_data->tokarr[i].type == T_DLESS 
	// 		&& (i + 1) < shell_data->tokarr_l
	// 		&& shell_data->tokarr[i + 1].type == T_WORD)
	// 		heredoc_count++;
	// 	i++;
	// }

	// Jeśli nie znaleziono heredoc, zakończ funkcję
	if (!heredoc_count)
		return (0);

	// Alokowanie pamięci dla cmdarr i ustawienie wartości
	shell_data->command_array = ft_malloc(sizeof(t_cmd_arr_str) * 1);
	shell_data->command_count = 1;
	allocate_command_memory((t_data_counter){.arg_count = 0, .input_count = heredoc_count, .output_count = 0}, shell_data->command_array);

	// Wypełnianie cmdarr danymi z heredoc
	i = 0;
	heredoc_index = -1;
	while (i < end_index)
	{
	    // Sprawdź, czy aktualny token jest typu T_DLESS
	    if (shell_data->token_array[i].type == T_DLESS)
	    {
	        // Zwiększ licznik heredoc_index przed wywołaniem funkcji fill_redir_type
	        heredoc_index++;
	        // Wywołaj funkcję fill_redir_type
	        set_redirection_type(&shell_data->command_array[0].input_tokens[heredoc_index], shell_data->token_array, &i);
	    }
	    // Przejdź do następnego tokena
	    i++;
	}
	// while (i < end_index)
	// {
	// 	if (shell_data->tokarr[i].type == T_DLESS)
	// 		fill_redir_type(&shell_data->cmdarr[0].inp[++heredoc_index], shell_data->tokarr, &i);
	// 	i++;
	// }
	return (heredoc_count);
}
// int	handle_heredoc_tokens(t_args *shell_data, int token_limit)
// {
// 	int	i;
// 	int	in;
// 	int	heredoc;

// 	i = 0;
// 	heredoc = 0;
// 	while (i < token_limit)
// 	{
// 		if ((shell_data->tokarr_l > i) && shell_data->tokarr[i].type == T_DLESS && (i + 1) < shell_data->tokarr_l
// 			&& shell_data->tokarr[i + 1].type == T_WORD)
// 			heredoc++;
// 		i++;
// 	}
// 	if (!heredoc)
// 		return (0);
// 	shell_data->cmdarr = ft_malloc(sizeof(t_cmdarr) * 1);
// 	shell_data->cmdarr_l = 1;
// 	alloc_cmd((t_count){.arg = 0, .in = heredoc, .out = 0}, shell_data->cmdarr);
// 	i = 0;
// 	in = -1;
// 	while (i < token_limit)
// 	{
// 		if (shell_data->tokarr[i].type == T_DLESS)
// 			fill_redir_type(&shell_data->cmdarr[0].inp[++in], shell_data->tokarr, &i);
// 		i++;
// 	}
// 	return (heredoc);
// }
