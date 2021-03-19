/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affich_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafidi <ehafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:26:28 by ehafidi           #+#    #+#             */
/*   Updated: 2020/11/30 16:24:11 by ehafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	get_arr_in_order(char **arr, int size)
{
	int		j;
	int		i;
	char	*buf;

	i = -1;
	j = -1;
	while (++j < (size - 1))
	{
		while (++i < (size - 1))
		{
			if (ft_strncmp(arr[i], arr[i + 1], 500) > 0)
			{
				buf = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = buf;
			}
		}
		i = -1;
	}
}

void	get_correct_string(char **arr, char **arr2, int size)
{
	int	i;
	int	j;

	size = 0;
	i = -1;
	j = -1;
	while (arr[++i])
	{
		while (++j < (int)ft_strlen(arr[i]))
		{
			if (arr[i][j] == '=')
			{
				if (!(arr2[i] = ft_strndup(arr[i], (j + 1))))
					err_msg("error");
				if (!(arr2[i] = ft_strjoin(arr2[i], "\"")))
					err_msg("error");
				if (!(arr2[i] = ft_strjoin(arr2[i], &arr[i][j + 1])))
					err_msg("error");
				if (!(arr2[i] = ft_strjoin(arr2[i], "\"")))
					err_msg("error");
			}
		}
		j = -1;
	}
}

void	fulfill_arr(char **arr, t_list *list, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		arr[i] = list->content;
		list = list->next;
	}
}

void	affiche_env(t_list *list)
{
	char	**arr;
	char	**arr2;
	int		lst_size;
	int		i;

	lst_size = ft_lstsize(list);
	if (!(arr = malloc(sizeof(char *) * (lst_size + 1))))
		err_msg("malloc");
	arr[lst_size] = NULL;
	if (!(arr2 = malloc(sizeof(char *) * (lst_size + 1))))
		err_msg("malloc");
	arr2[lst_size] = NULL;
	fulfill_arr(arr, list, lst_size);
	get_arr_in_order(arr, lst_size);
	get_correct_string(arr, arr2, lst_size);
	free_arr(arr);
	i = -1;
	while (arr2[++i])
	{
		write(1, "declare -x ", ft_strlen("declare -x "));
		write(1, arr2[i], ft_strlen(arr2[i]));
		write(1, "\n", 1);
	}
	free_arr(arr2);
}
