/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_msg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:35:34 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/30 17:37:22 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	p_show(char *str)
{
	write(1, str, ft_strlen(str));
}

static void	process_show(t_tok *prev)
{
	p_show("minishell: syntax error near unexpected token `");
	if (is_sepa(g_my.curtok->data))
	{
		if (g_my.curtok->next)
			write(1, g_my.curtok->next->data,
					ft_strlen(g_my.curtok->next->data));
		else
			write(1, "newline", ft_strlen("newline"));
	}
	else if (!(ft_strncmp(g_my.curtok->data, "|", 2)) && prev)
		write(1, g_my.curtok->next->data,
				ft_strlen(g_my.curtok->next->data));
	else
		write(1, g_my.curtok->data, ft_strlen(g_my.curtok->data));
}

void		show_msg(t_tok *save)
{
	t_tok	*prev;

	prev = get_previous_tok(save, g_my.curtok);
	if (prev && prev->data[0] == ';')
		prev = NULL;
	if (!(ft_strncmp(g_my.curtok->data, "|", 2)) &&
	!(g_my.curtok->next) && prev && prev->type == STRING)
		p_show("minishell: syntax error: unexpected end of file");
	else
		process_show(prev);
	write(1, "'\n", 2);
	g_my.ret = 2;
}
