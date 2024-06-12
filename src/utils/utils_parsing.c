/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beata <beata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 23:22:23 by dyarkovs          #+#    #+#             */
/*   Updated: 2024/06/12 08:35:30 by beata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

// finds position from start of s.
// Not iteration(from 0), iterates from 1!
int	ft_strchr_pos(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (unsigned char)c && s[i])
		i++;
	if (s[i] == (unsigned char)c)
		return (++i);
	return (-1);
}

int	leave_heredoc(t_args *shell_data, int err_i)
{
	int	i;
	int	in;
	int	heredoc;

	i = -1;
	heredoc = 0;
	while (++i < err_i)
	{
		if ((shell_data->tokarr_l > i) && shell_data->tokarr[i].type == T_HEREDOC && (i + 1) < shell_data->tokarr_l
			&& shell_data->tokarr[i + 1].type == T_WORD)
			heredoc++;
	}
	if (!heredoc)
		return (0);
	shell_data->cmdarr = ft_malloc(sizeof(t_cmdarr) * 1);
	shell_data->cmdarr_l = 1;
	alloc_cmd((t_count){.arg = 0, .in = heredoc, .out = 0}, shell_data->cmdarr);
	i = -1;
	in = -1;
	while (++i < err_i)
	{
		if (shell_data->tokarr[i].type == T_HEREDOC)
			fill_redir_type(&shell_data->cmdarr[0].inp[++in], shell_data->tokarr, &i);
	}
	return (heredoc);
}

int	empty_str(char *s)
{
	if (!s)
		return (1);
	while (*s && space(*s))
		s++;
	if (*s)
		return (0);
	return (1);
}

void	init_dst(char **dst, char *src)
{
	char	q;
	int		i;
	int		d;

	i = -1;
	d = 0;
	q = '\0';
	if (!src)
		return ;
	while (src[++i])
	{
		quote_opened_type(src[i], &q);
		if (!(((space(src[i]) && space(src[i + 1])) || (space(src[i]) && (!d
							|| !src[i + 1]))) && !q))
			d++;
	}
	*dst = (char *)ft_calloc(sizeof(char), d + 1);
	if (!*dst)
		alloc_err();
}
