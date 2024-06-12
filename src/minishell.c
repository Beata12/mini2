
#include "../incl/minishell.h"

void	init_mshell(t_args *shell_data, char **env)
{
	shell_data->env = NULL;
	shell_data->export = NULL;
	shell_data->exit_status = 0;
	shell_data->builtin = NULL;
	shell_data->tokarr = NULL;
	shell_data->cmdarr = NULL;
	shell_data->tokarr_l = 0;
	shell_data->cmdarr_l = 0;
	shell_data->cmd_num = 0;
	init_env(shell_data, env);
	init_builtin_arr(shell_data);
}

int	check_input(char *input)
{
	if (!input)
	{
		ft_free(input);
		printf("exit\n");
		exit(0);
	}
	else if (!*input)
	{
		ft_free(input);
		return (1);
	}
	return (0);
}

static void	minishell_loop(t_args *shell_data)
{
	char	*input;
	char	*path;
	
	// load_history();
	while (1)
	{
		// g_signal = 0;
		path = get_currect_path(shell_data);
		input = readline(path);
		if (check_input(input))
			continue ;
		add_history(input);
		if (parse_input(input, shell_data))
		{
			if (ft_exit(shell_data, input))
				continue ;
			execute(shell_data);
		}
		clean_command_data(shell_data);
		ft_free(input);
	}
	ft_free(path);
	// save_history();
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	t_args	shell_data;

	load_history();
	ft_alloc_init();
	setup_signal_handlers();
	if (argc == 1)
	{
		init_mshell(&shell_data, get_envp(envp));
		minishell_loop(&shell_data);
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
