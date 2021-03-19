/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:35:20 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/30 17:35:23 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			pwd(char **argv)
{
	int		argc;
	char	*str;

	argc = get_argc(argv);
	str = 0;
	if (!(str = getcwd(str, 0)))
	{
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		return (ERROR);
	}
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (BON);
}

int			change_pwd(char **argv, char *status, char *p)
{
	int		argc;
	char	*tab[3];

	argc = get_argc(argv);
	if (!ft_strncmp("old", status, 3))
		tab[1] = ft_strjoin("OLDPWD=", p);
	else
		(tab[1] = ft_strjoin("PWD=", p));
	if (!tab[1])
		err_msg("error");
	tab[0] = "export";
	tab[2] = NULL;
	export_b(tab);
	free(tab[1]);
	return (1);
}

int			init_pwd(void)
{
	char	*old;

	if (!spec_free(&old))
		return (ERROR);
	if (!(change_pwd(0, "new", old)))
		return (ERROR);
	free(old);
	return (BON);
}
