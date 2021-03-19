/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_to_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:31:28 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/30 17:31:30 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	a_to_fd_ind_1(struct stat buffer)
{
	if (buffer.st_mode & S_IFDIR)
		return (1);
	else
	{
		if ((buffer.st_mode & S_IFREG && buffer.st_mode
		& S_IXUSR && buffer.st_mode & S_IRUSR))
			return (5);
		return (0);
	}
}

int			a_to_fd(char *filename, int ind)
{
	struct stat	buffer;

	if (stat(filename, &buffer) == 0)
	{
		if (!ind)
			return ((buffer.st_mode & S_IFDIR && buffer.st_mode & S_IXUSR));
		else if (ind == 1)
			return (a_to_fd_ind_1(buffer));
		else
		{
			if (buffer.st_mode & S_IFDIR)
				return (1);
			else
			{
				if ((buffer.st_mode & S_IFREG && buffer.st_mode & S_IWUSR))
					return (5);
				return (0);
			}
		}
	}
	else
		return (-1);
}

static int	cd_p_error(t_tok *tok)
{
	int	ret;

	ret = a_to_fd(tok->next->data, 0);
	if (ret == -1)
		return (cd_file_error(2, tok->next->data));
	else if (!ret)
		return (cd_file_error(EACCES, tok->next->data));
	return (1);
}

int			cd_process(t_tok *tok)
{
	char	*str;
	t_tok	*new;

	if (tok->next && tok->next->type == STRING &&
		ft_strlen(tok->next->data))
	{
		if (!cd_p_error(tok))
			return (0);
	}
	else if (!(tok->next) || (tok->next &&
	(tok->next->type != STRING || !ft_strlen(tok->next->data))))
	{
		if (!(tok->next))
		{
			str = check_home_cd();
			if (!str)
				return (ERROR);
		}
		else
			str = ".";
		if (!(new = token_init(str, STRING)))
			err_msg("error");
		token_listadd_front(&(tok->next), new);
	}
	return (1);
}
