/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafidi <ehafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 15:24:25 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/22 19:06:28 by ehafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** ind = 0 => check si c'est un dossier
** ind = 1 => check si c'est un fichier et qu'on a access
*/

static void	file_error_c(char *file, int ind)
{
	char	*str;

	str = "minishell: ";
	write(1, str, ft_strlen(str));
	write(1, file, ft_strlen(file));
	if (ind)
		str = ": is a directory\n";
	else
		str = ": command not found\n";
	write(1, str, ft_strlen(str));
	if (ind)
		g_my.ret = 126;
	else
		g_my.ret = 127;
}

char		*get_abs_path_y(char **tab, char *func)
{
	int		i;
	int		ret;
	char	*abs_path;

	i = -1;
	while (tab[++i])
	{
		if (!(abs_path = ft_strjoin(tab[i], func)))
			p_error(errno);
		if (!file_exists(abs_path))
		{
			free_double_tab(tab);
			return (abs_path);
		}
		else
			free(abs_path);
	}
	free_double_tab(tab);
	if ((ret = a_to_fd(func, 1) == 1) && func[ft_strlen(func) - 1] == '/')
		file_error_c(func, 1);
	else
		file_error_c(func, 0);
	return (0);
}

char		**get_path_table_y(char *str)
{
	char	**tab;
	int		i;

	if (!(tab = ft_split(str, ':')))
		p_error(errno);
	i = -1;
	while (tab[++i])
		if (!(tab[i] = ft_join_custom2(tab[i], "/")))
			p_error(errno);
	return (tab);
}
