/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_err.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:31:55 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/30 17:31:56 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*cd_get_env(t_list *list, char *elem)
{
	int	i;

	i = -1;
	while (list)
	{
		if (!ft_strncmp((char*)(list->content), elem, ft_strlen(elem))
				&& ((char*)(list->content))[ft_strlen(elem)] == '=')
			return ((char*)(list->content + ft_strlen(elem) + 1));
		list = list->next;
	}
	return (NULL);
}

char	*check_home_cd(void)
{
	char	*str;

	if (!(str = cd_get_env(g_my.env_list, "HOME")))
	{
		str = "minishell: cd: HOME not set\n";
		write(1, str, ft_strlen(str));
		return (NULL);
	}
	return (str);
}

int		left_file_error(int err, char *file)
{
	char	*msg;

	msg = "minishell: ";
	write(1, msg, ft_strlen(msg));
	write(1, file, ft_strlen(file));
	write(1, ": ", 2);
	if (err == 18)
	{
		msg = "is a directory\n";
		write(1, msg, ft_strlen(msg));
	}
	else
	{
		write(1, strerror(err), ft_strlen(strerror(err)));
		write(1, "\n", 1);
	}
	if (err == 2)
		g_my.ret = 1;
	else if (err == 21 || err == EACCES || err == 18)
		g_my.ret = 1;
	return (0);
}

int		cd_file_error(int err, char *file)
{
	char	*msg;

	msg = "minishell: cd: ";
	write(1, msg, ft_strlen(msg));
	write(1, file, ft_strlen(file));
	write(1, ": ", 2);
	if (err == 18)
	{
		msg = "is a directory\n";
		write(1, msg, ft_strlen(msg));
	}
	else
	{
		write(1, strerror(err), ft_strlen(strerror(err)));
		write(1, "\n", 1);
	}
	if (err == 2)
		g_my.ret = 127;
	else if (err == 21 || err == EACCES || err == 18)
		g_my.ret = 126;
	return (0);
}

int		check_executable(char *data)
{
	char	*str;
	char	*path;
	int		ret;

	str = 0;
	path = 0;
	if (!(str = getcwd(str, 0)) ||
			!(path = ft_join_custom2(str, "/"))
			|| !(path = ft_join_custom2(path, data)))
	{
		if (str)
			free(str);
		if (path)
			free(path);
		return (0);
	}
	ret = file_exists(path);
	free(path);
	return (ret);
}
