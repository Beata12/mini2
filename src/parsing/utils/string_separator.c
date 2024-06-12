
#include "../../../incl/minishell.h"

static int	initialize_and_count_divisions(char ***result_array, char *input_string, char separator)
{
	int	i;
	int	len;

	i = 0;
	len = 1;
	while (input_string[i])
	{
	    if (input_string[i] == separator)
	        len++;
	    i++;
	    if (i == 1 && input_string[0] == separator)
	        i++;
	}
	// while (input_string[i])
	// {
	// 	if (!i && input_string[0] == separator)
	// 		i++;
	// 	if (input_string[i] == separator)
	// 		len++;
	// 	i++;
	// }
	*result_array = (char **)ft_calloc(sizeof(char *), len + 1);
	if (!*result_array)
		memory_allocation_error();
	return (len);
}

// searches for divider and preserve it!
//->put divider as a start of each arr[str] $part $part ...
char	**divide_and_store(char *input_string, char separator)
{
	int		i;
	int		array_index;
	int		word_length;
	int		length;
	char	**string_array;

	i = 0;
	array_index = 0;
	length = initialize_and_count_divisions(&string_array, input_string, separator);
	while (length)
	{
		//string_pos musisz poprawic!!!!!!!!!!!!!!!!!!!!!!
		if (!i && input_string[i] != separator)
			word_length = ft_strchr_pos(&input_string[i], separator) - 1;
		else
			word_length = ft_strchr_pos(&input_string[i + 1], separator);
		string_array[array_index] = ft_substr(input_string, i, word_length);
		if (!string_array[array_index])
			memory_allocation_error();
		i += word_length;
		array_index++;
		length--;
	}
	// while (length--)
	// {
	// 	if (!i && input_string[i] != separator)
	// 		word_length = ft_strchr_pos(&input_string[i], separator) - 1;
	// 	else
	// 		word_length = ft_strchr_pos(&input_string[i + 1], separator);
	// 	string_array[array_index] = ft_substr(input_string, i, word_length);
	// 	if (!string_array[array_index])
	// 		memory_allocation_error();
	// 	i += word_length;
	// 	array_index++;
	// }
	return (string_array);
}
