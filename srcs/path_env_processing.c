/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_env_processing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafidi <ehafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:27:32 by ehafidi           #+#    #+#             */
/*   Updated: 2020/11/30 16:00:51 by ehafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char **envp)
{
	char	*paths_line;
	int		i;
	int		j;

	j = -1;
	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			break ;
	paths_line = envp[i];
	while (paths_line[++j])
		if (paths_line[j] == '=')
			if (!(paths_line = ft_strdup(&paths_line[++j])))
				err_msg("error");
	return (paths_line);
}

char	**get_path_table(char *paths_line)
{
	char	**paths_arr;
	int		i;

	if (!(paths_arr = ft_split(paths_line, ':')))
		err_msg("error");
	i = -1;
	while (paths_arr[++i])
		if (!(paths_arr[i] = ft_strjoin(paths_arr[i], "/")))
			err_msg("error");
	return (paths_arr);
}

bool	file_exists(char *filename)
{
	struct stat	buffer;

	return (stat(filename, &buffer));
}

char	*get_abs_path(char **paths_arr, char *func)
{
	int		i;
	char	*abs_path;

	i = -1;
	if (func && ft_strlen(func) && (ft_strncmp(func, "./", 2) == 0 ||
	ft_strncmp(func, "../", 3) == 0 || ft_strncmp(func, "/", 1) == 0))
		return (func);
	while (paths_arr[++i])
	{
		if (!(abs_path = ft_strjoin(paths_arr[i], func)))
			err_msg("error");
		if (file_exists(abs_path) == 0)
			return (abs_path);
		else
			free(abs_path);
	}
	return ("ERROR");
}

void	protected_close_2(int fd)
{
	if (close(fd) == -1)
		err_msg("error");
}
