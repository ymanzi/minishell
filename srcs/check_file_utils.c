/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:32:08 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/30 17:32:09 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			file_error(int err, char *file)
{
	char	*msg;

	msg = "minishell: ";
	write(1, msg, ft_strlen(msg));
	write(1, file, ft_strlen(file));
	write(1, ": ", 2);
	if (err == 18)
	{
		msg = "is a directory\n";
		write(1, msg, ft_strlen(msg));
	}
	else
	{
		write(1, strerror(err), ft_strlen(strerror(err)));
		write(1, "\n", 1);
	}
	if (err == 2)
		g_my.ret = 127;
	else if (err == 21 || err == EACCES || err == 18)
		g_my.ret = 126;
	return (0);
}

t_tok		*check_pipe_suite(t_tok *tok)
{
	while (tok)
	{
		if (tok->type == PIPE && tok->next && tok->next->type == STRING)
			return (tok);
		tok = tok->next;
	}
	return (0);
}

int			check_file_greater_dgreat(t_tok *tok)
{
	int	fd;

	fd = a_to_fd(tok->data, 2);
	if (fd == 1)
		file_error(21, tok->data);
	else if (fd == 0)
		file_error(EACCES, tok->data);
	if ((fd == 1 || fd == 0) && !(tok = check_pipe_suite(tok)))
		return (0);
	return (1);
}

int			check_file_no_path(t_tok *tok)
{
	int	fd;

	fd = a_to_fd(tok->data, 2);
	if (fd == 1)
		file_error(21, tok->data);
	else if (fd == 0)
		file_error(EACCES, tok->data);
	else if (fd == -1)
		file_error(2, tok->data);
	if ((fd == 1 || fd == 0 || fd == -1) && !(tok = check_pipe_suite(tok)))
		return (0);
	return (1);
}
