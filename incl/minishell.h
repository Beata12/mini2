
#ifndef MINISHELL_H
# define MINISHELL_H


# define _POSIX_C_SOURCE 200809L
# define HISTORY_FILE "./.minishell_history"
# define RE "\001\033[0m\002"
# define RED "\001\033[1;31m\002"
# define BLUE "\001\033[1;34m\002"
# define GREEN "\001\033[0;32m\002"
# define YELLOW "\001\033[1;33m\002"
# define MAGENTA "\001\033[0;35m\002"
# define LIGHTGREEN "\001\033[1;32m\002"

# include "../ft_destructor/ft_alloc.h"
# include "../libft/libft.h"
# include "execute.h"
# include "parsing.h"
# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/param.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// extern int		g_signal;

typedef struct s_args
{
	t_env_variable		*export;
	t_env_variable		*env;
	t_token			*tokarr;
	t_cmd_arr_str	*cmdarr;
	t_builtin		*builtin;
	int				execution_result;
	int				exit_status;//to do usuniecia, bo to to samo co execution result tylko zamien wszystkie
	int				tokarr_l;
	int				cmdarr_l;
	int				cmd_num;

}				t_args;

//*UTILS
// void			ignore_signals(void);
char			**initialize_envp(char **environment);//poprawione
// void			child_signal(int signal);
// void			handle_sigint(int signals);
void			sort_environment_variables(t_env_variable *env_var);//zrobione
int				identify_builtin_command(char *cmd);//zrobione
char			**generate_envp_array(t_env_variable *env_list);//poprawione
void			wait_for_child_processes(t_args *shell_data);//poprawione
char			*locate_file_in_path(char *file_name, char *path_to_search);//zrobione
char			*get_prompt_path(t_args *shell_data);//poprawione
char			*find_env(t_env_variable *env, char *name);
char			*ft_remove_substr(char *str, char *sub);
void			initialize_pipes(t_args *shell_data, int **pipe_array);//poprawione
void			close_pipe_descriptors(t_args *shell_data, int **pipes);//poprawione
void			copy_environment_list(t_env_variable *env_list, t_env_variable **new_env_list);//zrobione
void			remove_env_var(char *str, t_env_variable **env);
void			exit_with_error(char *str, char *str2, int status);
void			process_environment_variables(t_args *shell_data, char **args, int i);//zrobione
void			handle_error(const char *error_message, t_args *shell_state, int exit_status_code, int modification_flag);// zmienione
// void			ft_error_return(char *str, t_args *shell_data, int status,
// 				int modif);
	// struct.c
void			alloc_err(void);
int				empty_str(char *s);
char			*arrjoin(char **arr);
void			ft_free_array(char **array);
void			clear_environment_list(t_env_variable **env_list);//zrobione
void			free_environment_node(t_env_variable **env_list);//zrobione
void			free_command_resources(t_args *shell_data);
char			**split_save_divider(char *s, char c);
void			initialize_shell(t_args *shell_state, char **environment);//poprawione
int				leave_heredoc(t_args *shell_data, int err_i);
void			ft_lstadd_env(t_env_variable **lst, char *name, char *val);

void			save_history(void);//poprawione
void			load_history(void);//pooprawione
void			setup_signal_handlers(void);//poprawione
void			handle_sigquit(int sig);//poprawione
void			handle_sigint(int sig);//poprawione

#endif
