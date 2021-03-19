# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehafidi <ehafidi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 14:05:13 by ymanzi            #+#    #+#              #
#    Updated: 2020/12/01 12:37:07 by ehafidi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
NAME = lexer.a
CFLAGS = -Wall -Werror -Wextra
SRCS = srcs/utils.c srcs/utils2.c srcs/read_lexem.c srcs/token_cut.c srcs/parsing_tok.c\
	 srcs/ltoken.c srcs/ast.c srcs/cmdline.c srcs/job.c srcs/cmd.c srcs/simple_cmd.c srcs/verif_cmd.c\
	 srcs/parser.c srcs/check_open_quotes.c srcs/ast2.c srcs/init.c srcs/ignore_signal.c\
	 srcs/get_next_line.c srcs/get_next_line_utils.c srcs/option_list.c srcs/get_env.c \
	 srcs/ft_lstdel.c srcs/tokez.c srcs/tokez2.c srcs/parsing_suite.c srcs/llexer.c srcs/squote.c \
	 srcs/error_mngmnt.c srcs/path_env_processing.c \
	 srcs/exec.c srcs/utils_execution.c srcs/protected_functions.c srcs/execute_cmdline.c\
	 srcs/check_elem_vide.c srcs/check_file.c srcs/buildin.c srcs/exit_b.c srcs/export.c \
	 srcs/affich_env.c srcs/init_shlvl.c srcs/init_shlvl_utils.c srcs/exec_2.c \
	 srcs/file_error.c srcs/env_utils.c \
	 srcs/msg_error.c srcs/check_file_err.c srcs/a_to_fd.c srcs/cd.c \
	 srcs/check_file_utils.c srcs/pwd.c srcs/unset.c srcs/show_msg.c srcs/dquote_in.c srcs/exit2.c

LFT_SRC = libft
LIBFT = $(LFT_SRC)/libft.a
OBJ = $(SRCS:.c=.o)
 
all: $(LIBFT) $(NAME)
	$(CC) $(CFLAGS) main.c lexer.a -o minishell
$(NAME): $(OBJ)
		cp $(LIBFT) $(NAME)
		ar rc $(NAME) $(OBJ)
$(LIBFT):
		(cd $(LFT_SRC) && $(MAKE))
clean:
		rm -f $(OBJ) 
		(cd $(LFT_SRC) && $(MAKE) $@)
fclean: clean
		rm -f $(NAME)
		rm -f minishell
		(cd $(LFT_SRC) && $(MAKE) $@)
re: fclean all

.PHONY:all fclean re
