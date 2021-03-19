/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 10:47:20 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/03 15:16:23 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == 0 && s2 == 0)
		return (NULL);
	if (!(ptr = (char*)malloc(sizeof(*ptr) * (ft_strlen(s1)
						+ ft_strlen(s2) + 1))))
		return (NULL);
	while (*(s1 + i))
		ptr[j++] = *(s1 + i++);
	i = 0;
	while (*(s2 + i))
		ptr[j++] = *(s2 + i++);
	ptr[j] = '\0';
	free(s1);
	s1 = NULL;
	return (ptr);
}

char	*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen((char*)s) < start)
		len = 0;
	if (s == 0 || !(ptr = (char*)malloc(sizeof(*ptr) * (len + 1))))
		return (NULL);
	while (len-- > 0 && *(s + start + i))
	{
		ptr[i] = s[start + i];
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}

int		find_line(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	creat_str_nl(char *s1, char **tmp, char **line, int *ret)
{
	int	i;

	if (*ret != -1)
	{
		i = find_line(s1);
		if (i > 0)
		{
			*line = ft_substr_gnl(s1, 0, i);
			*tmp = ft_substr_gnl(s1, i + 1, ft_strlen(s1) - i - 1);
		}
		else if (i < 0)
		{
			*line = ft_substr_gnl(s1, 0, ft_strlen(s1));
			*tmp = ft_substr_gnl(s1, ft_strlen(s1) + 2, 100);
		}
		else
		{
			*line = ft_substr_gnl(s1, ft_strlen(s1) + 2, 1);
			*tmp = ft_substr_gnl(s1, 1, ft_strlen(s1) - 1);
		}
		free(s1);
		s1 = NULL;
	}
	if (*line == NULL || *tmp == NULL)
		*ret = -1;
}
