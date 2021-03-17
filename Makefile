# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/16 15:17:45 by abahdir           #+#    #+#              #
#    Updated: 2021/03/17 08:42:16 by abahdir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c execution/*.c parsing/*.c gnl/*.c

all : $(NAME)

$(NAME):$(SRC)
	gcc -Wall -Wextra -Werror $(SRC) -g -o minishell
clean:
	rm -rf minishell minishell.dSYM
fclean:
	rm -rf minishell minishell.dSYM
re: fclean all
