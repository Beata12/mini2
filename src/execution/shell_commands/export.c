/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beata <beata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 09:58:45 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/13 11:51:48 by beata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/execute.h"

// void shell_export(t_args *shell_data)
// {
//     t_cmdarr *cmdarr_struct = shell_data->cmdarr;

//     if (!cmdarr_struct) {
//         fprintf(stderr, "shell_export: cmdarr is NULL\n");
//         return;
//     }

//     char **cmdarr = cmdarr_struct->args;
//     int i = 1;
//     char *key;
//     char *value;

//     while (cmdarr[i] != NULL) {
//         key = strtok(cmdarr[i], "=");
//         value = strtok(NULL, "=");

//         if (key && value) {
//             if (setenv(key, value, 1) != 0) {
//                 perror("export");
//                 return;
//             }
//         } else {
//             fprintf(stderr, "export: invalid format\n");
//             return;
//         }
//         i++;
//     }
// }

void	shell_export(t_args *shell_data)
{
	char	**args;

	args = shell_data->cmdarr[shell_data->cmd_num].args;
	if (args[1] == NULL)
	{
		copy_list(shell_data->env, &shell_data->export);
		remove_one_node("_", &shell_data->export);
		tmp_sort_env(shell_data->export);
		shell_env(shell_data);
		clean_lst_env(&shell_data->export);
		shell_data->exit_status = 0;
	}
	else
		export_loop(shell_data, args, 1);
}

// void shell_export(t_args *shell_data)
// {
//     char **command_line_args;
    
//     command_line_args = shell_data->cmdarr[shell_data->cmd_num].args;
//     if (command_line_args[1] == NULL)
//     {
//         // Handle export without arguments
//         copy_list(shell_data->env, &shell_data->export);
//         remove_one_node("_", &shell_data->export);
//         tmp_sort_env(shell_data->export);
//         shell_env(shell_data);
//         clean_lst_env(&shell_data->export);
//         shell_data->exit_status = 0;
//     }
//     else
//         export_loop(shell_data, command_line_args, 1);
// }

// void	shell_export(t_args *shell_data)
// {
// 	char	**args;

// 	args = shell_data->cmdarr[shell_data->cmd_num].args;
// 	if (args[1] == NULL)
// 	{
// 		copy_list(shell_data->env, &shell_data->export);
// 		remove_one_node("_", &shell_data->export);
// 		tmp_sort_env(shell_data->export);
// 		shell_env(shell_data);
// 		clean_lst_env(&shell_data->export);
// 		shell_data->exit_status = 0;
// 	}
// 	else
// 		export_loop(shell_data, args, 1);
// }



// void shell_export(Token *args) {
//     extern char **environ;

//     if (args[1].value == NULL) {
//         // No argument, print all environment variables
//         for (char **env = environ; *env != 0; env++) {
//             printf("%s\n", *env);
//         }
//     } else {
//         // Parse the argument
//         char *name = strtok(args[1].value, "=");
//         char *value = strtok(NULL, "=");

//         if (name && value) {
//             // Check for invalid name format (optional)
//             if (strcspn(name, " \t\n=") != strlen(name)) {
//                 fprintf(stderr, "minishell: export: invalid variable name\n");
//                 return;
//             }

//             // Find if the variable already exists
//             int index = find_env_var(name);
//             if (index != -1) {
//                 // Replace existing value
//                 size_t len = strlen(name) + strlen(value) + 2;
//                 char *new_env_var = malloc(len);
//                 snprintf(new_env_var, len, "%s=%s", name, value);
//                 environ[index] = new_env_var;
//             } else {
//                 // Add new environment variable
//                 size_t len = strlen(name) + strlen(value) + 2;
//                 char *new_env_var = malloc(len);
//                 snprintf(new_env_var, len, "%s=%s", name, value);

//                 // Count current environment variables
//                 int env_count = 0;
//                 while (environ[env_count] != NULL) {
//                     env_count++;
//                 }

//                 // Allocate space for the new environment variable
//                 environ = realloc(environ, (env_count + 2) * sizeof(char *));
//                 environ[env_count] = new_env_var;
//                 environ[env_count + 1] = NULL;
//             }
//         } else {
//             fprintf(stderr, "minishell: export: invalid format\n");
//         }
//     }
// }


// {
//	 char *equals = strchr(arg, '=');

//	 if (!equals)
// 	{
//		 fprintf(stderr, "Invalid argument format: %s\n", arg);
//		 return 1;
//	 }
//	 *equals = '\0';  // Splitting the argument into variable name and value
//	 int result = setenv(arg, equals + 1, 1); // Setting the environment variable
//	 if (result != 0)
// 	{
//		 perror("setenv");
//		 return 1;
//	 }
//	 return 0;
// }

// int main(int argc, char *argv[])
// {
//	 int result = shell_export(argv[1]);

//	 if (argc != 2)
// 	{
//		 fprintf(stderr, "Usage: %s <variable=value>\n", argv[0]);
//		 return 1;
//	 }
//	 if (result != 0)
// 	{
//		 fprintf(stderr, "Error: Failed to export variable\n");
//		 return 1;
//	 }
//	 printf("Variable exported successfully\n");
//	 return 0;
// }

//	check like this:
//	./a.out MY_VAR=my_value

// int shell_export(char **args) {
//	 if (!args[1])
// 	{
//		 fprintf(stderr, "export: missing argument\n");
//		 return 1;
//	 }
//	 if (putenv(args[1]) != 0)
// 	{
//		 perror("export");
//		 return 1;
//	 }
//	 return 0;
// }

// int main(int argc, char *argv[]) 
// {
//	 int result = shell_export(&argv[1]);

//	 if (argc != 2) {
//		 fprintf(stderr, "Usage: %s <variable=value>\n", argv[0]);
//		 exit(1);
//	 }
//	 if (result != 0) {
//		 fprintf(stderr, "Error: Failed to export variable\n");
//		 exit(1);
//	 }
//	 printf("Variable exported successfully\n");
//	 return 0;
// }