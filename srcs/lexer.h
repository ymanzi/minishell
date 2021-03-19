/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafidi <ehafidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 09:58:57 by ymanzi            #+#    #+#             */
/*   Updated: 2020/12/01 13:35:43 by ehafidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef LEXER_H
#	define LEXER_H

#	include "../libft/libft.h"
#	include "get_next_line.h"
#	include "minishell.h"
#	include <string.h>
#	include <errno.h>
#	include <signal.h>
#	include <sys/types.h>
#	include <sys/wait.h>
#	include <dirent.h>
#	include <sys/stat.h>

#	define ERROR 0
#	define BON 1

#	define SPACE 0
#	define GREATER 1
#	define DGREATER 2
#	define SMALLER 3
#	define SEMICOLON 4
#	define PIPE 5
#	define DOLLAR_WHO 11
#	define OPTION 11
#	define SQUOTE 11
#	define DQUOTE 11
#	define DOLLAR_CARA 11
#	define STRING 11
#	define CMD 11
#	define EXEC 11
#	define FILE_N 14

#	define NODE_PIPE 1
#	define NODE_SEQ 2
#	define NODE_GREATER 3
#	define NODE_DGREATER 4
#	define NODE_SMALLER 5
#	define NODE_CMDPATH 6
#	define NODE_ARGUMENT 7
#	define NODE_DATA 8

struct s_tok;
struct s_lexer;
struct s_ast;
struct s_gen;

typedef struct		s_ast
{
	int				type;
	char			*data;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct		s_tok
{
	char			*data;
	int				type;
	struct s_tok	*next;
}					t_tok;

typedef struct		s_lexer
{
	char			*str;
	struct s_lexer	*next;
}					t_lexer;

typedef struct		s_gen
{
	int		ret;
	t_ast	*tree;
	t_lexer	*lst;
	int		sig;
	t_tok	*curtok;
	t_list	*env_list;
	char	*line;
	t_tok	*err;
	int		err_tree;
	t_ast	*node_err;
	int		export;
	int		val;
	char	*str_process;
	t_lexer	*lex_save;
}					t_gen;

/*
** Utils.c
*/
int					free_double_tab(char **tab);
char				*ft_join(char *s1, char const *s2);
void				free_token(t_tok **token);
void				free_tab_token(char **tab, t_tok *llist);

/*
** Utils2.c
*/
void				free_double_node(t_ast *node1, t_ast *node2);
int					is_spec(char c);
t_tok				*p_error(int err);
char				*ft_join_custom(char *s1, char *s2);
char				*ft_join_custom2(char *s1, char *s2);

/*
** Read_lexem.c
*/
int					read_lexem(char *str);

/*
** ltoken.c
*/
t_lexer				*lexer_init(char *str);
t_tok				*token_init(char *data, int type);
void				token_listadd_front(t_tok **alst, t_tok *new);
t_tok				*token_listlast(t_tok *lst);
void				token_listadd_back(t_tok **alst, t_tok *new);

/*
**	Ast.c
*/
void				ast_branch(t_ast *root, t_ast *left, t_ast *right);
void				ast_setdata(t_ast *node, char *data);
void				ast_settype(t_ast *node, int type);
t_ast				*new_ast(void);
void				ast_delete(t_ast *node);

/*
**	Ast2.c
*/
void				ast_setdata_type(t_ast *node, char *data, int type);

/*
**	Cmdline.c
*/
t_ast				*cmdline(void);
t_ast				*cmdline1(void);
t_ast				*cmdline2(void);
t_ast				*cmdline3(void);

/*
**	Job.c
*/
t_ast				*job(void);
t_ast				*job1(void);
t_ast				*job2(void);
t_ast				*job3(void);

/*
**	Cmd.c
*/
t_ast				*cmd(void);
t_ast				*cmd1(void);
t_ast				*cmd2(void);
t_ast				*cmd3(void);
t_ast				*cmd4(void);

/*
**	Simple_cmd.c
*/
t_ast				*simple_cmd(void);
t_ast				*simple_cmd1(void);

