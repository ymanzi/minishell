/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafidi <ehafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 16:15:08 by ehafidi           #+#    #+#             */
/*   Updated: 2020/11/30 16:12:14 by ehafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	protected_open(t_exec *exec, t_ast *nextcmd, int nodetype)
{
	if (nodetype == NODE_DGREATER)
	{
		exec->file = open(nextcmd->data, O_CREAT | O_RDWR | O_APPEND, 0666);
		if (exec->file == -1)
			err_msg("error");
	}
	else if (nodetype == NODE_GREATER)
	{
		exec->file = open(nextcmd->data, O_CREAT | O_RDWR | O_TRUNC, 0666);
		if (exec->file == -1)
			err_msg("error");
	}
	else if (nodetype == NODE_SMALLER)
	{
		exec->file = open(nextcmd->data, O_RDWR, 0666);
		if (exec->file == -1)
			err_msg("error");
	}
}

void	protected_pipe(int *fd)
{
	if (pipe(fd) == -1)
		err_msg("error");
}

void	protected_dup2(int *fd, int fileno)
{
	if (dup2(*fd, fileno) == -1)
		err_msg("error");
}

void	protected_fork(int *pid)
{
	*pid = fork();
	if (*pid == -1)
		err_msg("error");
	if (*pid == 0)
		restore_signal();
}

void	protected_close(int *fd)
{
	if (close(*fd) == -1)
		err_msg("error");
}
