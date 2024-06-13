
#include "../../incl/minishell.h"

static int	init_split_save_divider(char ***dst, char *s, char c)
{
	int	i;
	int	len;

	i = -1;
	len = 1;
	while (s[++i])
	{
		if (!i && s[0] == c)
			i++;
		if (s[i] == c)
			len++;
	}
	*dst = (char **)ft_calloc(sizeof(char *), len + 1);
	if (!*dst)
		memory_allocation_error();
	return (len);
}

// searches for divider and preserve it!
//->put divider as a start of each arr[str] $part $part ...
char	**split_save_divider(char *s, char c)
{
	int		i;
	int		a_i;
	int		w_l;
	int		len;
	char	**arr;

	len = init_split_save_divider(&arr, s, c);
	a_i = 0;
	i = 0;
	while (len--)
	{
		if (!i && s[i] != c)
			w_l = ft_strchr_pos(&s[i], c) - 1;
		else
			w_l = ft_strchr_pos(&s[i + 1], c);
		arr[a_i] = ft_substr(s, i, w_l);
		if (!arr[a_i])
			memory_allocation_error();
		i += w_l;
		a_i++;
	}
	return (arr);
}
