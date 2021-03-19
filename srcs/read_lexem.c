/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lexem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 10:21:57 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/03 07:33:26 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	size_one(char *str)
{
	if (str[0] == ' ' || str[0] == '\t')
		return (SPACE);
	else if (str[0] == '>')
		return (GREATER);
	else if (str[0] == '<')
		return (SMALLER);
	else if (str[0] == ';')
		return (SEMICOLON);
	else if (str[0] == '|')
		return (PIPE);
	return (STRING);
}

int			read_lexem(char *str)
{
	if (ft_strlen(str) == 1)
		return (size_one(str));
	else if (ft_strlen(str) == 2 && !ft_strncmp(str, ">>", 2))
		return (DGREATER);
	else if (ft_strlen(str) == 2 && !ft_strncmp(str, "$?", 2))
		return (DOLLAR_WHO);
	else if (str[0] == '-')
		return (OPTION);
	else if (ft_strlen(str) >= 2 && str[0] == '\''
			&& str[ft_strlen(str) - 1] == '\'')
		return (SQUOTE);
	else if (ft_strlen(str) >= 2 && str[0] == '\"'
			&& str[ft_strlen(str) - 1] == '\"')
		return (DQUOTE);
	else if (ft_strlen(str) >= 2 && str[0] == '$')
		return (DOLLAR_CARA);
	else if (ft_strlen(str) >= 2 && !ft_strncmp(str, "./", 2))
		return (EXEC);
	else
		return (STRING);
}
