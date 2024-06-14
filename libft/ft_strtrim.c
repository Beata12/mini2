/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:59:25 by aneekhra          #+#    #+#             */
/*   Updated: 2024/06/14 11:56:11 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s1, char *set)
{
	unsigned int	i;
	unsigned int	j;
	char			*a;

	a = 0;
	if (!s1 || !set)
		return (a);
	if (s1 != 0 && set != 0)
	{
		i = 0;
		j = ft_strlen(s1);
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		while (j > i && s1[j - 1] && ft_strchr(set, s1[j - 1]))
			j--;
		a = (char *)ft_malloc(sizeof(char) * (j - i + 1));
		if (!a)
			return (NULL);
		ft_strncpy(a, s1 + i, j - i);
	}
	return (a);
}
