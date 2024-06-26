/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:18:14 by aneekhra          #+#    #+#             */
/*   Updated: 2024/06/14 12:01:10 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_int_lent(int nb)
{
	int	s;

	if (nb == 0)
	{
		return (1);
	}
	s = 0;
	if (nb < 0)
	{
		s = 1;
	}
	while (nb)
	{
		s++;
		nb = nb / 10;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	unsigned int	i;
	char			*a;
	int				x;

	x = ft_int_lent(n);
	a = ft_malloc((x + 1) * sizeof(char));
	if (!a)
		return (NULL);
	if (n < 0)
	{
		a[0] = '-';
		i = -n;
	}
	else
	{
		i = n;
	}
	a[x - 1] = '0';
	a[x] = '\0';
	while (i)
	{
		a[--x] = (i % 10) + '0';
		i = i / 10;
	}
	return (a);
}
