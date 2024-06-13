
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
void						shell_cd(t_args *shell_data);
void						shell_env(t_args *shell_data);
void						shell_pwd(t_args *shell_data);
void						ft_echo(t_args *shell_data);
void						ft_unset(t_args *shell_data);
void						ft_execve(t_args *shell_data);
void						shell_export(t_args *shell_data);
void						initialize_builtins(t_args *shell_data);
int							shell_exit(t_args *shell_data, char *input);

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
