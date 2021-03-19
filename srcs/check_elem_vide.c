/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elem_vide.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafidi <ehafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 17:44:09 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/23 19:14:54 by ehafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	check_elem_vide(t_ast **tree)
{
	if ((*tree)->type == NODE_PIPE)
	{
		if ((*tree)->left->type == NODE_GREATER || (*tree)->left->type
		== NODE_DGREATER || (*tree)->left->type == NODE_SMALLER)
		{
			if ((*tree)->left->left && !ft_strlen((*tree)->left->left->data))
			{
				ast_delete((*tree)->left->left);
				(*tree)->left->left = 0;
			}
		}
	}
	else if ((*tree)->type == NODE_GREATER || (*tree)->type == NODE_DGREATER
			|| (*tree)->type == NODE_SMALLER)
	{
		if ((*tree)->left && !ft_strlen((*tree)->left->data))
		{
			ast_delete((*tree)->left);
			(*tree)->left = 0;
		}
	}
}
