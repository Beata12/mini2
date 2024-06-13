/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:30:01 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/13 20:39:50 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_args		t_args;
typedef struct s_builtin	t_builtin;

typedef enum e_token_types
{
	T_WORD,
	T_RED_TO,	//>
	T_RED_FROM,	//<
	T_DLESS,	//<<
	T_DGREAT,	//>>
	// T_UNDEFINED,// *notdefined - DO USUNIECIA< NIE UZYWANE
	T_PIPE,		//|
}						t_token_types;

typedef struct s_token
{
	char					*word;
	t_token_types			type;
}							t_token;

typedef struct s_cmd_arr_str
{
	char					**args;
	int						input_length;
	int						output_length;
	t_token					*input_tokens;
	t_token					*output_tokens;
}							t_cmd_arr_str;

typedef struct s_data_counter
{
	int						arg_count;
	int						input_count;
	int						output_count;
}							t_data_counter;

typedef struct s_env_variable
{
	char					*value;
	char					*env_name;
	struct s_env_variable	*next_env_var;
}							t_env_variable;

//to nie do parsingu find_env, proccesss, initialize - do exec
t_env_variable		*find_env_var(char *name, t_env_variable *env_list);
void				initialize_environment(t_args *shell_data, char **env);
int					process_and_store_env_var(char *input_str,
						t_env_variable **env_list);
void				dollar_value_subst(char **s, char *q,
						t_args *shell_data);
int					get_char_position(char *input_str, int target_char);
char				*get_variable_name(char *input_str);
void				fill_redir_type(t_token *rdr, t_token *tarr,
						int *t);

//NOWE
void				my_error(char *c, int type);
int					parse_input(char *input, t_args *shell_data);
int					wrong_input(t_args *shell_data, char *input);
t_token_types		token_typizator(char *input_string);
void				is_open_quote(char input_string, char *quote_flag);
int					track_quote(char input_string);
int					missing_bracccet(char *input_string);
char				*combine_strings(char **string_array);
int					is_whitespace(char input_string);
void				initialize_trimmed_string(char **result_str,
						char *input_str);
int					check_special_symbol(char *input_string);
void				memory_allocation_error(void);
char				**divide_and_store(char *input_string, char separator);
void				free_string_array(char **string_array);
void				expand_dollar_variables(char **input_string,
						char *quote_status, t_args *shell_data);
char				*find_variable_name(char *input_string);
t_env_variable		*find_environment_variable(char *name, t_env_variable *env);
void				initialize_token_array(char *input_string,
						t_args *shell_data);
int					skip_special_characters(char *input_string);
int					validate_token_order(t_args *shell_data);
int					handle_heredoc_tokens(t_args *shell_data, int err_i);
void				remove_all_quotes(t_args *shell_data);
void				initialize_command_array(t_args *shell_data);
void				initialize_command(int command_counter,
						int *token_counter, t_args *shell_data);
void				allocate_command_memory(t_data_counter cmd_sizes,
						t_cmd_arr_str *command);
void				parse_and_fill_command(int cmd, int *tok,
						t_args *shell_data);
void				handle_double_redirection(t_token *redirection_token,
						t_token *token_array, int *token_index);
void				set_redirection_type(t_token *redirection_token,
						t_token *token_array, int *token_index);

#endif
