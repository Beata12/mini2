/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:30:13 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/14 12:56:31 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_args
{
	t_env_variable		*exported_vars;
	t_env_variable		*env;
	t_token				*token_array;
	t_cmd_arr_str		*command_array;
	t_builtin			*builtin_cmds;
	int					exec_result;
	int					token_count;
	int					command_count;
	int					command_index;
}						t_args;

char			**initialize_envp(char **environment);
void			sort_environment_variables(t_env_variable *env_var);
int				identify_builtin_command(char *cmd);
char			**generate_envp_array(t_env_variable *env_list);
void			wait_for_child_processes(t_args *shell_data);
char			*locate_file_in_path(char *file_name, char *path_to_search);
char			*get_prompt_path(t_args *shell_data);
char			*find_env(t_env_variable *env, char *name);
char			*ft_remove_substr(char *str, char *sub);
void			initialize_pipes(t_args *shell_data, int **pipe_array);
void			close_pipe_descriptors(t_args *shell_data, int **pipes);
void			copy_environment_list(t_env_variable *env_list,
					t_env_variable **new_env_list);
void			remove_env_var(char *str, t_env_variable **env);
void			exit_with_error(char *str, char *str2, int status);
void			process_environment_variables(t_args *shell_data,
					char **args, int i);
void			handle_error(const char *error_message, t_args *s_state,
					int exit_status_code, int modification_flag);
void			alloc_err(void);
int				is_empty_str(char *input_string);
char			*arrjoin(char **arr);
void			ft_free_array(char **array);
void			clear_environment_list(t_env_variable **env_list);
void			free_environment_node(t_env_variable **env_list);
void			free_command_resources(t_args *shell_data);
void			initialize_shell(t_args *shell_state, char **environment);
int				leave_heredoc(t_args *shell_data, int err_i);
void			add_environment_variable(t_env_variable **env_list,
					char *env_name, char *env_value);
void			save_history(void);
void			load_history(void);
void			setup_signal_handlers(void);
void			handle_sigquit(int sig);
void			handle_sigint(int sig);

#endif
