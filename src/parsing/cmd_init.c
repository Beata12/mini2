
#include "../../incl/minishell.h"

//DZIALA, WSYZTSKO OK
static void	reset_count(t_data_counter *token_counter)
{
	token_counter->arg_count = 0;
	token_counter->input_count = 0;
	token_counter->output_count = 0;
}
// void	alloc_cmd(t_count sizes, t_cmdarr *cmd)
// {
// 	cmd->args = ft_malloc(sizeof(char *) * (sizes.arg + 1));
// 	cmd->inp = ft_malloc(sizeof(t_token) * sizes.in);
// 	cmd->out = ft_malloc(sizeof(t_token) * sizes.out);
// 	cmd->args[sizes.arg] = NULL;
// 	cmd->inp_l = sizes.in;
// 	cmd->out_l = sizes.out;
// }
// void	allocate_command_memory(t_count sizes, t_cmdarr *cmd)
// {
// 	cmd->args = ft_malloc(sizeof(char *) * (sizes.arg + 1));
// 	cmd->inp = ft_malloc(sizeof(t_token) * sizes.in);
// 	cmd->out = ft_malloc(sizeof(t_token) * sizes.out);
// 	cmd->args[sizes.arg] = NULL;
// 	cmd->inp_l = sizes.in;
// 	cmd->out_l = sizes.out;
// }
//to to samo co alloc_cmd, ale musze pozmieniac w innych miejscach jeszcze
void allocate_command_memory(t_data_counter cmd_sizes, t_cmd_arr_str *command)
{
    command->args = ft_malloc(sizeof(char *) * (cmd_sizes.arg_count + 1));
    if (!command->args)
    {
        // Obsługa błędu alokacji pamięci
        perror("Failed to allocate memory for command arguments");
        exit(EXIT_FAILURE);
    }
    command->input_tokens = ft_malloc(sizeof(t_token) * cmd_sizes.input_count);
    if (!command->input_tokens)
    {
        // Obsługa błędu alokacji pamięci
        perror("Failed to allocate memory for input redirections");
        exit(EXIT_FAILURE);
    }
    command->output_tokens = ft_malloc(sizeof(t_token) * cmd_sizes.output_count);
    if (!command->output_tokens)
    {
        // Obsługa błędu alokacji pamięci
        perror("Failed to allocate memory for output redirections");
        exit(EXIT_FAILURE);
    }
    command->args[cmd_sizes.arg_count] = NULL;
    command->input_length = cmd_sizes.input_count;
    command->output_length = cmd_sizes.output_count;
}

//DZIALA I JEST GOTOWA
//100%moja funkcja
static void update_count(t_token *token, t_data_counter *count)
{
    if (token->type == T_WORD)
    {
        count->arg_count++;
    }
    else
    {
        if (token->type == T_RED_FROM || token->type == T_DLESS)
        {
            count->input_count++;
        }
        else if (token->type == T_RED_TO || token->type == T_DGREAT)
        {
            count->output_count++;
        }

        if (token->type == T_RED_FROM && check_special_symbol(token->word) == 2)
        {
            count->output_count++;
        }
    }
}

void	initialize_command(int command_counter, int *token_counter, t_args *shell_data)
{
	t_data_counter	count;

	reset_count(&count);
	while (shell_data->token_array && *token_counter < shell_data->token_count && shell_data->token_array[*token_counter].word
    && shell_data->token_array[*token_counter].type != T_PIPE)
	{
	    t_token current_token = shell_data->token_array[*token_counter];
	    update_count(&current_token, &count);
	    // Przejście do następnego tokena
	    (*token_counter)++;
	    // Dodatkowy warunek przejścia do następnego tokena dla nie-słów
	    if (current_token.type != T_WORD)
	        (*token_counter)++;
	}
	// while (shell_data->tokarr && *token_counter < shell_data->tokarr_l && shell_data->tokarr[*token_counter].word
	// 	&& shell_data->tokarr[*token_counter].type != T_PIPE)
	// {
	// 	if (shell_data->tokarr[*token_counter].type == T_WORD)
	// 		count.arg++;
	// 	else
	// 	{
	// 		if (shell_data->tokarr[*token_counter].type == T_RED_FROM
	// 			|| shell_data->tokarr[*token_counter].type == T_DLESS)
	// 			count.in++;
	// 		else if (shell_data->tokarr[*token_counter].type == T_RED_TO
	// 			|| shell_data->tokarr[*token_counter].type == T_DGREAT)
	// 			count.out++;
	// 		if (shell_data->tokarr[*token_counter].type == T_RED_FROM
	// 			&& spec_symb(shell_data->tokarr[*token_counter].word) == 2)
	// 			count.out++;
	// 		(*token_counter)++;
	// 	}
	// 	(*token_counter)++;
	// }
	//tutaj była alloc_cmd
	allocate_command_memory(count, &shell_data->command_array[command_counter]);
}

//nowa nAzWa
// void	initialize_command_array(t_args *shell_data)
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
	shell_data->command_array = ft_malloc(sizeof(t_cmd_arr_str) * command_counter);
	shell_data->command_count = command_counter;
	command_counter = 0;
	token_counter = 0;
	while (command_counter < shell_data->command_count && token_counter < shell_data->token_count)
	{
		initialize_command(command_counter, &token_counter, shell_data);
		command_counter++;
		token_counter++;
	}
}
