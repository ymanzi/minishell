/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 15:49:02 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/10 16:50:29 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_list	*create_env_list(char **env)
{
	int		i;
	char	*str;
	t_list	*new;
	t_list	*list;

	i = -1;
	new = 0;
	list = 0;
	while (env[++i])
	{
		if (!(str = ft_strdup(env[i])) ||
		!(new = ft_lstnew((void*)str)))
		{
			if (str)
				free(str);
			ft_lstclear(&list, free);
			write(1, strerror(errno), ft_strlen(strerror(errno)));
			return (0);
		}
		ft_lstadd_back(&list, new);
	}
	return (list);
}

char	*get_env(t_list *list, char *elem)
{
	int	i;

	i = -1;
	while (list)
	{
		if (!ft_strncmp((char*)(list->content), elem, ft_strlen(elem))
				&& ((char*)(list->content))[ft_strlen(elem)] == '=')
			return ((char*)(list->content + ft_strlen(elem) + 1));
		list = list->next;
	}
	return ("");
}
