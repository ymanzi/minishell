/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:34:01 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/30 17:34:02 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void		get_msg_error(t_ast *node)
{
	char	**arr;
	t_list	*argv;

	argv = 0;
	get_command_in_linked_list(&argv, node);
	arr = create_command_table(&argv);
	file_last_check(arr, 1);
}

void		affiche_msg_error(void)
{
	char	*msg;
	t_tok	*cur;

	if (g_my.err_tree)
	{
		cur = g_my.err;
		while (cur)
		{
			msg = cur->data;
			write(1, msg, ft_strlen(msg));
			cur = cur->next;
		}
	}
	free_token(&(g_my.err));
	g_my.err = 0;
}
