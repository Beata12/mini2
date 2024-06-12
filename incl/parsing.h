
#ifndef PARSING_H
# define PARSING_H

typedef struct s_args		t_args;
typedef struct s_builtin	t_builtin;

typedef enum e_token_types
{
	T_WORD,		// word, string, file, cmd ...
	T_RED_TO,	//>
	T_RED_FROM,	//<
	T_DLESS,	//<<
	T_DGREAT,	//>>
	T_UNDEFINED,// *notdefined - DO USUNIECIA< NIE UZYWANE
	T_PIPE,		//|
}							t_token_types;

// typedef enum e_type
// {
// 	T_NDEF,		// *notdefined
// 	T_WORD,		// word, string, file, cmd ...
// 	T_PIPE,		//|
// 	T_HEREDOC,	//<<
// 	T_RED_INP,	//<
// 	T_APPEND,	//>>
// 	T_RED_OUT,	//>
// }							t_type;

typedef struct s_token
{
	char					*word;
	t_token_types					type;
}							t_token;

typedef struct s_cmdarr
{
	char					**args;
	t_token					*inp; // arr[struct{word, type}];
	t_token					*out; // arr[struct{word, type}];
	int						inp_l;
	int						out_l;
}							t_cmdarr;

typedef struct s_count
{
	int						arg;
	int						in;
	int						out;
}							t_count;

typedef struct s_env_lst
{
	char					*val;
	char					*name;
	struct s_env_lst		*next;
}							t_env_lst;

// err check
void						my_error(char *c, int type);
int							wrong_input(t_args *shell_data, char *input);
int							token_order_check(t_args *shell_data);
// parsing
void						init_env(t_args *shell_data, char **env);
int							fill_str(char *s, t_env_lst **lst);
int							parse_input(char *input, t_args *shell_data);
void						dollar_value_subst(char **s, char *q,
								t_args *shell_data);
void						open_quotes(t_args *shell_data);
void						fill_cmd(int cmd, int *tok, t_args *shell_data);
// parsing utils
int							space(char c);
int							quote(char c);
int							spec_symb(char *s);
void						quote_opened_type(char c, char *q);
int							pass_str(char *s);
int							ft_strchr_pos(char *s, int c);
int							env_lst_len(t_env_lst *lst);
t_env_lst					*find_env_node(char *name, t_env_lst *env);
char						*cut_name(char *s);
void						init_dst(char **dst, char *src);
void						init_tokarr(char *s, t_args *shell_data);
void						init_cmdarr(t_args *shell_data);
void						init_cmd(int c, int *t, t_args *shell_data);
void						alloc_cmd(t_count sizes, t_cmdarr *cmd);
t_token_types				token_typizator(char *s);
void						fill_redir_type(t_token *rdr, t_token *tarr,
								int *t);
void						print_cmds(t_args *shell_data);
void						print_env(t_env_lst *env);

//NOWE
void						is_open_quote(char input_string, char *quote_flag);
int							track_quote(char input_string);
int							missing_bracccet(char *input_string);
char						*combine_strings(char **string_array);
int							is_whitespace(char input_string);
void						initialize_trimmed_string(char **result_str, char *input_str);
void						is_open_quote(char input_string, char *quote_flag);
int							check_special_symbol(char *input_string);
void						memory_allocation_error(void);
char						**divide_and_store(char *input_string, char separator);
void						free_string_array(char **string_array);
void						expand_dollar_variables(char **input_string, char *quote_status, t_args *shell_data);
char						*find_variable_name(char *input_string);
t_env_lst					*find_environment_variable(char *name, t_env_lst *env);
void						initialize_token_array(char *input_string, t_args *shell_data);
int							skip_special_characters(char *input_string);

#endif