/*
**	Option_list.c
*/
t_ast				*option_list();
t_ast				*option_list1();

/*
**	Parser.c
*/
int					parser(t_ast **tree, int i);
int					is_sepa(char *str);
t_tok				*get_previous_tok(t_tok *start, t_tok *find);

/*
**	Check_open_quotes.c
*/
int					check_open_quotes(char *str);

/*
** Init.c
*/
void				gen(char **env, char *str);

/*
**	Get_env.c
*/
t_list				*create_env_list(char **env);
char				*get_env(t_list *list, char *elem);

/*
**	Ft_lstdel.c
*/
void				ft_lstdel(t_list **lst, char *s);
void				token_del_vide(t_tok **save, t_tok **tok, t_tok *prev);

/*
**	Tokez.c
*/
void				tokez(char *str);
void				new_token(char *data);
void				p_new_token(char *str, int *i, int *tab);

/*
**	Tokez2.c
*/
void				fct_space(char *str, int *tab, int *i);
void				fct_sep(char *str, int *tab, int *i);

/*
**	Parsing_suite.c
*/
void				parsing_suite(char **str);

/*
** Squote.c
*/
void				squote_suite(char *str, char *new, int *i, int *j);
/*
** Parsing_tok.c
*/
void				parsing_tok(t_tok *tok);
int					is_al_num_u(char c);

/*
**	Llexer.c
*/
void				lexer_free(t_lexer *lex);
t_lexer				*lexer_listlast(t_lexer *lst);
void				lexer_listadd_back(t_lexer **alst, t_lexer *new);

/*
**	Token_cut.c
*/
void				string_cut(t_lexer **lst);
void				process_string(char **str);

/*
**	Ignore_signal.c
*/
void				ignore_signal(void);
void				restore_signal();

/*
** Verif_cmd.c
*/
char				*get_abs_path_y(char **tab, char *func);
char				**get_path_table_y(char *str);

/*
**	Check_elem_vide.c
*/
void				check_elem_vide(t_ast **tree);
/*
**	Check_file.c
*/
int					check_file(t_tok *tok);
int					a_to_fd(char *filename, int ind);
/*
** Buildin
*/
int					get_argc(char **tab);
int					echo(char **argv);
int					env(char **argv);
int					init_pwd(void);

/*
** Cd.c
*/
int					cd(char **argv);
char				*spec_free(char **p);

/*
** Export.c
*/
int					ft_strncmp_env(char *s1, char *s2);
int					export_b(char **argv);

/*
**	File_error.c
*/
void				check_tree(t_ast *tree, int ind);
int					file_last_check(char **arr, int ind);

/*
** Env_utils.c
*/
int					set_env(t_list *list, char *str);
int					check_env(char *str, int *ret);
char				*ft_strdup_env(char *s);

/*
** Msg_error.c
*/
void				affiche_msg_error(void);
void				get_msg_error(t_ast *node);

/*
** Check_file_err.c
*/
int					cd_file_error(int err, char *file);
int					left_file_error(int err, char *file);
char				*check_home_cd(void);
char				*cd_get_env(t_list *list, char *elem);
int					check_executable(char *data);

/*
** A_to_fd.c
*/
int					a_to_fd(char *filename, int ind);
int					cd_process(t_tok *tok);

/*
** Check_file_utils.c
*/
int					file_error(int err, char *file);
t_tok				*check_pipe_suite(t_tok *tok);
int					check_file_greater_dgreat(t_tok *tok);
int					check_file_no_path(t_tok *tok);

/*
** Pwd.c
*/
int					init_pwd(void);
int					change_pwd(char **argv, char *status, char *p);
int					pwd(char **argv);

/*
** Unset.c
*/
int					unset(char **argv);

/*
** Show_msg.c
*/
void				show_msg(t_tok *save);

/*
** Dquote_inc.c
*/
void				process_dquote_in(char *str, char **new, int *ind, int *j);

/*
** Exit2.c
*/
void				write_exit(void);

extern t_gen		g_my;

#	endif
