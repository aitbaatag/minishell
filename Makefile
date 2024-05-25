NAME	= shell
all		:
	cc -g -Wall -Wextra -Werror	minishell/main.c tokenizer/*.c syntax/*.c parser/*.c -lreadline libft/libft.a -o $(NAME)
clean	:
	tokenizer/*.o parser/*.o
fclean	:
	rm $(NAME)