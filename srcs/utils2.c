/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:03:53 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/16 09:11:16 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_double_node(t_ast *node1, t_ast *node2)
{
	ast_delete(node1);
	ast_delete(node2);
}

t_tok	*p_error(int err)
{
	write(1, strerror(err), ft_strlen(strerror(err)));
	write(1, "\n", 1);
	exit(ERROR);
	return (NULL);
}

int		is_spec(char c)
{
	int		i;
	char	*str;

	i = -1;
	str = "<>|;";
	while (str[++i])
	{
		if (c == str[i])
			return (1);
	}
	return (0);
}

char	*ft_join_custom(char *s1, char *s2)
{
	int		size_s1;
	int		size_s2;
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == 0)
		size_s1 = 0;
	else
		size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	if (!(ptr = (char*)malloc(sizeof(*ptr) * (size_s1 + size_s2 + 1))))
		return (0);
	while (s1 && *(s1 + i))
		ptr[j++] = *(s1 + i++);
	i = 0;
	while (*(s2 + i))
		ptr[j++] = *(s2 + i++);
	ptr[j] = '\0';
	free(s1);
	free(s2);
	return (ptr);
}

char	*ft_join_custom2(char *s1, char *s2)
{
	int		size_s1;
	int		size_s2;
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == 0)
		size_s1 = 0;
	else
		size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	if (!(ptr = (char*)malloc(sizeof(*ptr) * (size_s1 + size_s2 + 1))))
		return (0);
	while (s1 && *(s1 + i))
		ptr[j++] = *(s1 + i++);
	i = 0;
	while (*(s2 + i))
		ptr[j++] = *(s2 + i++);
	ptr[j] = '\0';
	free(s1);
	return (ptr);
}
