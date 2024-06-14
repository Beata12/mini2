/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:32:06 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/14 17:32:07 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*locate_file_in_path(char *file_name, char *path_to_search)
{
	int		i;
	int		fd;
	char	*full_path;
	char	*current_path;
	char	**search_paths;

	i = 0;
	search_paths = ft_split(path_to_search, ':');
	while (search_paths[i] != NULL)
	{
		current_path = ft_strjoin(search_paths[i], "/");
		full_path = ft_strjoin(current_path, file_name);
		ft_free(current_path);
		fd = open(full_path, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			free_string_array(search_paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_string_array(search_paths);
	return (NULL);
}

char	**create_default_env(void)
{
	char	**default_env;

	default_env = ft_malloc(sizeof(char *) * 9);
	default_env[0] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin");
	default_env[1] = ft_strdup("PWD=/");
	default_env[2] = ft_strdup("SHLVL=1");
	default_env[3] = ft_strdup("HOME=/");
	default_env[4] = ft_strdup("LOGNAME=user");
	default_env[5] = ft_strdup("USER=user");
	default_env[6] = ft_strdup("LANG=C");
	default_env[7] = ft_strdup("TERM=xterm-256color");
	default_env[8] = NULL;
	return (default_env);
}

char	**initialize_envp(char **environment)
{
	if (environment && *environment)
		return (environment);
	else
		return (create_default_env());
}

static char	*generate_command_prompt(char *exit_code)
{
	char	*prompt;
	char	*prefix_part;
	char	*exit_status;

	exit_status = NULL;
	prefix_part = ft_strjoin(exit_status, GREEN "Minishell:" RE);
	prompt = ft_strjoin(prefix_part, exit_code);
	ft_free(prefix_part);
	ft_free(exit_status);
	return (prompt);
}

char	*get_prompt_path(t_args *shell_data)
{
	t_env_variable	*home_env;
	char			*home_directory;
	char			*working_directory;
	char			*intermediate_path;
	static char		*cached_prompt_path;

	home_env = find_env_var("HOME", shell_data->env);
	working_directory = getcwd(NULL, 0);
	if (!working_directory)
	{
		printf("\nyou can use only 'cd ..' or 'exit'\n\n");
		return (cached_prompt_path);
	}
	if (home_env == NULL)
		home_directory = "/";
	else
		home_directory = home_env->value;
	intermediate_path = ft_strjoin(ft_remove_substr(working_directory,
				home_directory), "$ ");
	free(working_directory);
	cached_prompt_path = generate_command_prompt(intermediate_path);
	ft_free(intermediate_path);
	return (cached_prompt_path);
}

//zrobione
// static char	*generate_command_prompt(char *exit_code)
// {
// 	char	*prompt;
// 	char	*prefix_part;
// 	char	*exit_status;
// 	exit_status = NULL;
// 	// if (shell_data->exit_status == 0)
// 	// 	exit_status = get_brackets(ft_itoa(shell_data->exit_status), 1);
// 	// else
// 	// 	exit_status = get_brackets(ft_itoa(shell_data->exit_status), 0);
// 	prefix_part = ft_strjoin(exit_status, YELLOW "Minishell:" RE);
// 	prompt = ft_strjoin(prefix_part, exit_code);
// 	ft_free(prefix_part);
// 	ft_free(exit_status);
// 	return (prompt);
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