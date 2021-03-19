/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokez.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:30:48 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/12 14:02:40 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void		new_token(char *data)
{
	t_tok	*new;
	int		type;

	type = read_lexem(data);
	if (!(new = token_init(data, type)))
		err_msg("error");
	token_listadd_back(&(g_my.curtok), new);
}

void		p_new_token(char *str, int *i, int *tab)
{
	char	c;
	char	*new;

	c = str[*i];
	str[*i] = 0;
	if (tab[0] > 1)
	{
		if (!(new = ft_strjoin(" ", str)))
			p_error(errno);
		new_token(new);
		free(new);
	}
	else
		new_token(str);
	str[*i] = c;
	tab[2] = 1;
}

static void	p_quotes(char *str, int *tab, int *i)
{
	char	sep;

	sep = str[*i];
	(*i)++;
	tab[1]++;
	while (str[*i] && str[*i] != sep)
	{
		if (str[*i] == '\\')
			(*i)++;
		if (str[*i])
			(*i)++;
		tab[1]++;
	}
}

static void	process_tok(char *str, int *tab, int *i)
{
	if (!(*i))
		*i = -1;
	else
		(*i)--;
	while ((*i != -1 && str[*i] && str[++(*i)]) || (*i == -1 && str[++(*i)]))
	{
		if (str[*i] == '\\')
			(*i)++;
		else if (str[*i] == ' ' || str[*i] == '\t')
		{
			fct_space(str, tab, i);
			tab[1]++;
			break ;
		}
		else if (is_spec(str[*i]))
		{
			fct_sep(str, tab, i);
			tab[1]++;
			break ;
		}
		else if (str[*i] == '\'' || str[*i] == '\"')
			p_quotes(str, tab, i);
		tab[2] = 0;
		tab[1]++;
	}
}

/*
** tab[0] = space
** tab[1] = indice dans la string
** tab[2] = si cut ou pas
*/

void		tokez(char *str)
{
	int		i;
	int		tab[3];
	char	*new;

	i = 0;
	new = 0;
	memset(tab, 0, sizeof(int) * 3);
	tab[2] = 1;
	while (*(str + i))
	{
		if (new)
			free(new);
		if (!(new = ft_strdup(str)))
			p_error(errno);
		process_tok(new, tab, &i);
		if (*(str + i))
		{
			str += i;
			i = 0;
		}
	}
	if (!tab[2])
		fct_space(str, tab, &i);
	free(new);
}
