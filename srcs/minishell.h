/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafidi <ehafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 13:08:33 by ehafidi           #+#    #+#             */
/*   Updated: 2020/11/30 17:31:43 by ehafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef MINISHELL_H
#	define MINISHELL_H

#	include <unistd.h>
#	include "../libft/libft.h"
#	include <sys/types.h>
#	include <sys/stat.h>
#	include <fcntl.h>
#	include <stdbool.h>
#	include <limits.h>
#	include <stdio.h>

typedef struct s_ast	t_ast;

typedef struct			s_exec
{
	int		sign_n;
	int		pid;
	int		count;
	char	*paths_line;
	char	**paths_arr;
	int		file;
	int		builtin;
	int		stdin_c;
	int		stdout_c;
}						t_exec;

void					err_msg(char *cmd);

char					*get_path(char **envp);
char					**get_path_table(char *paths_line);
bool					file_exists(char *filename);
char					*get_abs_path(char **paths_arr, char *func);

void					free_arr(char **arr);
char					**create_command_table(t_list **argv);

void					get_command_in_linked_list(t_list **argv,
						t_ast *cmdpath);
t_ast					*get_corresponding_instruction(t_ast *node);

void					execute_job(t_ast *job, t_exec *exec, t_list **argv);

void					freed_from_desire(t_exec *exec);

void					protected_open(t_exec *exec,
						t_ast *nextcmd, int nodetype);
void					protected_pipe(int *fd);
void					protected_dup2(int *fd, int fileno);
void					protected_fork(int *pid);
void					protected_close(int *fd);
void					protected_close_2(int fd);

void					goto_next_step(t_ast *nxt_nod,
						t_ast *node, t_exec *exec, t_list **argv);
void					redirection_nodes(t_ast *node,
						t_exec *exec, t_list **argv);
void					launching_execve(t_ast *scmd,
						t_exec *exec, t_list **argv);
void					pipe_nodes(t_ast *node, t_exec *exec, t_list **argv);
void					execute_cmdline(t_ast *cmdline);

void					exec_builtin(char *str, char **arr);
int						compare_builtin(char *str);

void					exit_b(char **arr);

void					init_shlvl(void);

int						ft_atoi_2(const char *nptr);
#	endif
