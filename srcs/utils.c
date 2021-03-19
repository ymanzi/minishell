/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 21:00:19 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/02 19:46:38 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*ft_join(char *s1, char const *s2)
{
	int		size_s1;
	int		size_s2;
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	if (!(ptr = (char*)malloc(sizeof(*ptr) * (size_s1 + size_s2 + 1))))
		return (0);
	while (*(s1 + i))
		ptr[j++] = *(s1 + i++);
	i = 0;
	while (*(s2 + i))
		ptr[j++] = *(s2 + i++);
	ptr[j] = '\0';
	return (ptr);
}

int		free_double_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (0);
}

void	free_token(t_tok **token)
{
	t_tok	*tok;
	t_tok	*tmp;

	tok = *token;
	while (tok)
	{
		tmp = tok->next;
		free(tok->data);
		free(tok);
		tok = tmp;
	}
	*token = 0;
}

void	free_tab_token(char **tab, t_tok *llist)
{
	free_double_tab(tab);
	free_token(&llist);
}
