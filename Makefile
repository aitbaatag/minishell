NAME	= shell
all		:
	cc -g -Wall -Wextra -Werror	minishell/clean_main.c tokenizer/*.c builtins/*.c environment/*.c parser/*.c -lreadline libft/libft.a -o $(NAME)
clean	:
	tokenizer/*.o parser/*.o
fclean	:
	rm $(NAME)