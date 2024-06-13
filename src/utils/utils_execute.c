
#include "../../incl/minishell.h"

void	wait_in_parent(t_args *shell_data)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (i < shell_data->cmdarr_l)
	{
		wait(&status);
		if (WIFEXITED(status))
			shell_data->exit_status = WEXITSTATUS(status);
		i++;
	}
}
//zrobione
void	initialize_pipes(t_args *shell_data, int **pipe_array)
{
	int	i;

	i = 0;
	while (i < shell_data->cmdarr_l - 1)
	{
		pipe_array[i] = ft_malloc(sizeof(int) * 2);
		pipe(pipe_array[i]);
		i++;
	}
}

void	close_pipe_descriptors(t_args *shell_data, int **pipe_array)
{
	int	i;

	i = 0;
	while (i < shell_data->cmdarr_l - 1)
	{
		close(pipe_array[i][0]);
		close(pipe_array[i][1]);
		ft_free(pipe_array[i]);
		i++;
	}
}


void	ft_execve(t_args *shell_data)
{
	char *executable_path;
    char **command_args;
    char **envp_array;
    t_env_lst *env_node;

    executable_path = NULL;
    envp_array = generate_envp_array(shell_data->env);
    command_args = shell_data->cmdarr[shell_data->cmd_num].args;
    env_node = find_env_var("PATH", shell_data->env);

    if (ft_strchr(command_args[0], '/') == NULL)
    {
        if (!env_node)
            exit_with_error(command_args[0], ": command not found", 127);
        executable_path = find_path(command_args[0], env_node->val);
    }
    else
        executable_path = ft_strdup(command_args[0]);
    if (executable_path == NULL)
        exit_with_error(command_args[0], ": command not found", 127);
    execve(executable_path, command_args, envp_array);
    exit_with_error(command_args[0], ": command not found", 127);
    if (command_args[0] != NULL)
        exit_with_error(command_args[0], ": command not found", 127);
    exit(0);
}


