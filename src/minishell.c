
#include "../incl/minishell.h"
//ZMIENIONE !!!!!!!!!!!!!!!!!!!!!
void initialize_shell(t_args *shell_state, char **environment)
{
	shell_state->env = NULL;
	shell_state->export = NULL;
	shell_state->builtin = NULL;
	shell_state->tokarr = NULL;
	shell_state->cmdarr = NULL;
	// Inicjalizuj zmienne liczbowe na wartości początkowe
	shell_state->exit_status = 0;
	shell_state->tokarr_l = 0;
	shell_state->cmdarr_l = 0;
	shell_state->cmd_num = 0;
	// Inicjalizacja środowiska i wbudowanych poleceń
	initialize_environment(shell_state, environment);
	initialize_builtins(shell_state);
	// 	init_env(shell_data, env);
// 	init_builtin_arr(shell_data);
}

//ZMIENIONE !!!!!!!!!!!!!!!!!!!!!
int validate_input(char *user_input)
{
	if (user_input == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	if (user_input[0] == '\0')
	{
		free(user_input);
		return 1;
	}
	return 0;
}
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

//ZMIENIONE !!!!!!!!!!!!!!!!!!!!!
static void	display_prompt(t_args *shell_data)
{
	char	*user_input;
	char	*current_directory;
	
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
		clean_command_data(shell_data);
		ft_free(user_input);
	}
	ft_free(current_directory);
}

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

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	t_args	shell_data;

	load_history();
	ft_alloc_init();
	setup_signal_handlers();
	if (argc == 1)
	{
		initialize_shell(&shell_data, get_envp(envp));
		display_prompt(&shell_data);
	}
	else
		exit(write(1, RED "No arguments accepted!\n" RE, 32));
	ft_destructor();
	save_history();
	return (0);
}

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