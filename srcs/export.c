/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafidi <ehafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 15:39:11 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/29 13:34:19 by ehafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			ft_strncmp_env(char *s1, char *s2)
{
	int		i;
	int		ret;
	int		len;
	char	*str1;
	char	*str2;

	if (!(str1 = ft_strdup(s1))
	|| !(str2 = ft_strdup(s2)))
		err_msg("error");
	i = 0;
	while (str1[i] && str1[i] != '=')
		i++;
	str1[i] = 0;
	len = i;
	i = 0;
	while (str2[i] && str2[i] != '=')
		i++;
	str2[i] = 0;
	if (i > len)
		len = i;
	ret = ft_strncmp(str1, str2, len);
	free(str1);
	free(str2);
	return (ret);
}

static char	**trie_tab_env(char **tab)
{
	int		i;
	int		j;
	char	*tmp;

	j = -1;
	while (tab[++j])
	{
		i = -1;
		while (tab[++i] && tab[i + 1])
		{
			if (ft_strncmp_env(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
			}
		}
	}
	return (tab);
}

static void	affiche_env_quote(char *str)
{
	int		i;
	char	*s1;
	char	*s2;

	i = 0;
	if (!(s1 = ft_strdup(str)))
		err_msg("error");
	while (s1[i] && s1[i] != '=')
		i++;
	s1[i] = 0;
	s2 = s1 + i + 1;
	write(1, s1, ft_strlen(s1));
	write(1, "=\"", 2);
	while (*s2)
	{
		if (*s2 == '\"')
			write(1, "\\", 1);
		write(1, s2++, 1);
	}
	write(1, "\"\n", 2);
	free(s1);
}

static void	affiche_env(t_list *list)
{
	int		size;
	int		i;
	char	*str;
	char	**tab;

	i = 0;
	size = ft_lstsize(list);
	if (!(tab = (char**)malloc(sizeof(char*) * (size + 1))))
		err_msg("error");
	while (list)
	{
		str = (char*)(list->content);
		tab[i++] = str;
		list = list->next;
	}
	tab[i] = NULL;
	tab = trie_tab_env(tab);
	i = -1;
	while (tab[++i])
	{
		write(1, "declare -x ", ft_strlen("declare -x "));
		affiche_env_quote(tab[i]);
	}
}

int			export_b(char **argv)
{
	int		i;
	int		argc;
	t_list	*list;
	int		ret;

	i = 0;
	ret = 0;
	list = g_my.env_list;
	argc = get_argc(argv);
	if (argc == 1)
	{
		affiche_env(list);
		g_my.ret = 0;
		return (0);
	}
	while (++i < argc)
	{
		if (check_env(argv[i], &ret) && !(set_env((g_my.env_list), argv[i])))
			return (1);
	}
	g_my.ret = ret;
	return (ret);
}
