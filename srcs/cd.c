/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:31:41 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/30 17:31:43 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char		*spec_free(char **p)
{
	if (!(*p = (char*)malloc(sizeof(char) * 1000))
	|| !(*p = getcwd(*p, 1000)))
	{
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		return (0);
	}
	return (*p);
}

int			cd(char **argv)
{
	int		argc;
	char	*old;

	argc = get_argc(argv);
	if (!(old = ft_strdup(get_env(g_my.env_list, "PWD"))))
	{
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		return (ERROR);
	}
	if ((chdir(argv[1]) == -1))
	{
		free(old);
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		return (ERROR);
	}
	if (!(change_pwd(argv, "old", old)))
		return (ERROR);
	free(old);
	if (!spec_free(&old))
		return (ERROR);
	if (!(change_pwd(argv, "new", old)))
		return (ERROR);
	free(old);
	return (BON);
}
