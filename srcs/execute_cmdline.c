/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmdline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafidi <ehafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 16:37:56 by ehafidi           #+#    #+#             */
/*   Updated: 2020/11/30 18:52:58 by ehafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	exec_builtin(char *str, char **arr)
{
	if (!(ft_strncmp("exit", str, ft_strlen(str))) && ft_strlen(str) == 4)
		exit_b(arr);
	else if (!(ft_strncmp("export", str, ft_strlen(str)))
		&& ft_strlen(str) == 6)
		export_b(arr);
	else if (!(ft_strncmp("pwd", str, ft_strlen(str))) && ft_strlen(str) == 3)
		pwd(arr);
	else if (!(ft_strncmp("cd", str, ft_strlen(str))) && ft_strlen(str) == 2)
		cd(arr);
	else if (!(ft_strncmp("unset", str, ft_strlen(str))) &&
		ft_strlen(str) == 5)
		unset(arr);
	else if (!(ft_strncmp("echo", str, ft_strlen(str))) && ft_strlen(str) == 4)
		echo(arr);
	else if (!(ft_strncmp("env", str, ft_strlen(str))) && ft_strlen(str) == 3)
		env(arr);
}

int		compare_builtin(char *str)
{
	char	*tab[8];
	int		i;

	i = -1;
	tab[0] = "cd";
	tab[1] = "echo";
	tab[2] = "pwd";
	tab[3] = "env";
	tab[4] = "export";
	tab[5] = "unset";
	tab[6] = "exit";
	tab[7] = NULL;
	while (tab[++i])
	{
		if (str && ft_strlen(str) &&
		(!(ft_strncmp(tab[i], str, ft_strlen(str)))) &&
		!(tab[i][ft_strlen(str)]))
			return (1);
	}
	return (0);
}

void	execute_cmdline(t_ast *cmdline)
{
	t_exec exec;
	t_list *argv;

	if (!(exec.paths_arr = get_path_table_y(get_env(g_my.env_list, "PATH"))))
		err_msg("error");
	exec.count = 0;
	exec.builtin = 0;
	argv = 0;
	exec.stdin_c = dup(0);
	if (exec.stdin_c == -1)
		err_msg("error");
	exec.stdout_c = dup(1);
	if (exec.stdout_c == -1)
		err_msg("error");
	if (cmdline && cmdline->type != NODE_CMDPATH)
		g_my.export = 1;
	else
		g_my.export = 0;
	execute_job(cmdline, &exec, &argv);
	affiche_msg_error();
	free_arr(exec.paths_arr);
	ft_lstclear(&argv, free);
}
