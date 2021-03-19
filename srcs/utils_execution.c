/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafidi <ehafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 13:13:42 by ehafidi           #+#    #+#             */
/*   Updated: 2020/11/30 12:51:58 by ehafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i] != NULL)
		free(arr[i]);
	free(arr);
}

char	**create_command_table(t_list **argv)
{
	t_list	*current;
	int		i;
	int		size;
	char	**arr;

	size = ft_lstsize(*argv);
	if (!(arr = malloc(sizeof(char*) * (size + 1))))
		err_msg("error");
	current = *argv;
	i = -1;
	while (current)
	{
		if (!(arr[++i] = ft_strdup((char *)(current->content))))
		{
			free_arr(arr);
			err_msg("error");
		}
		current = current->next;
	}
	arr[++i] = NULL;
	return (arr);
}

void	get_command_in_linked_list(t_list **argv, t_ast *cmdpath)
{
	t_list	*elem;
	char	*str;

	elem = *argv;
	while (cmdpath)
	{
		if (!(str = ft_strdup((char*)cmdpath->data))
		|| !(*argv = ft_lstnew(str)))
			err_msg("error");
		ft_lstadd_back(&elem, *argv);
		cmdpath = cmdpath->right;
	}
	*argv = elem;
}

t_ast	*get_corresponding_instruction(t_ast *node)
{
	node = node->right;
	node = node->left;
	return (node);
}
