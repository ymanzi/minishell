/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:32:29 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/28 15:33:28 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char		*ft_strdup_env(char *s)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	if (!(ptr = (char*)malloc(sizeof(*ptr) * ((i * 2) + 1))))
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\\' || s[i] == ' ')
			ptr[j++] = s[i];
		else if (s[i] == '\'' || s[i] == '\"')
			ptr[j++] = '\\';
		ptr[j++] = s[i++];
	}
	ptr[j] = 0;
	return (ptr);
}

static int	find_carac(char *str, char c)
{
	int i;

	i = -1;
	if (!str)
		return (-1);
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	return (-1);
}

static void	env_err(char *str)
{
	char	*msg;

	msg = "minishell: export: `";
	write(1, msg, ft_strlen(msg));
	write(1, str, ft_strlen(str));
	msg = "': not a valid identifier\n";
	write(1, msg, ft_strlen(msg));
}

int			set_env(t_list *list, char *str)
{
	int		i;
	t_list	*save;

	i = find_carac(str, '=');
	save = list;
	if (i == -1 || g_my.export)
		return (1);
	while (save)
	{
		if (!ft_strncmp_env((char*)(save->content), str))
		{
			free(save->content);
			if (!(save->content = ft_strdup(str)))
				err_msg("error");
			return (1);
		}
		save = save->next;
	}
	if (!(str = ft_strdup(str))
	|| !(save = ft_lstnew(str)))
		err_msg("error");
	ft_lstadd_back(&list, save);
	return (1);
}

int			check_env(char *str, int *ret)
{
	int		ind;
	int		i;

	i = -1;
	ind = 0;
	while (str[++i] && str[i] != '=')
	{
		if (!i && !(ft_isalpha(str[i]) || str[i] == '_'))
			ind = 1;
		else if (i && !((ft_isalnum(str[i]) || str[i] == '_')))
			ind = 1;
		if (ind == 1)
			break ;
	}
	if (!ft_strlen(str) || !find_carac(str, '=') || ind == 1)
	{
		*ret = 1;
		env_err(str);
		return (0);
	}
	return (1);
}
