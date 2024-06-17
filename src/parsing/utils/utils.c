/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 08:12:12 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/17 07:48:13 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

int	calculate_trimmed_length(char *input_str)
{
	int				i;
	int				output_index;
	char			quote_status;
	unsigned char	flags;

	i = 0;
	output_index = 0;
	quote_status = '\0';
	while (input_str[i])
	{
		is_open_quote(input_str[i], &quote_status);
		flags = 0;
		flags |= (is_whitespace(input_str[i]) << 0);
		flags |= (is_whitespace(input_str[i + 1]) << 1);
		flags |= ((flags & 0x01) && (!output_index || !input_str[i + 1])) << 2;
		flags |= (((flags & 0x01) && (flags & 0x02)) || (flags & 0x04)) << 3;
		if (!((flags & 0x08) && !quote_status))
			output_index++;
		i++;
	}
	return (output_index);
}

void	initialize_trimmed_string(char **result_str, char *input_str)
{
	int		output_index;

	if (!input_str)
		return ;
	output_index = calculate_trimmed_length(input_str);
	*result_str = (char *)ft_calloc(sizeof(char), output_index + 1);
	if (!*result_str)
		memory_allocation_error();
}

int	is_whitespace(char input_string)
{
	if (input_string == ' ' || input_string == '\t')
		return (1);
	return (0);
}

int	check_special_symbol(char *input_string)
{
	if (*input_string == '|')
		return (1);
	if (*input_string == '<' && (*(input_string + 1) == '<'
			|| *(input_string + 1) == '>'))
		return (2);
	if (*input_string == '>' && *(input_string + 1) == '>')
		return (2);
	return (0);
}

void	process_string(char *src, char *result)
{
	int		i;
	int		output_index;
	char	quote_status;

	i = 0;
	output_index = 0;
	quote_status = '\0';
	while (src[i])
	{
		is_open_quote(src[i], &quote_status);
		if (is_whitespace(src[i]) && is_whitespace(src[i + 1]) && !quote_status)
		{
			i++;
			continue ;
		}
		if (is_whitespace(src[i]) && (!output_index || !src[i + 1])
			&& !quote_status)
		{
			i++;
			continue ;
		}
		result[output_index++] = src[i];
		i++;
	}
	result[output_index] = '\0';
}
