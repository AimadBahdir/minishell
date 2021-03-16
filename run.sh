rm *.tst ; clear ; gcc -Wall -Wextra -Werror main.c execution/*.c -o minishell -g -fsanitize=address ; ./minishell
