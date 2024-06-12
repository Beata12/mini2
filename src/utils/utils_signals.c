//ANJALI changed it
#include "../../incl/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	// g_exit_status = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	// if (sig == SIGQUIT)
	// {
	// 	rl_replace_line("", 0);
	// 	rl_redisplay();
	// }
}

void	handle_sigquit(int sig)
{
	(void)sig;
	// Do nothing on Ctrl-
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGTSTP, &sa, NULL);
}

void	load_history(void)
{
	read_history(HISTORY_FILE);
}

void	save_history(void)
{
	write_history(HISTORY_FILE);
}
// int		g_signal;

// void	child_signal(int signal)
// {
// 	if (signal == SIGINT)
// 		exit(1);
// }

// void	handle_sigint(int signals)
// {
// 	if (signals == SIGCHLD)
// 		g_signal = SIGCHLD;
// 	else if (signals == SIGINT)
// 	{
// 		write(1, "\n", 1);
// 		wait(NULL);
// 		if (g_signal == SIGCHLD)
// 		{
// 			g_signal = 0;
// 			return ;
// 		}
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 		g_signal = 0;
// 	}
// }
	
// void	ignore_signals(void)
// {
// 	struct sigaction	sa;

// 	sa.sa_handler = handle_sigint;
// 	sa.sa_flags = SA_RESTART;
// 	sigemptyset(&sa.sa_mask);
// 	sigaction(SIGINT, &sa, NULL);
// 	sigaction(SIGCHLD, &sa, NULL);
// 	signal(SIGQUIT, SIG_IGN);
// 	sigaction(SIGTSTP, &sa, NULL);
// }
