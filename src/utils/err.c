
#include "../../incl/minishell.h"

void	alloc_err(void)
{
	exit(printf(RED "Allocation failed\n" RE));
}

void	ft_error_exit(char *str, char *str2, int status)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, str2, ft_strlen(str2));
	write(2, "\n", 1);
	exit(status);
}

static void	ft_print_err(char *cmd, char *arg, char *content)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write (2, ":", 2);
	if (*arg)
	{
		write(2, "`", 1);
		write(2, arg, ft_strlen(arg));
		write(2, "': ", 2);
	}
	write(2, content, ft_strlen(content));
	write(2, "\n", 1);
}

void	ft_error_return(char *str, t_args *shell_data, int status, int modif)
{
	char	*name;
	char	*content;

	content = NULL;
	name = shell_data->cmdarr[shell_data->cmd_num].args[0];
	if (!ft_strcmp(name, "cd") && modif)
		content = "HOME not set";
	else if (!ft_strcmp(name, "cd") && !modif)
		content = "No such file or directory";
	else if (!ft_strcmp(name, "pwd"))
		content = "error retrieving current directory";
	else if (!ft_strcmp(name, "exit") && !modif)
		content = "too many arguments";
	else if (!ft_strcmp(name, "export"))
		content = "not a valid identifier";
	else if (!ft_strcmp(name, "unset"))
		content = "not enough arguments";
	ft_print_err(name, str, content);
	shell_data->exit_status = status;
}
