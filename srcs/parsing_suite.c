/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_suite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafidi <ehafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 19:13:43 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/16 10:40:03 by ehafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	process_dquote(char *str, char **new, int *ind, int *j)
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
	|| !(new_env = ft_strdup_env(get_env(g_my.env_list, env))))
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

static void	dquote(char *str, char **new, int *i, int *j)
{
	while (str[++(*i)])
	{
		if (str[*i] == '\\' && (str[(*i) + 1] == '\\' || str[(*i) + 1] == '$' ||
		str[(*i) + 1] == '\"'))
			(*new)[(*j)++] = str[++(*i)];
		else if (str[*i] == '$' && str[(*i) + 1]
				&& (ft_isalpha((str)[(*i) + 1]) || str[(*i) + 1] == '_'))
			process_dquote_in(str, new, i, j);
		else if (str[*i] == '$' && str[(*i) + 1]
				&& str[(*i) + 1] == '?')
		{
			(*new)[(*j)++] = (g_my.ret + 48);
			(*i)++;
		}
		else if (str[*i] == '\"')
			return ;
		else
			(*new)[(*j)++] = str[*i];
	}
}

static void	process_ret(char *str, char **new, int *ind, int *j)
{
	int		i;
	char	*env;
	char	*big;

	i = 0;
	str = 0;
	(*ind)++;
	i++;
	if (!(env = ft_itoa(g_my.ret)))
		p_error(errno);
	if (!(big = (char*)malloc(sizeof(char) * (ft_strlen(*new) +
						ft_strlen(env) + 1))))
		p_error(errno);
	ft_strlcpy(big, *new, ft_strlen(*new) + 1);
	ft_strlcpy(big + (*j), env,
			ft_strlen(env) + 1);
	(*ind) += (i - 1);
	(*j) += ft_strlen(env);
	free(env);
	free(*new);
	*new = big;
}

static void	p_parsing_suite(char **str, char **new, int *i, int *j)
{
	if ((*str)[*i] == '\\')
		(*new)[(*j)++] = (*str)[++(*i)];
	else if ((*str)[(*i)] == '\"')
		dquote(*str, new, i, j);
	else if ((*str)[(*i)] == '\'')
		squote_suite(*str, *new, i, j);
	else if ((*str)[(*i)] == '$' && (*str)[(*i) + 1]
	&& (ft_isalpha((*str)[(*i) + 1]) || (*str)[(*i) + 1] == '_'))
		process_dquote(*str, new, i, j);
	else if ((*str)[(*i)] == '$' && (*str)[(*i) + 1] && (*str)[(*i) + 1] == '?')
		process_ret(*str, new, i, j);
	else
		(*new)[(*j)++] = (*str)[*i];
}

void		parsing_suite(char **str)
{
	int		i;
	int		j;
	char	*new;

	i = -1;
	j = 0;
	if (!(new = ft_strdup(*str)))
		p_error(errno);
	while ((i != -1 && (*str)[i] && (*str)[++i]) || (i == -1 && (*str)[++i]))
		p_parsing_suite(str, &new, &i, &j);
	new[j] = 0;
	free(*str);
	*str = new;
}
