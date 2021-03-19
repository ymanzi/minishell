/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafidi <ehafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:45:33 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/12 18:18:23 by ehafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int		free_parser(t_ast *tree, t_tok *save, int i)
{
	ast_delete(tree);
	if (!i)
		free_token(&save);
	return (0);
}

int				is_sepa(char *str)
{
	int		i;
	char	*tab[4];

	tab[0] = "<";
	tab[1] = ">";
	tab[2] = ">>";
	tab[3] = NULL;
	i = -1;
	while (tab[++i])
	{
		if (!(ft_strncmp(str, tab[i], ft_strlen(tab[i]))))
			return (1);
	}
	return (0);
}

t_tok			*get_previous_tok(t_tok *start, t_tok *find)
{
	if (start == find)
		return (NULL);
	while (start)
	{
		if (start->next == find)
			return (start);
		start = start->next;
	}
	return (NULL);
}

int				parser(t_ast **tree, int i)
{
	t_tok	*save;

	*tree = 0;
	save = g_my.curtok;
	*tree = cmdline();
	if (!i && g_my.curtok)
	{
		show_msg(save);
		return (free_parser(*tree, save, 0));
	}
	if (!i)
		free_parser(*tree, save, 1);
	return (1);
}
