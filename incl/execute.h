/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:30:07 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/14 18:46:57 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../ft_destructor/ft_alloc.h"
# include "../libft/libft.h"
# include "minishell.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_args			t_args;
typedef struct s_env_variable	t_env_variable;

typedef					void(command_executor)(t_args *shell_data);

typedef struct s_builtin
{
	char				*env_name;
	command_executor	*command_executor;
}							t_builtin;

int		shell_exit(t_args *shell_data, char *input);

void	initialize_builtins(t_args *shell_data);
void	shell_cd(t_args *shell_data);
void	shell_echo(t_args *shell_data);
void	shell_env(t_args *shell_data);
void	shell_export(t_args *shell_data);
void	shell_pwd(t_args *shell_data);
void	shell_unset(t_args *shell_data);
void	execute(t_args *shell_data);
void	execute_pipeline(t_args *shell_data,
			int **pipe_array);
void	ft_execve(t_args *shell_data);
void	ft_execute(t_args *shell_data);
void	process_all_heredocs(t_args *shell_data,
			int command_index);
void	setup_input_redirection(t_args *shell_data,
			int command_index);
void	setup_output_redirection(t_args *shell_data,
			int command_index);

#endif

// int		manage_file_access(char *file_path, int file_flags);
// void	execute_heredoc(t_args *shell_data,
// 			int command_index, int input_index);