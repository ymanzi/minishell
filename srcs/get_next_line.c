/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafidi <ehafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 09:37:31 by ymanzi            #+#    #+#             */
/*   Updated: 2020/12/01 13:35:58 by ehafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	free_fct(char **line, char **tmp, int ret)
{
	if (*line != NULL && ret != 0)
	{
		free(*line);
		*line = NULL;
	}
	if (*tmp != NULL)
	{
		free(*tmp);
		*tmp = NULL;
	}
	return (ret);
}

int			get_next_line(int fd, char **line)
{
	char			buf[BUFFER_SIZE + 1];
	static char		*tmp[FOPEN_MAX] = {0};
	int				ret;

	ret = 1;
	if (!line || fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)
		return (-1);
	*line = NULL;
	if (!tmp[fd])
	{
		if (!(tmp[fd] = (char*)malloc(sizeof(char))))
			return (-1);
		tmp[fd][0] = '\0';
	}
	while (find_line(tmp[fd]) == -1 && (ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (!(tmp[fd] = ft_strjoin_gnl(tmp[fd], buf)))
			return (free_fct(line, &tmp[fd], -1));
	}
	creat_str_nl(tmp[fd], &tmp[fd], line, &ret);
	if (ret == -1)
		return (free_fct(line, &tmp[fd], -1));
	return ((ret > 0 ? 1 : free_fct(line, &tmp[fd], 0)));
}
