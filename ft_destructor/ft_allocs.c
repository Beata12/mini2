/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_allocs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:26:07 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/14 12:26:54 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_alloc.h"

void	*ft_malloc(size_t size)
{
	t_allocs	*allocs;
	void		*ptr;

	allocs = ft_allocs(NULL);
	if (allocs == NULL)
		return (malloc(size));
	ptr = malloc(size);
	if (ptr == NULL)
	{
		printf("Memory allocation failed\n");
		ft_destructor();
		exit(EXIT_FAILURE);
	}
	add_allocnode(&allocs, create_alloc(ptr));
	return (ptr);
}

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n-- > 0)
		*ptr++ = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = ft_malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
