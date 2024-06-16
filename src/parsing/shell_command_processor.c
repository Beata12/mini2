/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_command_processor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 07:15:52 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/16 16:36:42 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	set_redirection_type(t_token *redirection_token,
		t_token *token_array, int *token_index)
{
	redirection_token->type = token_array[*token_index].type;
	(*token_index)++;
	if (!token_array[*token_index].word)
		memory_allocation_error();
	redirection_token->word = ft_strdup(token_array[*token_index].word);
}

static void	handle_double_redirection(t_token *redirection_token,
		t_token *token_array, int *token_index)
{
	set_redirection_type(redirection_token, token_array, token_index);
	(*token_index)--;
	token_array[*token_index].type = T_RED_TO;
}

static void	process_token(int command_index, t_parse_state *state,
		t_args *shell_data)
{
	t_token	*current_token;

	current_token = &shell_data->token_array[*state->token_index];
	if (current_token->type == T_RED_FROM
		&& check_special_symbol(current_token->word) == 2)
		handle_double_redirection(&shell_data->command_array
		[command_index].input_tokens[++(*state->current_input)],
			shell_data->token_array, state->token_index);
	else if (current_token->type == T_RED_FROM
		|| current_token->type == T_DLESS)
		set_redirection_type(&shell_data->command_array
		[command_index].input_tokens
		[++(*state->current_input)], shell_data->token_array,
			state->token_index);
	else if (current_token->type == T_RED_TO || current_token->type == T_DGREAT)
		set_redirection_type(&shell_data->command_array
		[command_index].output_tokens[++(*state->current_output)],
			shell_data->token_array, state->token_index);
	else
		shell_data->command_array[command_index].args
		[++(*state->current_arg)] = current_token->word;
	(*state->token_index)++;
}

