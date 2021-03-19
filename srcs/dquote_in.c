/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:32:47 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/30 17:40:20 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	process_dquote_in(char *str, char **new, int *ind, int *j)
{
	int		i;
	char	*env;
	char	*big;
	char	*new_env;

	i = 0;
	(*ind)++;
	new_env = 0;
	while (str[(*ind) + i] && is_al_num_u(str[(*ind) + i]))
		i++;
	if (!(env = ft_substr(str, (*ind), i))
	|| !(new_env = ft_strdup(get_env(g_my.env_list, env))))
		p_error(errno);
	if (!(big = (char*)malloc(sizeof(char) * (ft_strlen(*new) +
						ft_strlen(new_env) + 1))))
		p_error(errno);
	ft_strlcpy(big, *new, ft_strlen(*new) + 1);
	ft_strlcpy(big + (*j), new_env, ft_strlen(new_env) + 1);
	(*ind) += (i - 1);
	(*j) += ft_strlen(new_env);
	free(env);
	free(*new);
	free(new_env);
	*new = big;
}
