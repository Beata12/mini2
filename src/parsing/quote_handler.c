
#include "../../incl/minishell.h"

static char	*allocate_unquoted_string(t_token current_token)
{
	int		i;
	char	quote_status;
	char	*processed_word;

	i = 0;
	quote_status = '\0';
	// while (*current_token.word && current_token.type == T_WORD)
	// {
	// 	if (!(quote_status == *current_token.word || (!quote_status && *current_token.word == quote(*current_token.word))))
	// 	{
	// 		i++;
	// 	}
	// 	quote_opened_type(*current_token.word, &quote_status);
	// 	current_token.word++;
	// }
	while (*current_token.word && current_token.type == T_WORD)
	{
		char current_char = *current_token.word;

		if (quote_status == current_char || (!quote_status && current_char != track_quote(current_char)))
			is_open_quote(current_char, &quote_status);
		if (!(quote_status == current_char || (!quote_status && current_char == track_quote(current_char))))
			i++;
		current_token.word++;
	}
	processed_word = ft_calloc(sizeof(char), i + 1);
	if (!processed_word)
		memory_allocation_error();
	return (processed_word);
}

static void	remove_token_quotes(t_token *current_token)
{
	int		i;
	int		new_index;
	char	quote_status;
	char	*processed_word;

	i = 0;
	new_index = 0;
	quote_status = '\0';
	if (current_token->type > T_WORD)
		return ;
	processed_word = allocate_unquoted_string(*current_token);
	while (current_token->word[i])
	{
	    // Sprawdzenie, czy bieżący znak otwiera cudzysłów
	    if (quote_status == current_token->word[i])
	    {
	        // Zaktualizuj stan cudzysłowu i przejdź do następnego znaku
	        is_open_quote(current_token->word[i], &quote_status);
	    }
	    else if (!quote_status && current_token->word[i] == track_quote(current_token->word[i]))
	    {
	        // Zaktualizuj stan cudzysłowu i przejdź do następnego znaku
	        is_open_quote(current_token->word[i], &quote_status);
	    }
	    else
	    {
	        // Dodaj znak do processed_word, jeśli nie jest częścią cudzysłowu
	        processed_word[new_index] = current_token->word[i];
	        new_index++;
	    }

	    // Przejdź do następnego znaku
	    i++;
	}
	// while (current_token->word[i])
	// {
	// 	if (!(quote_status == current_token->word[i] || (!quote_status && current_token->word[i] == quote(current_token->word[i]))))
	// 	{
	// 		processed_word[new_index] = current_token->word[i];
	// 		new_index++;
	// 	}
	// 	quote_opened_type(current_token->word[i], &quote_status);
	// 	i++;
	// }
	ft_free(current_token->word);
	current_token->word = processed_word;
}

void	remove_all_quotes(t_args *shell_data)
{
	int		i;

	i = 0;
	while (i < shell_data->token_count)
	{
		remove_token_quotes(&shell_data->token_array[i]);
		i++;
	}
}

// void	open_quotes(t_args *shell_data)
// {
// 	int		a_i;

// 	a_i = -1;
// 	while (++a_i < shell_data->tokarr_l)
// 		open_token_quotes(&shell_data->tokarr[a_i]);
// }