void	parse_and_fill_command(int command_index, int *token_index,
	t_args *shell_data)
{
	int				current_input;
	int				current_output;
	int				current_arg;
	t_parse_state	state;

	current_input = -1;
	current_output = -1;
	current_arg = -1;
	state.current_input = &current_input;
	state.current_output = &current_output;
	state.current_arg = &current_arg;
	state.token_index = token_index;
	while (*token_index < shell_data->token_count
		&& shell_data->token_array[*token_index].type != T_PIPE)
	{
		process_token(command_index, &state, shell_data);
	}
}
// static void	process_token(int command_index, int *token_index,
// 		t_args *shell_data, int *current_input,
//int *current_output, int *current_arg)
// {
// 	t_token	*current_token;
// 	current_token = &shell_data->token_array[*token_index];
// 	if (current_token->type == T_RED_FROM
// 		&& check_special_symbol(current_token->word) == 2)
// 		handle_double_redirection(&shell_data->command_array
// 		[command_index].input_tokens[++(*current_input)],
// 			shell_data->token_array, token_index);
// 	else if (current_token->type == T_RED_FROM
// 		|| current_token->type == T_DLESS)
// 		set_redirection_type(&shell_data->command_array
// 		[command_index].input_tokens
// 		[++(*current_input)], shell_data->token_array, token_index);
// 	else if (current_token->type == T_RED_TO || current_token->type == T_DGREAT)
// 		set_redirection_type(&shell_data->command_array
// 		[command_index].output_tokens[++(*current_output)],
// 			shell_data->token_array, token_index);
// 	else
// 		shell_data->command_array[command_index].args
// 		[++(*current_arg)] = current_token->word;
// 	(*token_index)++;
// }
// void	parse_and_fill_command(int command_index, int *token_index,
// 	t_args *shell_data)
// {
// 	int	current_input;
// 	int	current_output;
// 	int	current_arg;
// 	current_input = -1;
// 	current_output = -1;
// 	current_arg = -1;
// 	while (*token_index < shell_data->token_count
// 		&& shell_data->token_array[*token_index].type != T_PIPE)
// 	{
// 		process_token(command_index, token_index, shell_data,
// 			&current_input, &current_output, &current_arg);
// 	}
// }
// void set_redirection_type(t_token *redirection_token, 
//t_token *token_array, int *token_index)
// {
// 	// Przypisz typ z aktualnego tokena do redirection_token
// 	redirection_token->type = token_array[*token_index].type;
// 	// Przejdź do następnego tokena
// 	(*token_index)++;
// 	// Sprawdź, czy następny token ma słowo, jeśli nie, wywołaj błąd
// 	if (!token_array[*token_index].word)
// 		memory_allocation_error();
// 	// Przypisz skopiowane słowo z token_array do redirection_token
// 	redirection_token->word = ft_strdup(token_array[*token_index].word);
// }
// //zrobione
// void handle_double_redirection(t_token *redirection_token, t_token 
//*token_array, int *token_index)
// {
// 	// Wypełnij szczegóły przekierowania
// 	set_redirection_type(redirection_token, token_array, token_index);
// 	// Zmniejsz wskaźnik tokena o 1
// 	(*token_index)--;
// 	// Zmień typ tokena na T_RED_TO
// 	token_array[*token_index].type = T_RED_TO;
// }
// //zrobione
// static void process_token(int command_index, int *token_index,
//t_args *shell_data, int *current_input, int *current_output, int *current_arg)
// {
//     t_token *current_token = &shell_data->token_array[*token_index];
//     if (current_token->type == T_RED_FROM
//&& check_special_symbol(current_token->word) == 2)
//         handle_double_redirection(&shell_data->command_array
//[command_index].input_tokens[++(*current_input)],
//shell_data->token_array, token_index);
//     else if (current_token->type == T_RED_FROM 
//|| current_token->type == T_DLESS)
//         set_redirection_type(&shell_data->command_arra
//[command_index].input_tokens
//[++(*current_input)], shell_data->token_array, token_index);
//     else if (current_token->type == T_RED_TO 
//|| current_token->type == T_DGREAT)
//         set_redirection_type(&shell_data->command_array
//[command_index].output_tokens
//[++(*current_output)], shell_data->token_array, token_index);
//     else
//         shell_data->command_array[command_index].args[++(*current_arg)]
//= current_token->word;
//     (*token_index)++;
// }
// //zrobione
// void parse_and_fill_command(int command_index, int *token_index,
//t_args *shell_data)
// {
//     int current_input = -1;
//     int current_output = -1;
//     int current_arg = -1;
//     while (*token_index < shell_data->token_count && shell_data->token_array
//[*token_index].type != T_PIPE)
// 	{
//         process_token(command_index, token_index, shell_data, &current_input,
//&current_output, &current_arg);
//     }
// }
// void	parse_and_fill_command(int command_index, int *token_index,
//t_args *shell_data)
// {
// 	int current_input;
// 	int	current_arg;
// 	int	current_output;
// 	current_input = -1;
// 	current_arg = -1;
// 	current_output = -1;
// 	while (*token_index < shell_data->tokarr_l && shell_data->tokarr
//[*token_index].type != T_PIPE)
// 	{
// 		if (shell_data->tokarr[*token_index].type == T_RED_FROM
// 			&& check_special_symbol(shell_data->tokarr
//[*token_index].word) == 2)
// 			handle_double_redirection(&shell_data->cmdarr
//[command_index].inp[++current_input], shell_data->tokarr,
// 				token_index);
// 		if (shell_data->tokarr[*token_index].type == T_RED_FROM
// 			|| shell_data->tokarr[*token_index].type == T_DLESS)
// 			set_redirection_type(&shell_data->cmdarr[command_index]
//.inp[++current_input], shell_data->tokarr, token_index);
// 		else if (shell_data->tokarr[*token_index].type == T_RED_TO
// 			|| shell_data->tokarr[*token_index].type == T_DGREAT)
// 			set_redirection_type(&shell_data->cmdarr[command_index]
//.out[++current_output], shell_data->tokarr, token_index);
// 		else
// 			shell_data->cmdarr[command_index].args[++current_arg]
//= shell_data->tokarr[*token_index].word;
// 		(*token_index)++;
// 	}
// }
// void	fill_redir_type(t_token *redir, t_token *tokarr, int *t)
// {
// 	redir->type = tokarr[*t].type;
// 	(*t)++;
// 	if (!tokarr[*t].word)
// 		alloc_err();
// 	redir->word = ft_strdup(tokarr[*t].word);
// }
// void	double_redir_case(t_token *redir, t_token *tokarr, int *t)
// {
// 	fill_redir_type(redir, tokarr, t);
// 	tokarr[--(*t)].type = T_RED_TO;
// }
// #include "../../incl/minishell.h"
// void	fill_redir_type(t_token *redir, t_token *tokarr, int *t)
// {
// 	redir->type = tokarr[*t].type;
// 	(*t)++;
// 	if (!tokarr[*t].word)
// 		alloc_err();
// 	redir->word = ft_strdup(tokarr[*t].word);
// }
// void	double_redir_case(t_token *redir, t_token *tokarr, int *t)
// {
// 	fill_redir_type(redir, tokarr, t);
// 	tokarr[--(*t)].type = T_RED_TO;
// }
// // takes curr cmd, and token start i for this cmd
// // returns token end i (where encounted pipe or end of arr)
// //NOWA NAZWA!!!!!!!!!!!!!!!!!!!!!!!!!!!
// // void	process_command_tokens(int cmd, int *tok, t_args *shell_data)
// void	parse_and_fill_command(int cmd, int *tok, t_args *shell_data)
// {
// 	int	a;
// 	int	i;
// 	int	o;
// 	a = -1;
// 	i = -1;
// 	o = -1;
// 	while (*tok < shell_data->tokarr_l && shell_data->tokarr[*tok].type
//!= T_PIPE)
// 	{
// 		if (shell_data->tokarr[*tok].type == T_RED_FROM
// 			&& check_special_symbol(shell_data->tokarr[*tok].word) == 2)
// 			handle_double_redirection(&shell_data->cmdarr[cmd].inp[++i], 
//shell_data->tokarr,
// 				tok);
// 		if (shell_data->tokarr[*tok].type == T_RED_FROM
// 			|| shell_data->tokarr[*tok].type == T_DLESS)
// 			fill_redir_type(&shell_data->cmdarr[cmd].inp[++i],
//shell_data->tokarr, tok);
// 		else if (shell_data->tokarr[*tok].type == T_RED_TO
// 			|| shell_data->tokarr[*tok].type == T_DGREAT)
// 			fill_redir_type(&shell_data->cmdarr[cmd].out[++o], 
//shell_data->tokarr, tok);
// 		else
// 			shell_data->cmdarr[cmd].args[++a] = 
//shell_data->tokarr[*tok].word;
// 		(*tok)++;
// 	}
// }