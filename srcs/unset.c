/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:36:54 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/30 17:36:55 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	unset_check(char *str)
{
	int		i;
	char	*msg;

	i = -1;
	while (str[++i])
	{
		if (!i && !ft_isalpha(str[i]))
			break ;
		else if (i && !is_al_num_u(str[i]))
			break ;
	}
	if (!ft_strlen(str) || str[i])
	{
		msg = "minishell: unset: `";
		write(1, msg, ft_strlen(msg));
		write(1, str, ft_strlen(str));
		msg = "': not a valid identifier\n";
		write(1, msg, ft_strlen(msg));
		g_my.ret = 1;
		return (0);
	}
	return (1);
}

int			unset(char **argv)
{
	int		i;
	t_list	*list;
	int		argc;

	i = 0;
	argc = get_argc(argv);
	list = g_my.env_list;
	while (++i < argc)
	{
		if (unset_check(argv[i]))
			ft_lstdel(&list, argv[i]);
	}
	return (BON);
}
