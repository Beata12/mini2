
#include "../../incl/minishell.h"


char	*find_path(char *cmd, char *path)
{
	char	*c;
	char	*tmp;
	char	**paths;
	int		i;
	int		fd;

	i = 0;
	paths = ft_split(path, ':');
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		c = ft_strjoin(tmp, cmd);
		ft_free(tmp);
		fd = open(c, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			free_string_array(paths);
			return (c);
		}
		free(c);
		i++;
	}
	free_string_array(paths);
	return (NULL);
}

char	**get_envp(char **envp)
{
	char	**basic_env;

	if (envp && *envp)
		return (envp);
	else
	{
		basic_env = ft_malloc(sizeof(char *) * 9);
		basic_env[0] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin");
		basic_env[1] = ft_strdup("PWD=/");
		basic_env[2] = ft_strdup("SHLVL=1");
		basic_env[3] = ft_strdup("HOME=/");
		basic_env[4] = ft_strdup("LOGNAME=user");
		basic_env[5] = ft_strdup("USER=user");
		basic_env[6] = ft_strdup("LANG=C");
		basic_env[7] = ft_strdup("TERM=xterm-256color");
		basic_env[8] = NULL;
		return (basic_env);
	}
}

// char	*get_brackets(char *str, int color)
// {
// 	char	*tmp;

// 	if (color == 1)
// 		tmp = ft_strjoin(BLUE, str);
// 	else
// 		tmp = ft_strjoin(RED, str);
// 	ft_free(str);
// 	str = ft_strjoin(tmp, RE);
// 	ft_free(tmp);
// 	tmp = ft_strjoin("[", str);
// 	ft_free(str);
// 	str = ft_strjoin(tmp, "]" RE);
// 	ft_free(tmp);
// 	return (str);
// }

char	*append_prompt_prefix(char *tmp2)
{
	char	*tmp;
	char	*tmp1;
	char	*exit_status;

	exit_status = NULL;
	// if (shell_data->exit_status == 0)
	// 	exit_status = get_brackets(ft_itoa(shell_data->exit_status), 1);
	// else
	// 	exit_status = get_brackets(ft_itoa(shell_data->exit_status), 0);
	tmp1 = ft_strjoin(exit_status, YELLOW "Minishell:" RE);
	tmp = ft_strjoin(tmp1, tmp2);
	ft_free(tmp1);
	ft_free(exit_status);
	return (tmp);
}

char *get_prompt_path(t_args *shell_data)
{
	t_env_lst	*home_env;
	char		*home_directory;
	char		*working_directory;
	char		*intermediate_path;
	static char	*cached_prompt_path;

	home_env = find_env_node("HOME", shell_data->env);
	working_directory = getcwd(NULL, 0);
	if (!working_directory)
	{
		printf("\nyou can use only 'cd ..' or 'exit'\n\n");
		return (cached_prompt_path);
	}
	if (home_env == NULL)
		home_directory = "/";
	else
		home_directory = home_env->val;
	intermediate_path = ft_strjoin(ft_remove_substr(working_directory, home_directory), "$ ");
	ft_free(working_directory);
	cached_prompt_path = append_prompt_prefix(intermediate_path);
	ft_free(intermediate_path);
	return (cached_prompt_path);
}
// char	*get_currect_path(t_args *shell_data)
// {
// 	static char	*path;
// 	char		*tmp2;
// 	char		*tmp3;
// 	t_env_lst	*user;
// 	char		*home;

// 	user = find_env_node("HOME", shell_data->env);
// 	tmp3 = getcwd(NULL, 0);
// 	if (!tmp3)
// 	{
// 		printf("\nyou can use only 'cd ..' or 'exit'\n\n");
// 		return (path);
// 	}
// 	if (user == NULL)
// 		home = "/";
// 	else
// 		home = user->val;
// 	tmp2 = ft_strjoin(ft_remove_substr(tmp3, home), "$ ");
// 	ft_free(tmp3);
// 	path = exit_status_smile(tmp2, shell_data);
// 	ft_free(tmp2);
// 	return (path);
// }













// char	*find_path(char *cmd, char *path)
// {
// 	char	*c;
// 	char	*tmp;
// 	char	**paths;
// 	int		i;
// 	int		fd;

// 	i = 0;
// 	paths = ft_split(path, ':');
// 	while (paths[i] != NULL)
// 	{
// 		tmp = ft_strjoin(paths[i], "/");
// 		c = ft_strjoin(tmp, cmd);
// 		ft_free(tmp);
// 		fd = open(c, O_RDONLY);
// 		if (fd != -1)
// 		{
// 			close(fd);
// 			free_string_array(paths);
// 			return (c);
// 		}
// 		free(c);
// 		i++;
// 	}
// 	free_string_array(paths);
// 	return (NULL);
// }

// char	**get_envp(char **envp)
// {
// 	char	**basic_env;

// 	if (envp && *envp)
// 		return (envp);
// 	else
// 	{
// 		basic_env = ft_malloc(sizeof(char *) * 9);
// 		basic_env[0] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin");
// 		basic_env[1] = ft_strdup("PWD=/");
// 		basic_env[2] = ft_strdup("SHLVL=1");
// 		basic_env[3] = ft_strdup("HOME=/");
// 		basic_env[4] = ft_strdup("LOGNAME=user");
// 		basic_env[5] = ft_strdup("USER=user");
// 		basic_env[6] = ft_strdup("LANG=C");
// 		basic_env[7] = ft_strdup("TERM=xterm-256color");
// 		basic_env[8] = NULL;
// 		return (basic_env);
// 	}
// }

// char	*get_brackets(char *str, int color)
// {
// 	char	*tmp;

// 	if (color == 1)
// 		tmp = ft_strjoin(BLUE, str);
// 	else
// 		tmp = ft_strjoin(RED, str);
// 	ft_free(str);
// 	str = ft_strjoin(tmp, RE);
// 	ft_free(tmp);
// 	tmp = ft_strjoin("[", str);
// 	ft_free(str);
// 	str = ft_strjoin(tmp, "]" RE);
// 	ft_free(tmp);
// 	return (str);
// }

// char	*exit_status_smile(char *tmp2, t_args *shell_data)
// {
// 	char	*tmp;
// 	char	*exit_status;
// 	char	*tmp1;

// 	exit_status = NULL;
// 	if (shell_data->exit_status == 0)
// 		exit_status = get_brackets(ft_itoa(shell_data->exit_status), 1);
// 	else
// 		exit_status = get_brackets(ft_itoa(shell_data->exit_status), 0);
// 	tmp1 = ft_strjoin(exit_status, YELLOW "Minishell:" RE);
// 	tmp = ft_strjoin(tmp1, tmp2);
// 	ft_free(tmp1);
// 	ft_free(exit_status);
// 	return (tmp);
// }

// char	*get_currect_path(t_args *shell_data)
// {
// 	static char	*path;
// 	char		*tmp2;
// 	char		*tmp3;
// 	t_env_lst	*user;
// 	char		*home;

// 	user = find_env_node("HOME", shell_data->env);
// 	tmp3 = getcwd(NULL, 0);
// 	if (!tmp3)
// 	{
// 		printf("\nyou can use only 'cd ..' or 'exit'\n\n");
// 		return (path);
// 	}
// 	if (user == NULL)
// 		home = "/";
// 	else
// 		home = user->val;
// 	tmp2 = ft_strjoin(ft_remove_substr(tmp3, home), "$ ");
// 	ft_free(tmp3);
// 	path = exit_status_smile(tmp2, shell_data);
// 	ft_free(tmp2);
// 	return (path);
// }
