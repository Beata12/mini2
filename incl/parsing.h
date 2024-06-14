/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:30:01 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/14 18:45:47 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_args		t_args;
typedef struct s_builtin	t_builtin;

typedef enum e_token_types
{
	T_UNDEFINED,// *notdefined - DO USUNIECIA< NIE UZYWANE
	T_WORD,
	T_RED_TO,	//>
	T_RED_FROM,	//<
	T_DLESS,	//<<
	T_DGREAT,	//>>
	T_PIPE,		//|
}						t_token_types;

typedef struct s_token
{
	char					*word;
	t_token_types			type;
}							t_token;

typedef struct s_parse_state
{
	int	*current_input;
	int	*current_output;
	int	*current_arg;
	int	*token_index;
}				t_parse_state;

typedef struct s_should_not_replace_vars
{
	int	is_first_char_dollar;
	int	is_whitespace_or_empty;
	int	is_quote_status_single_quote;
	int	is_quote_status_valid;
	int	is_alnum_or_special_symbol;
	int	is_quote_status_allowed;
}				t_should_not_replace_vars;

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

char			*combine_strings(char **string_array);
char			**divide_and_store(char *input_string, char separator);

int				check_special_symbol(char *input_string);
int				handle_heredoc_tokens(t_args *shell_data, int err_i);
int				is_whitespace(char input_string);
int				missing_bracccet(char *input_string);
int				parse_input(char *input, t_args *shell_data);
int				process_question_mark(char *input_string);
int				skip_special_characters(char *input_string);
int				track_quote(char input_string);
int				validate_token_order(t_args *shell_data);
int				wrong_input(t_args *shell_data, char *input);

void			allocate_command_memory(t_data_counter cmd_sizes,
					t_cmd_arr_str *command);
void			expand_dollar_variables(char **input_string,
					char *quote_status, t_args *shell_data);
char			*find_variable_name(char *input_string);
void			free_string_array(char **string_array);
void			handle_double_redirection(t_token *redirection_token,
					t_token *token_array, int *token_index);
void			is_open_quote(char input_string, char *quote_flag);
void			initialize_command(int command_counter,
					int *token_counter, t_args *shell_data);
void			initialize_command_array(t_args *shell_data);
void			initialize_token_array(char *input_string,
					t_args *shell_data);
void			initialize_trimmed_string(char **result_str,
					char *input_str);
void			my_error(char *c, int type);
void			memory_allocation_error(void);
void			parse_and_fill_command(int cmd, int *tok,
					t_args *shell_data);
void			process_string(char *src, char *result);
void			remove_all_quotes(t_args *shell_data);
void			set_redirection_type(t_token *redirection_token,
					t_token *token_array, int *token_index);

t_env_variable	*find_environment_variable(char *name, t_env_variable *env);
t_token_types	token_typizator(char *input_string);

#endif
