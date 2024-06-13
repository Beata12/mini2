
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
void						shell_echo(t_args *shell_data);
void						shell_unset(t_args *shell_data);
void						shell_export(t_args *shell_data);
void						initialize_builtins(t_args *shell_data);
int							shell_exit(t_args *shell_data, char *input);

// execute
void						ft_execve(t_args *shell_data);//zrobione
void						execute(t_args *shell_data);//zrobione
void						ft_execute(t_args *shell_data);//zrobione
int							manage_file_access(char *file_path, int file_flags);//zrobione
void						process_all_heredocs(t_args *shell_data, int command_index);//poprawione
void						execute_heredoc(t_args *shell_data, int command_index, int input_index);//poprawione
void						execute_pipeline(t_args *shell_data, int **pipe_array);//poprawione
void						setup_input_redirection(t_args *shell_data, int command_index);//poprawione
void						setup_output_redirection(t_args *shell_data, int command_index);//poprawione

#endif
