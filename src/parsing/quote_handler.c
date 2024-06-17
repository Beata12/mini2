/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:31:17 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/17 07:48:29 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static char	*allocate_unquoted_string(t_token current_token)
{
	int		i;
	char	quote_status;
	char	*processed_word;
	char	current_char;

	i = 0;
	quote_status = '\0';
	while (*current_token.word && current_token.type == T_WORD)
	{
		current_char = *current_token.word;
		if (quote_status == current_char || (!quote_status
				&& current_char != track_quote(current_char)))
			is_open_quote(current_char, &quote_status);
		if (!(quote_status == current_char || (!quote_status
					&& current_char == track_quote(current_char))))
			i++;
		current_token.word++;
	}
	processed_word = ft_calloc(sizeof(char), i + 1);
	if (!processed_word)
		memory_allocation_error();
	return (processed_word);
}

static char	*process_word(t_token current_token)
{
	int		i;
	int		new_index;
	char	quote_status;
	char	*processed_word;

	i = 0;
	new_index = 0;
	quote_status = '\0';
	processed_word = allocate_unquoted_string(current_token);
	while (current_token.word[i])
	{
		if (quote_status == current_token.word[i])
			is_open_quote(current_token.word[i], &quote_status);
		else if (!quote_status && current_token.word[i]
			== track_quote(current_token.word[i]))
			is_open_quote(current_token.word[i], &quote_status);
		else
		{
			processed_word[new_index] = current_token.word[i];
			new_index++;
		}
		i++;
	}
	processed_word[new_index] = '\0';
	return (processed_word);
}

static void	remove_token_quotes(t_token *current_token)
{
	char	*processed_word;

	if (current_token->type > T_WORD)
		return ;
	processed_word = process_word(*current_token);
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
