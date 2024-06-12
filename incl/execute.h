/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beata <beata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:46:02 by btvildia          #+#    #+#             */
/*   Updated: 2024/06/12 08:38:43 by beata            ###   ########.fr       */
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

typedef struct s_args		t_args;
typedef struct s_env_lst	t_env_lst;

typedef						void(exec_fn)(t_args *shell_data);
typedef struct s_builtin
{
	char					*name;
	exec_fn					*fn_ptr;
}							t_builtin;

// builtins
void						ft_cd(t_args *shell_data);
void						ft_env(t_args *shell_data);
void						ft_pwd(t_args *shell_data);
void						ft_echo(t_args *shell_data);
void						ft_unset(t_args *shell_data);
void						ft_execve(t_args *shell_data);
void						ft_export(t_args *shell_data);
void						init_builtin_arr(t_args *shell_data);
int							ft_exit(t_args *shell_data, char *input);

// execute
void						execute(t_args *shell_data);
void						ft_execute(t_args *shell_data);
int							open_file(char *argv, int i);
void						heredoc_loop(t_args *shell_data, int i);
void						heredoc(t_args *shell_data, int i, int j);
void						ft_piping(t_args *shell_data, int **pipes);
void						open_input_files(t_args *shell_data, int i);
void						open_output_files(t_args *shell_data, int i);

#endif
