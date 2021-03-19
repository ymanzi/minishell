/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafidi <ehafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 09:45:52 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/22 19:02:52 by ehafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	p_check_exec(t_tok *tok)
{
	int	ret;

	ret = a_to_fd(tok->data, 1);
	if (ret == -1 || ret == 1 || !ret)
	{
		if (ret == -1)
			return (file_error(2, tok->data));
		else if (ret == 1)
			return (file_error(18, tok->data));
		else
			return (file_error(EACCES, tok->data));
	}
	return (1);
}

static int	p_check_file(t_tok *tok)
{
	char	**tab;
	char	*path;

	path = 0;
	if (!ft_strncmp(tok->data, "cd", 2) && !(tok->data)[2])
		return (cd_process(tok));
	else if ((!ft_strncmp(tok->data, "./", 2) ||
	!ft_strncmp(tok->data, "../", 3) || !ft_strncmp(tok->data, "/", 1)))
	{
		if (!p_check_exec(tok))
			return (0);
	}
	else if (compare_builtin(tok->data))
		return (1);
	else if (!(tab = get_path_table_y(get_env(g_my.env_list, "PATH")))
			|| !(path = get_abs_path_y(tab, tok->data)))
		return (0);
	free(path);
	return (1);
}

static int	check_string(t_tok **tok)
{
	int	fd;

	if (((*tok)->type == STRING && ft_strlen((*tok)->data))
	|| ((*tok)->type == PIPE && (*tok)->next && (*tok)->next->type == STRING))
	{
		if ((*tok)->type == PIPE)
			(*tok) = (*tok)->next;
		if (!ft_strlen(get_env(g_my.env_list, "PATH"))
		&& !check_file_no_path((*tok)))
			return (0);
		else if (!(p_check_file((*tok))) &&
		!((*tok) = check_pipe_suite((*tok))))
			return (0);
	}
	else if ((*tok)->type == SMALLER && (*tok)->next)
	{
		if ((fd = open((*tok)->next->data, O_RDONLY)) == -1)
			left_file_error(errno, (*tok)->next->data);
		if (fd == -1 && !((*tok) = check_pipe_suite((*tok)->next)))
			return (0);
		close(fd);
		(*tok) = (*tok)->next;
	}
	return (1);
}

int			check_file(t_tok *tokken)
{
	t_tok	*tok;

	tok = tokken;
	while (tok)
	{
		if (!check_string(&tok))
			return (0);
		while (tok && (tok->type == STRING || tok->type == GREATER
					|| tok->type == DGREATER))
		{
			if ((tok->type == GREATER || tok->type == DGREATER) &&
			tok->next->type == STRING && !check_file_greater_dgreat(tok->next))
				return (0);
			tok = tok->next;
		}
	}
	return (1);
}
