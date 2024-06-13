
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
	t_env_lst	*export;
	t_env_lst	*env;
	t_token		*tokarr;
	t_cmdarr	*cmdarr;
	t_builtin	*builtin;
	int			execution_result;
	int			exit_status;//to do usuniecia, bo to to samo co execution result tylko zamien wszystkie
	int			tokarr_l;
	int			cmdarr_l;
	int			cmd_num;

}				t_args;

//*UTILS
// void			ignore_signals(void);
char			**get_envp(char **envp);
// void			child_signal(int signal);
// void			handle_sigint(int signals);
void			tmp_sort_env(t_env_lst *env);
int				return_builtin_num(char *cmd);
char			**convert_env(t_env_lst *env);
void			wait_in_parent(t_args *shell_data);
char			*find_path(char *cmd, char *path);
char			*get_prompt_path(t_args *shell_data);//poprawione
char			*find_env(t_env_lst *env, char *name);
char			*ft_remove_substr(char *str, char *sub);
void			open_fds(t_args *shell_data, int **pipes);
void			close_fds(t_args *shell_data, int **pipes);
void			copy_list(t_env_lst *env, t_env_lst **new);
void			remove_one_node(char *str, t_env_lst **env);
void			exit_with_error(char *str, char *str2, int status);
void			export_loop(t_args *shell_data, char **args, int i);
void			handle_error(const char *error_message, t_args *shell_state, int exit_status_code, int modification_flag);// zmienione
// void			ft_error_return(char *str, t_args *shell_data, int status,
// 				int modif);
	// struct.c
void			alloc_err(void);
int				empty_str(char *s);
char			*arrjoin(char **arr);
void			ft_free_array(char **array);
void			clean_lst_env(t_env_lst **lst);
void			clean_node_env(t_env_lst **lst);
void			clean_command_data(t_args *shell_data);
char			**split_save_divider(char *s, char c);
void			initialize_shell(t_args *shell_state, char **environment);//poprawione
int				leave_heredoc(t_args *shell_data, int err_i);
void			ft_lstadd_env(t_env_lst **lst, char *name, char *val);

void			save_history(void);
void			load_history(void);
void			setup_signal_handlers(void);
void			handle_sigquit(int sig);
void			handle_sigint(int sig);

#endif
