/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 11:55:13 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/11 11:19:13 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_ast	*cmdline(void)
{
	t_tok	*save;
	t_ast	*node;

	save = g_my.curtok;
	if (g_my.curtok && (node = cmdline1()))
		return (node);
	g_my.curtok = save;
	if (g_my.curtok && (node = cmdline2()))
		return (node);
	g_my.curtok = save;
	if (g_my.curtok && (node = cmdline3()))
		return (node);
	return (NULL);
}

t_ast	*cmdline1(void)
{
	t_ast	*job_node;
	t_ast	*cmdline_node;
	t_ast	*result;

	if (!(job_node = job()))
		return (NULL);
	if (!g_my.curtok || g_my.curtok->type != SEMICOLON)
	{
		ast_delete(job_node);
		return (NULL);
	}
	g_my.curtok = g_my.curtok->next;
	if (!(cmdline_node = cmdline()))
	{
		ast_delete(job_node);
		return (NULL);
	}
	if (!(result = new_ast()))
	{
		free_double_node(job_node, cmdline_node);
		return (NULL);
	}
	result->type = NODE_SEQ;
	ast_branch(result, job_node, cmdline_node);
	return (result);
}

t_ast	*cmdline2(void)
{
	t_ast	*job_node;
	t_ast	*result;

	if (!(job_node = job()))
		return (NULL);
	if (!g_my.curtok || g_my.curtok->type != SEMICOLON)
	{
		ast_delete(job_node);
		return (NULL);
	}
	g_my.curtok = g_my.curtok->next;
	if (!(result = new_ast()))
	{
		ast_delete(job_node);
		return (NULL);
	}
	result->type = NODE_SEQ;
	ast_branch(result, job_node, NULL);
	return (result);
}

t_ast	*cmdline3(void)
{
	return (job());
}
