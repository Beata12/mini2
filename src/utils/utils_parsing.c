/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 06:41:52 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/14 10:37:05 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

// finds position from start of s.
// Not iteration(from 0), iterates from 1!
//zrobione
//sprawdz ta iteracje od 0 i od 1!!!!!!!!!!!!!!!!!!!!!!!!
int	get_char_position(char *input_str, int target_char)
{
	int	i;

	i = 0;
	while (input_str[i] != (unsigned char)target_char && input_str[i])
		i++;
	if (input_str[i] == (unsigned char)target_char)
		return (++i);
	return (-1);
}

// int	is_empty_str(char *input_string)
// {
// 	if (!input_string)
// 		return (1);
// 	while (*input_string && is_whitespace(*input_string))
// 		input_string++;
// 	if (*input_string)
// 		return (0);
// 	return (1);
// }

// int	leave_heredoc(t_args *shell_data, int err_i)
// {
// 	int	i;
// 	int	in;
// 	int	heredoc;

// 	i = -1;
// 	heredoc = 0;
// 	while (++i < err_i)
// 	{
// 		if ((shell_data->tokarr_l > i) && shell_data->tokarr[i].type
//== T_DLESS && (i + 1) < shell_data->tokarr_l
// 			&& shell_data->tokarr[i + 1].type == T_WORD)
// 			heredoc++;
// 	}
// 	if (!heredoc)
// 		return (0);
// 	shell_data->cmdarr = ft_malloc(sizeof(t_cmdarr) * 1);
// 	shell_data->cmdarr_l = 1;
// 	alloc_cmd((t_count){.arg = 0, .in = heredoc, .out = 0}, shell_data->cmdarr);
// 	i = -1;
// 	in = -1;
// 	while (++i < err_i)
// 	{
// 		if (shell_data->tokarr[i].type == T_DLESS)
// 			fill_redir_type(&shell_data->cmdarr[0].inp[++in],
//shell_data->tokarr, &i);
// 	}
// 	return (heredoc);
// }

// void	init_dst(char **dst, char *src)
// {
// 	char	q;
// 	int		i;
// 	int		d;

// 	i = -1;
// 	d = 0;
// 	q = '\0';
// 	if (!src)
// 		return ;
// 	while (src[++i])
// 	{
// 		is_open_quote(src[i], &q);
// 		// quote_opened_type(src[i], &q);
// 		if (!(((is_whitespace(src[i]) && is_whitespace(src[i + 1]))
//|| (is_whitespace(src[i]) && (!d
// 							|| !src[i + 1]))) && !q))
// 			d++;
// 	}
// 	*dst = (char *)ft_calloc(sizeof(char), d + 1);
// 	if (!*dst)
// 		alloc_err();
// }
