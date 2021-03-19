/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 10:46:16 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/01 18:54:36 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ast_branch(t_ast *root, t_ast *left, t_ast *right)
{
	if (root)
	{
		root->left = left;
		root->right = right;
	}
}

void	ast_setdata(t_ast *node, char *data)
{
	if (node && data)
	{
		node->type = read_lexem(data);
		node->data = data;
	}
}

void	ast_settype(t_ast *node, int type)
{
	if (node)
		node->type = type;
}

t_ast	*new_ast(void)
{
	t_ast	*new;

	if (!(new = (t_ast*)malloc(sizeof(t_ast))))
		return (NULL);
	new->left = 0;
	new->right = 0;
	return (new);
}

void	ast_delete(t_ast *node)
{
	if (node)
	{
		if (node->left)
			ast_delete(node->left);
		if (node->right)
			ast_delete(node->right);
		free(node);
	}
}
