NAME	= shell
all		:
	cc -g -Wall -Wextra -Werror	minishell/clean_main.c \
	builtins/*.c environment/*.c executer/*.c parser/*.c tokenizer/*.c \
	-lreadline libft/libft.a -o $(NAME)
clean	:
	rm -rf *.o */*.o
fclean	:
	rm $(NAME)