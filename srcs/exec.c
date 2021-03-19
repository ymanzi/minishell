/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafidi <ehafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:04:33 by ehafidi           #+#    #+#             */
/*   Updated: 2020/11/30 16:18:02 by ehafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	closing_launch(t_ast *scmd, char **arr, t_exec *exec)
{
	if (WIFEXITED(g_my.ret))
		g_my.ret = WEXITSTATUS(g_my.ret);
	if (g_my.err_tree && g_my.ret == 42)
		get_msg_error(scmd);
	if (compare_builtin(arr[0]))
		exec_builtin(arr[0], arr);
	close(exec->file);
	dup2(exec->stdin_c, 0);
	dup2(exec->stdout_c, 1);
	close(exec->stdin_c);
	close(exec->stdout_c);
	free_arr(arr);
}

void	inside_child_process(t_ast *scmd, char **arr, t_exec *exec)
{
	char	*abs_path_cmd1;

	if (g_my.err_tree && file_last_check(arr, 0) && (g_my.node_err = scmd))
		exit(42);
	abs_path_cmd1 = get_abs_path(exec->paths_arr, &arr[0][0]);
	execve(abs_path_cmd1, arr, (char*[]){NULL});
	err_msg(abs_path_cmd1);
}

void	launching_execve(t_ast *scmd, t_exec *exec, t_list **argv)
{
	char	**arr;
	int		pid;

	exec->count++;
	if (exec->count <= 1)
	{
		exec->builtin++;
		get_command_in_linked_list(argv, scmd);
	}
	arr = create_command_table(argv);
	protected_fork(&pid);
	restore_signal();
	if (pid == 0)
	{
		if (!arr[0])
			if (!(arr[0] = ft_strdup("echo")))
				err_msg("malloc");
		if (!(compare_builtin(arr[0])))
			inside_child_process(scmd, arr, exec);
		else
			exit(0);
	}
	if (waitpid(pid, &(g_my.ret), 0) == -1)
		err_msg("error");
	closing_launch(scmd, arr, exec);
}

void	goto_next_step(t_ast *nxt_nod, t_ast *node, t_exec *exec, t_list **argv)
{
	if (nxt_nod->type == NODE_CMDPATH)
		launching_execve(node, exec, argv);
	else if (nxt_nod->type == NODE_PIPE)
		execute_job(nxt_nod->right, exec, argv);
	else
		redirection_nodes(nxt_nod, exec, argv);
}

void	redirection_nodes(t_ast *node, t_exec *exec, t_list **argv)
{
	t_ast *nextcmd;

	nextcmd = 0;
	exec->count++;
	if (exec->count == 1)
	{
		if (node->left != 0)
		{
			exec->builtin++;
			get_command_in_linked_list(argv, node->left);
		}
	}
	if (node->right->type != NODE_CMDPATH)
		nextcmd = get_corresponding_instruction(node);
	else if (node->right->type == NODE_CMDPATH)
		nextcmd = node->right;
	if (node->type == NODE_DGREATER || node->type == NODE_GREATER)
		protected_close_2(STDOUT_FILENO);
	else
		protected_close_2(STDIN_FILENO);
	protected_open(exec, nextcmd, node->type);
	if (nextcmd->right != 0)
		get_command_in_linked_list(argv, nextcmd->right);
	goto_next_step(node->right, node, exec, argv);
}
