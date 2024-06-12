/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:12:09 by aneekhra          #+#    #+#             */
/*   Updated: 2024/06/12 21:12:14 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execute.h"

void	init_builtin_arr(t_args *shell_data)
{
	int	n_cmds;

	n_cmds = 6;
	shell_data->builtin = ft_malloc(sizeof(t_builtin) * (n_cmds + 1));
	shell_data->builtin[0].name = "pwd";
	shell_data->builtin[0].fn_ptr = ft_pwd;
	shell_data->builtin[1].name = "cd";
	shell_data->builtin[1].fn_ptr = ft_cd;
	shell_data->builtin[2].name = "echo";
	shell_data->builtin[2].fn_ptr = ft_echo;
	shell_data->builtin[3].name = "unset";
	shell_data->builtin[3].fn_ptr = ft_unset;
	shell_data->builtin[4].name = "export";
	shell_data->builtin[4].fn_ptr = ft_export;
	shell_data->builtin[5].name = "env";
	shell_data->builtin[5].fn_ptr = ft_env;
	shell_data->builtin[6].name = NULL;
	shell_data->builtin[6].fn_ptr = NULL;
}

void	ft_cd(t_args *shell_data)
{
	char		**tmp;
	char		*path;
	t_env_lst	*node;
	// int			i;

	// i = 0;
	node = NULL;
	path = NULL;
	tmp = shell_data->cmdarr[shell_data->cmd_num].args;
	if (!tmp[1])
	{
		node = find_env_node("HOME", shell_data->env);
		if (node)
			path = ft_strdup(node->val);
		if (!path || chdir(path) == -1)
			return (ft_error_return("", shell_data, 1, 1));
		ft_free(path);
	}
	else
	{
		if (chdir(tmp[1]) == -1)
			return (ft_error_return(tmp[1], shell_data, 1, 0));
	}
	shell_data->exit_status = 0;
}

void	ft_pwd(t_args *shell_data)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (ft_error_return(path, shell_data, 1, 0));
	printf("%s\n", path);
	ft_free(path);
	shell_data->exit_status = 0;
}

int	ft_exit(t_args *shell_data, char *input)
{
	if (ft_strcmp("exit", shell_data->cmdarr[0].args[0]) == 0)
	{
		ft_free(input);
		printf("exit\n");
		if (!shell_data->cmdarr[0].args[1])
			exit(shell_data->exit_status);
		else if (shell_data->cmdarr[0].args[1]
			&& !ft_isdigit_loop(shell_data->cmdarr[0].args[1]))
			ft_error_exit("exit: ", "numeric argument required", 2);
		else if (ft_isdigit_loop(shell_data->cmdarr[0].args[1])
			&& shell_data->cmdarr[0].args[2])
			return (ft_error_return("", shell_data, 1, 0), 1);
		else if (shell_data->cmdarr[0].args[1])
			exit(ft_atoi(shell_data->cmdarr[0].args[1]));
	}
	return (0);
}
