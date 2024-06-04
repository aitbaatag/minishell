NAME	= shell
all		:
	cc -g -Wall -Wextra -Werror	minishell/clean_main.c minishell/welcome.c minishell/signals.c \
	builtins/*.c environment/*.c executer/*.c \
	parser/*.c syntax/*.c tokenizer/*.c \
	-lreadline libft/libft.a -o $(NAME)
clean	:
	rm -rf *.o */*.o
fclean	:
	rm $(NAME)
