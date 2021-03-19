/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_open_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 08:44:03 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/11 08:58:54 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	show_msg_q(char c)
{
	char	*msg;

	msg = "minishell: unexpected EOF while looking for matching `";
	write(1, msg, ft_strlen(msg));
	write(1, &c, 1);
	write(1, "'\n", 2);
	g_my.ret = 2;
}

int			check_open_quotes(char *str)
{
	int		quote;
	int		i;
	char	c;

	i = 0;
	quote = 1;
	while (str[i])
	{
		if (str[i] == '\\' && (quote || (!quote && c == '\"')) && str[i + 1])
			i++;
		else if (quote && (str[i] == '\"' || str[i] == '\''))
		{
			quote = 0;
			c = str[i];
		}
		else if (!quote && str[i] == c)
			quote = 1;
		i++;
	}
	if (!quote)
		show_msg_q(c);
	return (quote);
}
