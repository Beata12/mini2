/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:14:12 by aneekhra          #+#    #+#             */
/*   Updated: 2024/06/14 12:12:11 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int		g_exit_status = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	// g_exit_status = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

	// Do nothing on Ctrl-
void	handle_sigquit(int sig)
{
	(void)sig;
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
