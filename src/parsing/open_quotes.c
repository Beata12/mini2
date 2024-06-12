/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beata <beata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:35:43 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/06/12 08:37:22 by beata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static char	*alloc_new_tok_len(t_token tok)
{
	char	q;
	int		len;
	char	*new;

	q = '\0';
	len = 0;
	while (*tok.word && tok.type == T_WORD)
	{
		if (!(q == *tok.word || (!q && *tok.word == quote(*tok.word))))
		{
			len++;
		}
		quote_opened_type(*tok.word, &q);
		tok.word++;
	}
	new = ft_calloc(sizeof(char), len + 1);
	if (!new)
		alloc_err();
	return (new);
}

static void	open_token_quotes(t_token *tok)
{
	char	q;
	int		i;
	int		n_i;
	char	*new;

	q = '\0';
	i = -1;
	n_i = 0;
	if (tok->type > T_WORD)
		return ;
	new = alloc_new_tok_len(*tok);
	while (tok->word[++i])
	{
		if (!(q == tok->word[i] || (!q && tok->word[i] == quote(tok->word[i]))))
		{
			new[n_i] = tok->word[i];
			n_i++;
		}
		quote_opened_type(tok->word[i], &q);
	}
	ft_free(tok->word);
	tok->word = new;
}

void	open_quotes(t_args *shell_data)
{
	int		a_i;

	a_i = -1;
	while (++a_i < shell_data->tokarr_l)
		open_token_quotes(&shell_data->tokarr[a_i]);
}
