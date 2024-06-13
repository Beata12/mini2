
#include "../../incl/minishell.h"

// static int	prepare_split_array(char ***result_array, char *input_str, char separator)
// {
// 	int	i;
// 	int	array_length;

// 	i = -1;
// 	array_length = 1;
// 	while (input_str[++i])
// 	{
// 		if (!i && input_str[0] == seperator)
// 			i++;
// 		if (input_str[i] == separator)
// 			array_length++;
// 	}
// 	*result_array = (char **)ft_calloc(sizeof(char *), array_length + 1);
// 	if (!*result_array)
// 		memory_allocation_error();
// 	return (array_length);
// }

// char	**split_with_separator(char *input_str, char separator)
// {
// 	int		i;
// 	int		arr_index;
// 	int		word_length;
// 	int		array_length;
// 	char	**output;

// 	array_length = prepare_split_array(&output, input_str, separator);
// 	arr_index = 0;
// 	i = 0;
// 	while (array_length--)
// 	{
// 		if (!i && input_str[i] != separator)
// 			word_length = get_char_position(&input_str[i], separator) - 1;
// 		else
// 			word_length = get_char_position(&input_str[i + 1], separator);
// 		output[arr_index] = ft_substr(input_str, i, word_length);
// 		if (!arr[arr_index])
// 			memory_allocation_error();
// 		i += word_length;
// 		arr_index++;
// 	}
// 	return (output);
// }
