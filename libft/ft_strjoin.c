/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:00:05 by aneekhra          #+#    #+#             */
/*   Updated: 2024/06/14 16:47:51 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*a;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	a = malloc(i + j + 1);
	if (!a || !s2)
		return (NULL);
	ft_strcpy(a, s1);
	ft_strcpy(a + i, s2);
	return (a);
}
