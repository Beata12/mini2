/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 07:15:00 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/14 17:26:51 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	initialize_shell(t_args *shell_state, char **environment)
{
	shell_state->env = NULL;
	shell_state->exported_vars = NULL;
	shell_state->builtin_cmds = NULL;
	shell_state->token_array = NULL;
	shell_state->command_array = NULL;
	shell_state->exec_result = 0;
	shell_state->token_count = 0;
	shell_state->command_count = 0;
	shell_state->command_index = 0;
	initialize_environment(shell_state, environment);
	initialize_builtins(shell_state);
}

int	validate_input(char *user_input)
{
	if (user_input == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	if (user_input[0] == '\0')
	{
		free(user_input);
		return (1);
	}
	return (0);
}

static void	display_prompt(t_args *shell_data)
{
	char	*user_input;
	char	*current_directory;

	load_history();
	setup_signal_handlers();
	while (1)
	{
		current_directory = get_prompt_path(shell_data);
		user_input = readline(current_directory);
		if (validate_input(user_input))
			continue ;
		add_history(user_input);
		if (parse_input(user_input, shell_data))
		{
			if (shell_exit(shell_data, user_input))
				continue ;
			execute(shell_data);
		}
		free_command_resources(shell_data);
		ft_free(current_directory);
		free(user_input);
	}
	free(user_input);
	ft_free(current_directory);
	save_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_args	shell_data;

	(void)argv;
	setup_signal_handlers();
	ft_alloc_init();
	if (argc == 1)
	{
		initialize_shell(&shell_data, initialize_envp(envp));
		display_prompt(&shell_data);
	}
	else
		exit(write(1, RED "No arguments accepted!\n" RE, 32));
	ft_destructor();
	return (0);
}

// //ZMIENIONE !!!!!!!!!!!!!!!!!!!!!
// void initialize_shell(t_args *shell_state, char **environment)
// {
// 	shell_state->env = NULL;
// 	shell_state->exported_vars = NULL;
// 	shell_state->builtin_cmds = NULL;
// 	shell_state->token_array = NULL;
// 	shell_state->command_array = NULL;
// 	// Inicjalizuj zmienne liczbowe na wartości początkowe
// 	shell_state->exec_result = 0;
// 	shell_state->token_count = 0;
// 	shell_state->command_count = 0;
// 	shell_state->command_index = 0;
// 	// Inicjalizacja środowiska i wbudowanych poleceń
// 	initialize_environment(shell_state, environment);
// 	initialize_builtins(shell_state);
// 	// 	init_env(shell_data, env);
// // 	init_builtin_arr(shell_data);
// }
// int	main(int ac, char **av, char **envp)
// {
// 	t_args	shell_data;
// 	ft_alloc_init();
// 	ignore_signals();
// 	(void)av;
// 	(void)ac;
// 	if (ac != 1)
// 		exit(write(1, RED "No arguments accepted!\n" RE, 32));
// 	else
// 	{
// 		init_mshell(&shell_data, get_envp(envp));
// 		minishell_loop(&shell_data);
// 	}
// 	ft_destructor();
// 	return (0);
// }
// static void	display_prompt(t_args *shell_data)
// {
// 	char	*input;
// 	char	*path;
// 	// load_history();
// 	while (1)
// 	{
// 		// g_signal = 0;
// 		path = get_prompt_path(shell_data);
// 		input = readline(path);
// 		if (check_input(input))
// 			continue ;
// 		add_history(input);
// 		if (parse_input(input, shell_data))
// 		{
// 			if (ft_exit(shell_data, input))
// 				continue ;
// 			execute(shell_data);
// 		}
// 		clean_command_data(shell_data);
// 		ft_free(input);
// 	}
// 	ft_free(path);
// 	// save_history();
// }
// int	check_input(char *input)
// {
// 	if (!input)
// 	{
// 		ft_free(input);
// 		printf("exit\n");
// 		exit(0);
// 	}
// 	else if (!*input)
// 	{
// 		ft_free(input);
// 		return (1);
// 	}
// 	return (0);
// }