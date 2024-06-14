/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:26:23 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/14 12:26:25 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_alloc.h"

bool	ft_alloc_init(void)
{
	t_allocs	*lst;

	lst = ft_calloc(1, sizeof(t_allocs));
	if (lst == NULL)
		return (false);
	ft_allocs(lst);
	return (true);
}
