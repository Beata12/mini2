/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:02:04 by aneekhra          #+#    #+#             */
/*   Updated: 2024/06/14 11:43:08 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_put(char **c, char *a, char d)
{
	int	x;
	int	i;
	int	j;

	i = 0;
	j = 0;
	x = 0;
	while (a[i])
	{
		while (a[i] && a[i] == d)
			i++;
		j = i;
		while (a[i] && a[i] != d)
			i++;
		if (i > j)
		{
			c[x] = ft_malloc(sizeof(char) * (i - j) + 1);
			ft_strncpy(c[x], &a[j], i - j);
			x++;
		}
	}
	c[x] = NULL;
	return (c);
}

char	**ft_split(char *a, char d)
{
	int		j;
	int		i;
	char	**c;

	i = 0;
	j = 0;
	while (a[i])
	{
		while (a[i] && a[i] == d)
			i++;
		if (a[i])
			j++;
		while (a[i] && a[i] != d)
			i++;
	}
	c = ft_malloc(sizeof(char *) * (j + 1));
	c = ft_put(c, a, d);
	return (c);
}

/* #include <stdio.h>
#include <stdlib.h>
#include "libft.h"
int main() {
    char const *sentence = "Hello,world,this,is,a,test";
    char delimiter = ',';
    char **result = ft_split(sentence, delimiter);
    if (result == NULL)
    {
        printf("allocation failed\n");
        return 1;
    }
    printf("After splitting:\n");
    int i = 0;
    while (result[i] != NULL)
    {
        printf("%s\n", result[i]);
        i++;
    }
    char **temp = result;
    while (*temp) {
        free(*temp);
        temp++;
    }
    free(result);
    return 0;
}
 */