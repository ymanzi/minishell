/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mngmnt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafidi <ehafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 19:29:44 by ehafidi           #+#    #+#             */
/*   Updated: 2020/11/30 17:39:43 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	err_msg(char *cmd)
{
	char		*str;
	struct stat	buffer;

	stat(cmd, &buffer);
	if (buffer.st_mode & S_IFREG && buffer.st_mode
	& S_IXUSR)
		exit(0);
	if (errno == 8)
	{
		str = "minishell: ";
		write(1, str, ft_strlen(str));
		write(1, cmd, ft_strlen(cmd));
		str = ": Permission denied\n";
		write(1, str, ft_strlen(str));
		exit(126);
	}
	else
		write(1, strerror(errno), ft_strlen(strerror(errno)));
	exit(1);
}
