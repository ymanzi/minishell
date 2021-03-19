/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafidi <ehafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 17:04:05 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/23 20:05:47 by ehafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			get_argc(char **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return (0);
	while (tab[++i])
		;
	return (i);
}

static int	echo_cmp(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (0);
	}
	return (1);
}

int			echo(char **argv)
{
	int	i;
	int	argc;
	int	op_nl;

	i = 1;
	op_nl = 1;
	argc = get_argc(argv);
	if (argc > 1)
	{
		while (argv[i] && echo_cmp(argv[i]))
		{
			op_nl = 0;
			i++;
		}
		while (i < argc)
		{
			write(1, argv[i], ft_strlen(argv[i]));
			if (argc > (i + 1))
				write(1, " ", 1);
			i++;
		}
	}
	if (op_nl)
		write(1, "\n", 1);
	return (BON);
}

int			env(char **argv)
{
	int		argc;
	t_list	*list;
	char	*str;

	argc = get_argc(argv);
	list = g_my.env_list;
	while (list)
	{
		str = (char*)(list->content);
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
		list = list->next;
	}
	return (BON);
}
