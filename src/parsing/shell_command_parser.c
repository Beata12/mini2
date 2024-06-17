/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_command_parser.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 07:58:10 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/17 07:48:35 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	reset_count(t_data_counter *token_counter)
{
	token_counter->arg_count = 0;
	token_counter->input_count = 0;
	token_counter->output_count = 0;
}

void	allocate_command_memory(t_data_counter cmd_sizes,
	t_cmd_arr_str *command)
{
	command->args = ft_malloc(sizeof(char *) * (cmd_sizes.arg_count + 1));
	if (!command->args)
	{
		perror("Failed to allocate memory for command arguments");
		exit(EXIT_FAILURE);
	}
	command->input_tokens = ft_malloc(sizeof(t_token) * cmd_sizes.input_count);
	if (!command->input_tokens)
	{
		perror("Failed to allocate memory for input redirections");
		exit(EXIT_FAILURE);
	}
	command->output_tokens = ft_malloc(sizeof(t_token)
			* cmd_sizes.output_count);
	if (!command->output_tokens)
	{
		perror("Failed to allocate memory for output redirections");
		exit(EXIT_FAILURE);
	}
	command->args[cmd_sizes.arg_count] = NULL;
	command->input_length = cmd_sizes.input_count;
	command->output_length = cmd_sizes.output_count;
}

static void	update_count(t_token *token, t_data_counter *count)
{
	if (token->type == T_WORD)
		count->arg_count++;
	else
	{
		if (token->type == T_RED_FROM || token->type == T_DLESS)
			count->input_count++;
		else if (token->type == T_RED_TO || token->type == T_DGREAT)
			count->output_count++;
		if (token->type == T_RED_FROM && check_special_symbol(token->word) == 2)
			count->output_count++;
	}
}

static void	initialize_command(int command_counter, int *token_counter,
	t_args *shell_data)
{
	t_data_counter	count;
	t_token			current_token;

	reset_count(&count);
	while (shell_data->token_array && *token_counter < shell_data->token_count
		&& shell_data->token_array[*token_counter].word
		&& shell_data->token_array[*token_counter].type != T_PIPE)
	{
		current_token = shell_data->token_array[*token_counter];
		update_count(&current_token, &count);
		(*token_counter)++;
		if (current_token.type != T_WORD)
			(*token_counter)++;
	}
	allocate_command_memory(count, &shell_data->command_array[command_counter]);
}

void	initialize_command_array(t_args *shell_data)
{
	int	token_counter;
	int	command_counter;

	token_counter = 0;
	command_counter = 1;
	while (token_counter < shell_data->token_count)
	{
		if (shell_data->token_array[token_counter].type == T_PIPE)
			command_counter++;
		token_counter++;
	}
	shell_data->command_array = ft_malloc(sizeof(t_cmd_arr_str)
			* command_counter);
	shell_data->command_count = command_counter;
	command_counter = 0;
	token_counter = 0;
	while (command_counter < shell_data->command_count
		&& token_counter < shell_data->token_count)
	{
		initialize_command(command_counter, &token_counter, shell_data);
		command_counter++;
		token_counter++;
	}
}
