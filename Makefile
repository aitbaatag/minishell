ANSI_GREEN		:= \\033[38;5;2m
ANSI_RED		:= \\033[38;5;125m
ANSI_ORANGE		:= \\033[38;5;208m
ANSI_GOLD		:= \\033[38;5;214m
ANSI_CYAN		:= \\033[38;5;44m
ANSI_RESET		:= \\033[0m

# Compiler and flags
CC = cc
CFLAGS = 

# Source files
SRCS = ./shell/clean_main.c \
      ./executer/executer.c \
      ./executer/get_path.c \
	  ./executer/exec_cmd.c \
      ./executer/exec_pipe.c \
	  ./executer/exec_logic.c \
      ./executer/exec_subshell.c \
      ./executer/exec_redirection.c \
	  ./executer/exit_satus.c \
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
      ./parser/utils_heredoc.c \
      ./shell/signals.c \
      ./environment/environment.c \
      ./environment/env_utils.c \
      ./environment/helper_functions.c \
      ./environment/env_utils2.c \
      ./builtins/ft_cd.c \
      ./builtins/ft_echo.c \
      ./builtins/ft_exit.c \
      ./builtins/export.c \
      ./builtins/export_utils.c \
      ./builtins/builtins.c \
      ./builtins/ft_pwd.c \
      ./builtins/env.c \
      ./builtins/unset.c \
      ./syntax/syntax_analysis.c \
	  ./syntax/check_token_types.c \
	  ./syntax/other_checks.c \
      ./tokenizer/type_token.c \
      ./tokenizer/token.c \
      ./tokenizer/utils.c \
      ./tokenizer/utils_creator_nodes.c \
      ./garbage_collection/collection.c \
      ./libft/ft_split.c \
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

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)
	@printf "$(ANSI_ORANGE)"
	@printf "\n"
	@printf "\t███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓    \n"
	@printf "\t▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    \n"
	@printf "\t▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    \n"
	@printf "\t▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    \n"
	@printf "\t▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒\n"
	@printf "\t░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░\n"
	@printf "\t░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░\n"
	@printf "\t░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   \n"
	@printf "\t       ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░\n"
	@printf "$(ANSI_RESET)$(ANSI_CYAN)"
	@printf "\t\t\t\tby: asadiqui && kait-baa\n"
	@printf "\t\t\t\t^^^^^^^^^^^^^^^^^^^^^^^^\n"
	@printf "$(ANSI_RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@


clean:
	@rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all