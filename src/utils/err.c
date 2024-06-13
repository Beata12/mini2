
// #include "../../incl/minishell.h"

// // void	alloc_err(void)
// // {
// // 	exit(printf(RED "Allocation failed\n" RE));
// // }

// void	exit_with_error(char *str, char *str2, int status)
// {
// 	write(2, "minishell: ", 11);
// 	write(2, str, ft_strlen(str));
// 	write(2, str2, ft_strlen(str2));
// 	write(2, "\n", 1);
// 	exit(status);
// }

// // static void	ft_print_err(char *cmd, char *arg, char *content)
// // {
// // 	write(2, "minishell: ", 11);
// // 	write(2, cmd, ft_strlen(cmd));
// // 	write (2, ":", 2);
// // 	if (*arg)
// // 	{
// // 		write(2, "`", 1);
// // 		write(2, arg, ft_strlen(arg));
// // 		write(2, "': ", 2);
// // 	}
// // 	write(2, content, ft_strlen(content));
// // 	write(2, "\n", 1);
// // }

// // static void ft_print_err(const char *cmd, const char *arg, const char *content)
// // {
// //     write(2, "minishell: ", 11);
// //     write(2, cmd, strlen(cmd));
// //     write(2, ":", 1);
// //     if (arg && *arg)
// //     {
// //         write(2, "`", 1);
// //         write(2, arg, strlen(arg));
// //         write(2, "': ", 3);
// //     }
// //     write(2, content, strlen(content));
// //     write(2, "\n", 1);
// // }
// static void print_shell_error(const char *cmd_name, const char *arg_value, const char *error_msg)
// {
//     const char *prefix = "minishell: ";
//     write(2, prefix, strlen(prefix));
//     write(2, cmd_name, strlen(cmd_name));
//     write(2, ":", 1);
//     if (arg_value && *arg_value)
//     {
//         write(2, "`", 1);
//         write(2, arg_value, strlen(arg_value));
//         write(2, "': ", 3);
//     }
//     write(2, error_msg, strlen(error_msg));
//     write(2, "\n", 1);
// }
// // static void ft_print_err2(const char *cmd, const char *arg, const char *content)
// // {
// //     fprintf(stderr, "Error in command '%s': %s - %s\n", cmd, arg, content);
// // }

// void handle_error(const char *error_message, t_args *shell_state, int exit_status_code, int modification_flag)
// {
//     // Logic to determine error content based on command name
//     char *command_name = shell_state->cmdarr[shell_state->cmd_num].args[0];
//     const char *error_content = NULL;

//     // Determine error content based on command name
//     if (!strcmp(command_name, "cd")) {
//         if (modification_flag)
//             error_content = "HOME environment variable is not set";
//         else
//             error_content = "Failed to retrieve current directory";
//     } else if (!strcmp(command_name, "pwd")) {
//         error_content = "error retrieving current directory";
//     } else if (!strcmp(command_name, "exit")) {
//         if (!modification_flag)
//             error_content = "Too many arguments provided";
//     } else if (!strcmp(command_name, "export")) {
//         error_content = "Invalid identifier";
//     } else if (!strcmp(command_name, "unset")) {
//         error_content = "Not enough arguments provided";
//     }

//     // Call ft_print_err with appropriate arguments
//     print_shell_error(command_name, error_message, error_content);

//     // Set exit status
//     shell_state->exit_status = exit_status_code;
// }

// // void	ft_error_return(char *str, t_args *shell_data, int status, int modif)
// // {
// // 	char	*name;
// // 	char	*content;

// // 	content = NULL;
// // 	name = shell_data->cmdarr[shell_data->cmd_num].args[0];
// // 	if (!ft_strcmp(name, "cd") && modif)
// // 		content = "HOME not set";
// // 	else if (!ft_strcmp(name, "cd") && !modif)
// // 		content = "No such file or directory";
// // 	else if (!ft_strcmp(name, "pwd"))
// // 		content = "error retrieving current directory";
// // 	else if (!ft_strcmp(name, "exit") && !modif)
// // 		content = "too many arguments";
// // 	else if (!ft_strcmp(name, "export"))
// // 		content = "not a valid identifier";
// // 	else if (!ft_strcmp(name, "unset"))
// // 		content = "not enough arguments";
// // 	ft_print_err(name, str, content);
// // 	shell_data->exit_status = status;
// // }
