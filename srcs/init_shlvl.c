/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shlvl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafidi <ehafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 13:06:48 by ehafidi           #+#    #+#             */
/*   Updated: 2020/11/30 19:13:59 by ehafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void		add_new_link(t_list **list, char *content)
{
	t_list	*elem;

	elem = *list;
	if (!(*list = ft_lstnew((char *)(content))))
		err_msg("error");
	ft_lstadd_back(&elem, *list);
	*list = elem;
}

void		shlvl_err_msg(int shlvl)
{
	write(1, "minishell: warning: shell level (",
		ft_strlen("minishell: warning: shell level ("));
	ft_putnbr_fd(shlvl, STDERR_FILENO);
	ft_putstr_fd(") too high, resetting to 1\n", STDERR_FILENO);
}

int			go_to_shlvl(t_list **env)
{
	int		exist;
	t_list	*temp;

	temp = *env;
	exist = 0;
	while (temp)
	{
		if (ft_strncmp(temp->content, "SHLVL=", 6) == 0)
		{
			exist++;
			break ;
		}
		temp = temp->next;
	}
	*env = temp;
	return (exist);
}

void		set_env_content(int shlvl, t_list **env)
{
	char	*new_shlvl;
	t_list	*temp;
	char	*buf;

	temp = *env;
	if (!(buf = ft_itoa(shlvl)))
		err_msg("error");
	if (!(new_shlvl = ft_strjoin("SHLVL=", buf)))
		err_msg("error");
	free(buf);
	free(temp->content);
	temp->content = new_shlvl;
	*env = temp;
}

void		init_shlvl(void)
{
	int		exist;
	t_list	*env;
	int		i;
	int		shlvl;

	env = g_my.env_list;
	if ((exist = go_to_shlvl(&env)) > 0)
	{
		i = 0;
		while (ft_strncmp(&env->content[i], "=", 1) != 0)
			i++;
		shlvl = (int)ft_atoi_2((const char*)&env->content[++i]);
		shlvl++;
		(shlvl < 0) ? shlvl = 0 : shlvl;
		if (shlvl > 1000)
		{
			if (shlvl < INT_MAX)
				shlvl_err_msg(shlvl);
			shlvl = 1;
		}
		set_env_content(shlvl, &env);
	}
	else
		add_new_link(&g_my.env_list, "SHLVL=1");
}
