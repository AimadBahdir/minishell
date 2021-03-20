# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/16 15:17:45 by abahdir           #+#    #+#              #
#    Updated: 2021/03/20 08:36:33 by abahdir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	main.c							\
		execution/createnv.c			\
		execution/crud_env.c			\
		execution/execmds_0.c			\
		execution/execmds_1.c			\
		execution/execmds_2.c			\
		execution/execmds_3.c			\
		execution/execmds_4.c			\
		execution/execmds_5.c			\
		execution/execmds_6.c			\
		execution/ft_atoi.c				\
		execution/ft_checkfor.c			\
		execution/ft_error.c			\
		execution/ft_exprint.c			\
		execution/ft_itoa.c				\
		execution/ft_putstr.c			\
		execution/ft_split.c			\
		execution/ft_strcmp.c			\
		execution/ft_strdup.c			\
		execution/ft_strjoin.c			\
		execution/ft_strlen.c			\
		execution/ft_strtolower.c		\
		execution/ft_strtrim.c			\
		execution/ft_substr.c			\
		gnl/get_next_line.c				\
		gnl/get_next_line_utils.c		\
		parsing/check_args.c			\
		parsing/check_args2.c			\
		parsing/check_syntax.c			\
		parsing/cut_args.c				\
		parsing/ft_trim.c				\
		parsing/function_utils.c		\
		parsing/function_utils2.c		\
		parsing/listshell_tcargs.c		\
		parsing/listshell_tgargs.c		\
		parsing/listshell_tgargs2.c		\
		parsing/listshell_tinputs.c		\
		parsing/management_args.c		\
		parsing/management_args2.c		\
		parsing/management_line.c

all : $(NAME)

$(NAME):$(SRC)
	gcc -Wall -Wextra -Werror $(SRC) -g -o minishell
clean:
	rm -rf minishell minishell.dSYM
fclean:
	rm -rf minishell minishell.dSYM
re: fclean all
