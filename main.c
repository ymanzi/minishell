/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafidi <ehafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 09:16:22 by ymanzi            #+#    #+#             */
/*   Updated: 2020/12/01 14:59:00 by ehafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/lexer.h"

t_gen		g_my;

int	main(int argc, char **argv, char **env)
{
	char	*str;

	if (argc == 3 && !ft_strncmp(argv[1], "-c", 2))
		str = argv[2];
	else
		str = 0;
	gen(env, str);
	if (g_my.ret == 256 || g_my.ret == 42)
		g_my.ret = 1;
	return (g_my.ret);
}
