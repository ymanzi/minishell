/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 09:51:28 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/11 12:00:54 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void			one_quote(char *str, int *i)
{
	char	c;

	c = str[*i];
	while (str[++(*i)])
	{
		if (c == '\"' && str[*i] == '\\' && str[(*i) + 1])
			(*i)++;
		else if (str[(*i)] == c)
			return ;
	}
}

static void		p_string_cut(t_lexer **lst, char *str, int *i)
{
	t_lexer	*new;

	if ((*i) > 0)
	{
		str[(*i)] = 0;
		if (!(new = lexer_init(str)))
			err_msg("err");
		lexer_listadd_back(lst, new);
	}
}

void			string_cut(t_lexer **lst)
{
	int		i;
	char	*str;

	i = 0;
	*lst = 0;
	str = g_my.str_process;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
			i++;
		else if (str[i] == '\'' || str[i] == '\"')
			one_quote(str, &i);
		else if (str[i] == ';')
		{
			p_string_cut(lst, str, &i);
			while (str[i + 1] == ' ' || str[i + 1] == '\t')
				i++;
			str += i + 1;
			i = -1;
		}
		i++;
	}
	p_string_cut(lst, str, &i);
	free(g_my.line);
}

static void		pr_quote(char **str, int *ind)
{
	int		i;
	char	*env;
	char	*big;
	char	*new_env;

	i = 0;
	new_env = 0;
	while ((*str)[(*ind) + 1 + i] && is_al_num_u((*str)[(*ind) + 1 + i]))
		i++;
	if (!(env = ft_substr((*str), (*ind) + 1, i))
	|| !(new_env = ft_strdup_env(get_env(g_my.env_list, env))))
		p_error(errno);
	if (!(big = (char*)malloc(sizeof(char) * (ft_strlen((*str)) +
						ft_strlen(new_env) + 1))))
		p_error(errno);
	ft_strlcpy(big, (*str), ft_strlen((*str)) + 1);
	ft_strlcpy(big + (*ind), new_env, ft_strlen(new_env) + 1);
	ft_strlcat(big, (*str) + (*ind) + 1 + i,
	ft_strlen((*str)) + ft_strlen(big) + 1);
	(*ind) += ft_strlen(new_env) - 1;
	free(env);
	free(new_env);
	free(*str);
	*str = big;
}

void			process_string(char **str)
{
	int		i;
	char	*string;

	i = 0;
	string = *str;
	while (string[i])
	{
		if (string[i] == '\\' && string[i + 1])
			i++;
		else if (string[i] == '$' && string[i + 1]
			&& (ft_isalpha(string[i + 1]) || string[i + 1] == '_'))
		{
			pr_quote(str, &i);
			string = *str;
		}
		else if (string[i] == '\'' || string[i] == '\"')
			one_quote(string, &i);
		i++;
	}
}
