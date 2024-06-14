/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 07:32:02 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/14 13:38:10 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

void	free_string_array(char **string_array)
{
	int	i;

	i = 0;
	if (string_array == NULL)
		return ;
	while (string_array[i] != NULL)
	{
		ft_free(string_array[i]);
		i++;
	}
	ft_free(string_array);
}

char	*combine_strings(char **string_array)
{
	int		i;
	char	*final_string;

	i = 0;
	while (string_array[i])
	{
		if (!i)
			final_string = ft_strdup(string_array[i]);
		if (string_array[i + 1])
			final_string = ft_strjoin(final_string, string_array[i + 1]);
		if (!final_string)
			memory_allocation_error();
		i++;
	}
	return (final_string);
}

int	process_question_mark(char *input_string)
{
	if (input_string[2])
		return (2);
	else
		return (ft_strlen(input_string));
}
