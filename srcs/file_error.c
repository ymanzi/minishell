/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:33:51 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/30 17:33:52 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int		a_to_f(char *filename)
{
	struct stat	buffer;

	if (stat(filename, &buffer) == 0)
	{
		if (buffer.st_mode & S_IFDIR)
			return (1);
		else
		{
			if ((buffer.st_mode & S_IFREG && buffer.st_mode & S_IRUSR))
				return (5);
			return (0);
		}
	}
	else
		return (-1);
}

static void		f_err(int err, char *file, char *cmd)
{
	t_tok	*tok;
	int		size;
	char	*data;

	size = ft_strlen(file) + ft_strlen(cmd) + ft_strlen(strerror(err)) + 6;
	if (!(data = (char*)malloc(sizeof(char) * size)))
		err_msg("error");
	data[0] = 0;
	ft_strlcat(data, cmd, ft_strlen(data) + ft_strlen(cmd) + 5);
	ft_strlcat(data, ": ", ft_strlen(data) + 2 + 5);
	ft_strlcat(data, file, ft_strlen(data) + ft_strlen(file) + 5);
	ft_strlcat(data, ": ", ft_strlen(data) + 2 + 5);
	ft_strlcat(data, strerror(err), ft_strlen(data) +
	ft_strlen(strerror(err)) + 5);
	ft_strlcat(data, "\n", ft_strlen(data) + 1 + 5);
	if (!(tok = token_init(data, STRING)))
		err_msg("error");
	token_listadd_back(&(g_my.err), tok);
}

int				file_last_check(char **arr, int ind)
{
	int	i;
	int	ret;
	int	fd;

	ret = 0;
	i = 0;
	if (ft_strncmp(arr[0], "cat", 4) && ft_strncmp(arr[0], "ls", 3))
		return (0);
	if (arr[1] && arr[1][0] == '-')
		i = 1;
	while (arr[++i])
	{
		fd = a_to_f(arr[i]);
		if (fd == -1 && ind)
			f_err(2, arr[i], arr[0]);
		else if (fd == 1 && ind)
			f_err(21, arr[i], arr[0]);
		else if (!fd && ind)
			f_err(EACCES, arr[i], arr[0]);
		if (!fd || fd == -1 || fd == 1)
			ret = 1;
	}
	return (ret);
}

static t_ast	*look_pipe(t_ast *tree)
{
	while (tree)
	{
		if (tree->type == NODE_PIPE)
			return (tree);
		tree = tree->right;
	}
	return (NULL);
}

void			check_tree(t_ast *tree, int ind)
{
	t_ast	*n_pipe;

	if (!ind)
		g_my.err_tree = 0;
	if (tree && !ind && tree->type != NODE_PIPE)
		return ;
	if (tree && tree->type == NODE_PIPE)
	{
		check_tree(tree->left, 2);
		check_tree(tree->right, 1);
	}
	else if (tree && tree->type == NODE_CMDPATH &&
(!ft_strncmp(tree->data, "echo", 5) || !ft_strncmp(tree->data, "cat", 5)))
	{
		g_my.err_tree = 1;
	}
	else if (tree && tree->type != NODE_CMDPATH)
	{
		if (!tree->left)
			return ;
		else
			check_tree(tree->left, 1);
		if (tree->right && (n_pipe = look_pipe(tree->right)))
			check_tree(n_pipe, 1);
	}
}
