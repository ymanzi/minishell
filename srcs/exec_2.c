/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafidi <ehafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 12:29:55 by ehafidi           #+#    #+#             */
/*   Updated: 2020/11/30 12:30:59 by ehafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	goto_next_step_2(t_ast *node, t_exec *exec, t_list **argv)
{
	if (node->right->type == NODE_CMDPATH)
		launching_execve(node->right, exec, argv);
	else if (node->right->type == NODE_PIPE)
		pipe_nodes(node->right, exec, argv);
	else
		redirection_nodes(node->right, exec, argv);
}

void	pipe_nodes(t_ast *node, t_exec *exec, t_list **argv)
{
	int fd[2];
	int pid;

	protected_pipe(fd);
	protected_fork(&pid);
	if (pid == 0)
	{
		protected_dup2(&fd[1], STDOUT_FILENO);
		protected_close(&fd[0]);
		if (node->left->type == NODE_CMDPATH)
			launching_execve(node->left, exec, argv);
		else
			redirection_nodes(node->left, exec, argv);
		exit(g_my.ret);
	}
	protected_close(&fd[1]);
	if (waitpid(pid, &(g_my.ret), 0) == -1)
		err_msg("error");
	if (WIFEXITED(g_my.ret))
		g_my.ret = WEXITSTATUS(g_my.ret);
	if (g_my.err_tree && g_my.ret == 42)
		get_msg_error(node->left);
	protected_dup2(&fd[0], STDIN_FILENO);
	goto_next_step_2(node, exec, argv);
}

void	execute_job(t_ast *job, t_exec *exec, t_list **argv)
{
	if (job->type == NODE_DGREATER || job->type == NODE_GREATER ||
		job->type == NODE_SMALLER)
		redirection_nodes(job, exec, argv);
	else if (job->type == NODE_CMDPATH)
		launching_execve(job, exec, argv);
	else if (job->type == NODE_PIPE)
		pipe_nodes(job, exec, argv);
}
