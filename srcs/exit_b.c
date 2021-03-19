/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafidi <ehafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 19:41:16 by ehafidi           #+#    #+#             */
/*   Updated: 2020/11/24 19:59:30 by ehafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int			check_only_digit(char *str)
{
	while (*str && (*str == '\t' || *str == '\n' || *str == '\v' ||
	*str == '\f' || *str == '\r' || *str == ' '))
		str++;
	if (*str && (*str == '-' || *str == '+'))
		str++;
	while (*str && ft_isdigit(*str))
		str++;
	while (*str && (*str == '\t' || *str == ' '))
		str++;
	if (*str)
		return (0);
	return (1);
}

static int			check_max(char *str, int minus)
{
	int	len;

	len = ft_strlen(str);
	if (len > 19)
		return (0);
	else if (len == 19 && minus == 1 &&
	ft_strncmp(str, "9223372036854775807", 20) > 0)
		return (0);
	else if (len == 19 && minus == -1 &&
	ft_strncmp(str, "9223372036854775808", 20) > 0)
		return (0);
	while (*str && ft_isdigit(*str))
		str++;
	while (*str && (*str == '\t' || *str == ' '))
		str++;
	if (*str)
		return (0);
	return (1);
}

static void			exit_err(char *str, int ind)
{
	char	*msg;

	msg = "minishell: exit: ";
	write(1, msg, ft_strlen(msg));
	if (!ind)
	{
		msg = "too many arguments\n";
		write(1, msg, ft_strlen(msg));
		exit(1);
	}
	write(1, str, ft_strlen(str));
	msg = ": numeric argument required\n";
	write(1, msg, ft_strlen(msg));
	exit(255);
}

static long long	c_strtoll(char *str, int minus)
{
	long long	nbr;

	nbr = 0;
	while (*str && ft_isdigit(*str))
	{
		nbr = nbr * 10 + (*str - 48);
		str++;
	}
	write(1, "exit\n", 5);
	return (nbr * minus);
}

void				exit_b(char **arr)
{
	int		argc;
	char	*str;
	int		minus;

	argc = get_argc(arr);
	minus = 1;
	if (argc == 1)
		write_exit();
	else if (!check_only_digit(arr[1]))
		exit_err(arr[1], 1);
	else if (argc > 2)
		exit_err(arr[1], 0);
	str = arr[1];
	while (*str && (*str == '\t' || *str == '\n' || *str == '\v' ||
	*str == '\f' || *str == '\r' || *str == ' '))
		str++;
	if (*str && (*str == '-' || *str == '+') && (*(str++) == '-'))
		minus *= -1;
	while (*str && *str == '0')
		str++;
	if (!(*str))
		write_exit();
	if (!check_max(str, minus))
		exit_err(arr[1], 1);
	exit((unsigned char)c_strtoll(str, minus));
}
