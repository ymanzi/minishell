/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafidi <ehafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:34:11 by ymanzi            #+#    #+#             */
/*   Updated: 2020/12/01 14:44:56 by ehafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	p_start_check(char **line, char **tmp)
{
	if (!(*line) && !ft_strlen(*tmp))
	{
		write(1, "\nexit\n", 6);
		free(*tmp);
		exit(0);
	}
	else if (!(*line = ft_join_custom(*line, *tmp)))
		err_msg("error");
}

static int	start_check(char **line, char *str)
{
	int		ret;
	char	*tmp;

	tmp = 0;
	*line = 0;
	while (!str && (ret = get_next_line(0, &tmp) <= 0))
		p_start_check(line, &tmp);
	if (!str && !(*line = ft_join_custom(*line, tmp)))
		err_msg("error");
	else if (str && !(*line = ft_strdup(str)))
		err_msg("error");
	g_my.line = *line;
	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (!(**line))
	{
		free(g_my.line);
		return (0);
	}
	if (!(check_open_quotes(*line)))
	{
		free(g_my.line);
		return (0);
	}
	return (1);
}

static int	main_boucle(t_lexer *lex_save)
{
	t_tok	*save;

	process_string(&(lex_save->str));
	tokez(lex_save->str);
	parsing_tok(g_my.curtok);
	if (!(check_file(g_my.curtok)))
	{
		free_token(&(g_my.curtok));
		return (0);
	}
	save = g_my.curtok;
	parser(&(g_my.tree), 1);
	check_elem_vide(&(g_my.tree));
	check_tree(g_my.tree, 0);
	execute_cmdline(g_my.tree);
	if (WIFEXITED(g_my.ret))
		g_my.ret = WEXITSTATUS(g_my.ret);
	ast_delete(g_my.tree);
	free_token(&save);
	return (1);
}

static void	init_gen(char **env, char *str, int *val, int ind)
{
	if (!ind)
	{
		g_my.env_list = create_env_list(env);
		g_my.ret = 0;
		init_pwd();
		*val = 42;
	}
	else
	{
		init_shlvl();
		if (str)
			*val = 0;
		else
			*val = 42;
		g_my.lst = 0;
		g_my.curtok = 0;
		ignore_signal();
	}
}

void		gen(char **env, char *str)
{
	char	*line;
	t_tok	*save;

	init_gen(env, 0, &(g_my.val), 0);
	while (g_my.val)
	{
		init_gen(env, str, &(g_my.val), 1);
		ft_putstr_fd("MiniShell%>", 1);
		if (!(start_check(&line, str)))
			continue ;
		g_my.str_process = line;
		tokez(line);
		save = g_my.curtok;
		if (!(parser(&(g_my.tree), 0)))
			continue ;
		free_token(&save);
		string_cut(&(g_my.lst));
		g_my.lex_save = g_my.lst;
		while (g_my.lex_save)
		{
			main_boucle(g_my.lex_save);
			g_my.lex_save = g_my.lex_save->next;
		}
		lexer_free(g_my.lst);
	}
}
