/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:09:13 by aneekhra          #+#    #+#             */
/*   Updated: 2024/06/11 21:28:53 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	j;
	size_t	l;

	if (!s)
		return (NULL);
	l = ft_strlen(s);
	if (start > l)
		len = 0;
	else if ((len + start) > l)
		len = l - start;
	sub = (char *) malloc((len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	j = start;
	while (i < len && j < l)
	{
		sub[i] = s[j];
		i++;
		j++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_remove_substr(char *str, char *sub)
{
	char	*result;
	char	*found;
	int		len;
	int		new_len;
	int		i;

	result = NULL;
	found = ft_strstr(str, sub);
	if (!str || !sub)
		return (NULL);
	if (found)
	{
		len = ft_strlen(sub);
		new_len = ft_strlen(str) - len;
		result = ft_malloc((new_len + 1) * sizeof(char));
		if (result)
		{
			i = found - str;
			ft_strncpy(result, str, i);
			ft_strncpy(result + i, found + len, new_len - i);
			result[new_len] = '\0';
		}
	}
	return (result);
}
