/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_command_processor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 07:15:52 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/17 07:48:48 by bmarek           ###   ########.fr       */
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
