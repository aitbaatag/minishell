NAME	= shell
all		:
	cc -g -Wall -Wextra -Werror	minishell/clean_main.c \
	builtins/*.c environment/*.c executer/*.c parser/*.c tokenizer/*.c \
	-lreadline libft/libft.a -o $(NAME)
clean	:
	tokenizer/*.o parser/*.o
fclean	:
	rm $(NAME)