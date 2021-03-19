/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignore_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafidi <ehafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:10:04 by ymanzi            #+#    #+#             */
/*   Updated: 2020/12/01 12:30:33 by ehafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	handler_int(int num)
{
	num = 0;
	if (num == 0)
	{
		write(1, "\n", 1);
		ft_putstr_fd("MiniShell%>", 1);
	}
}

void		ignore_signal(void)
{
	g_my.sig = 1;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler_int);
}

void		restore_signal(void)
{
	if (g_my.sig)
		signal(SIGINT, SIG_DFL);
}
