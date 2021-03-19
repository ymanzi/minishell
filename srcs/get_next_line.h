/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 13:10:06 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/03 15:14:33 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef GET_NEXT_LINE_H
#	define GET_NEXT_LINE_H

#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#	ifndef BUFFER_SIZE
#	define BUFFER_SIZE 500
#	endif

int			get_next_line(int fd, char **line);
char		*ft_strjoin_gnl(char *s1, char *s2);
char		*ft_substr_gnl(char *s, unsigned int start, size_t len);
int			find_line(char *str);
void		creat_str_nl(char *s1, char **tmp, char **line, int *ret);

#	endif
