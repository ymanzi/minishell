/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:51:30 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/02 19:52:48 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ast_setdata_type(t_ast *node, char *data, int type)
{
	if (node && data)
	{
		node->type = read_lexem(data);
		node->data = data;
		node->type = type;
	}
}
