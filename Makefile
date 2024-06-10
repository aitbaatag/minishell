# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Source files
SRCS = ./executer/exit_satus.c \
      ./shell/clean_main.c \
      ./executer/executer.c \
      ./executer/utils.c \
      ./executer/redirection.c \
      ./executer/get_path.c \
      ./executer/start_exec.c \
	  ./expander/expand_vars.c \
	  ./expander/expand_vars_utils.c \
	  ./expander/expand_status.c \
	  ./expander/expand_wildcards.c \
      ./parser/build_tree.c \
      ./parser/start_build_tree.c \
      ./parser/heredoc_list.c \
      ./parser/utils.c \
      ./parser/redir_tree.c \
      ./parser/utils2.c \
      ./parser/building_utils2.c \
      ./parser/building_utils.c \
      ./parser/parser.c \
      ./parser/utils_heredoc.c \
      ./shell/welcome.c \
      ./shell/signals.c \
      ./environment/environment.c \
      ./environment/env_utils.c \
      ./environment/helper_functions.c \
      ./environment/env_utils2.c \
      ./builtins/ft_cd.c \
      ./builtins/ft_echo.c \
      ./builtins/ft_exit.c \
      ./builtins/export.c \
      ./builtins/utils_builtins.c \
      ./builtins/builtins.c \
      ./builtins/ft_pwd.c \
      ./builtins/env.c \
      ./builtins/unset.c \
      ./syntax/syntax_analysis.c \
      ./syntax/checks.c \
      ./tokenizer/type_token.c \
      ./tokenizer/token.c \
      ./tokenizer/utils.c \
      ./tokenizer/utils_creator_nodes.c \
      ./garbage_collection/collection.c

# Libft source files
SRCS_LIBFT = ./libft/ft_split.c \
             ./libft/ft_strncmp.c \
             ./libft/ft_substr.c \
             ./libft/ft_atoi.c \
             ./libft/ft_isalpha.c \
             ./libft/ft_itoa.c \
             ./libft/ft_strchr.c \
             ./libft/ft_strlcpy.c \
             ./libft/ft_strdup.c \
             ./libft/ft_strlen.c \
             ./libft/ft_isdigit.c \
             ./libft/ft_putstr_fd.c \
             ./libft/ft_strjoin.c \
             ./libft/ft_strcmp.c \
             ./libft/ft_isalnum.c

# Header files
HEADERS = ./include/envs.h \
          ./include/builtins.h \
          ./include/syntax.h \
          ./include/executer.h \
          ./include/parser.h \
          ./include/tokenizer.h \
          ./include/minishell.h

OBJS = $(SRCS:.c=.o)
OBJS_LIBFT = $(SRCS_LIBFT:.c=.o)

NAME = minishell

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT)  -lreadline -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): $(SRCS_LIBFT)
	@make -C $(LIBFT_DIR)

clean:
	@rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all