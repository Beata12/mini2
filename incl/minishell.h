/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:30:13 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/14 18:49:53 by bmarek           ###   ########.fr       */
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
	t_env_variable		*env;
	t_env_variable		*exported_vars;
	t_token				*token_array;
	t_cmd_arr_str		*command_array;
	t_builtin			*builtin_cmds;
	int					exec_result;
	int					token_count;
	int					command_count;
	int					command_index;
}						t_args;

char			**initialize_envp(char **environment);
char			**generate_envp_array(t_env_variable *env_list);
char			*locate_file_in_path(char *file_name, char *path_to_search);
char			*get_prompt_path(t_args *shell_data);

int				get_char_position(char *input_str, int target_char);
int				process_and_store_env_var(char *input_str,
					t_env_variable **env_list);

void			clear_environment_list(t_env_variable **env_list);
void			close_pipe_descriptors(t_args *shell_data, int **pipes);
void			copy_environment_list(t_env_variable *env_list,
					t_env_variable **new_env_list);
void			exit_with_error(char *str, char *str2, int status);
void			free_command_resources(t_args *shell_data);
void			handle_error(const char *error_message, t_args *s_state,
					int exit_status_code, int modification_flag);
void			handle_sigquit(int sig);
void			initialize_environment(t_args *shell_data, char **env);
void			initialize_pipes(t_args *shell_data, int **pipe_array);
void			initialize_shell(t_args *shell_state, char **environment);
void			load_history(void);
void			process_environment_variables(t_args *shell_data,
					char **args, int i);
void			remove_env_var(char *str, t_env_variable **env);
void			save_history(void);
void			setup_signal_handlers(void);
void			sort_environment_variables(t_env_variable *env_var);
void			wait_for_child_processes(t_args *shell_data);

t_env_variable	*find_env_var(char *name, t_env_variable *env_list);

#endif