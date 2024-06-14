/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:22:12 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/14 15:41:08 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

void	initialize_token_array(char *input_string, t_args *shell_data)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
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

int	skip_special_characters(char *input_string)
{
	int		i;
	char	quote_status;

	i = 0;
	quote_status = '\0';
	while (input_string[i] && !check_special_symbol(&input_string[i])
		&& !is_whitespace(input_string[i]))
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
