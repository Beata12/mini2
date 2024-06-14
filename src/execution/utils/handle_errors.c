/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:57:30 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/13 21:04:38 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

void	exit_with_error(char *str, char *str2, int status)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, str2, ft_strlen(str2));
	write(2, "\n", 1);
	exit(status);
}

static void	print_shell_error(const char *cmd_name,
			const char *arg_value, const char *error_msg)
{
	const char	*prefix;

	prefix = "minishell: ";
	write(2, prefix, strlen(prefix));
	write(2, cmd_name, strlen(cmd_name));
	write(2, ":", 1);
	if (arg_value && *arg_value)
	{
		write(2, "`", 1);
		write(2, arg_value, strlen(arg_value));
		write(2, "': ", 3);
	}
	write(2, error_msg, strlen(error_msg));
	write(2, "\n", 1);
}

void	handle_error(const char *error_message, t_args *s_state,
		int exit_status_code, int modification_flag)
{
	char		*command_name;
	const char	*error_content;

	command_name = s_state->command_array[s_state->command_index].args[0];
	error_content = NULL;
	if (!strcmp(command_name, "cd"))
	{
		if (modification_flag)
			error_content = "HOME environment variable is not set";
		else
			error_content = "Failed to retrieve current directory";
	}
	else if (!strcmp(command_name, "pwd"))
		error_content = "error retrieving current directory";
	else if (!strcmp(command_name, "exit"))
	{
		if (!modification_flag)
			error_content = "Too many arguments provided";
	}
	else if (!strcmp(command_name, "export"))
		error_content = "Invalid identifier";
	else if (!strcmp(command_name, "unset"))
		error_content = "Not enough arguments provided";
	print_shell_error(command_name, error_message, error_content);
	s_state->exec_result = exit_status_code;
}

// void	handle_error(const char *error_message, t_args *shell_state,
//int exit_status_code, int modification_flag)
// {
// 	// Logic to determine error content based on command name
// 	char *command_name = shell_state->command_array
//[shell_state->command_index].args[0];
// 	const char *error_content = NULL;
// 	// Determine error content based on command name
// 	if (!strcmp(command_name, "cd")) {
// 		if (modification_flag)
// 			error_content = "HOME environment variable is not set";
// 		else
// 			error_content = "Failed to retrieve current directory";
// 	} else if (!strcmp(command_name, "pwd")) {
// 		error_content = "error retrieving current directory";
// 	} else if (!strcmp(command_name, "exit")) {
// 		if (!modification_flag)
// 			error_content = "Too many arguments provided";
// 	} else if (!strcmp(command_name, "export")) {
// 		error_content = "Invalid identifier";
// 	} else if (!strcmp(command_name, "unset")) {
// 		error_content = "Not enough arguments provided";
// 	}
// 	// Call ft_print_err with appropriate arguments
// 	print_shell_error(command_name, error_message, error_content);
// 	// Set exit status
// 	shell_state->exec_result = exit_status_code;
// }