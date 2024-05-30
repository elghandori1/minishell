NAME = minishell
LIBFT = libft/libft.a


SRC = main.c utils1.c ./execution/execution.c ./execution/execution_tools.c ./lexer/ft_split2.c ./lexer/lexer.c ./lexer/lexer_utils1.c ./lexer/lexer_utils2.c ./lexer/split_1.c\
    ./lexer/syntax_error.c ./lexer/syntax_error_utils.c ./lexer/ft_split2_utils.c \
	./lexer/split_2.c  ./builtins/run_builtin.c \
	./qoutes_remover/quotes_remover.c  ./qoutes_remover/quotes_remover_utils1.c ./qoutes_remover/quotes_remover_utils2.c \
	./herdoc_expand/herdoc_expander.c ./herdoc_expand/herdoc_expander_utils2.c ./herdoc_expand/herdoc_expander_utils1.c\
    ./expand/expand_utils1.c ./expand/expand_utils2.c ./expand/expand.c \
	./get_cmd/get_cmds.c ./get_cmd/get_cmd_utils1.c ./get_cmd/get_cmd_utils2.c\
	./builtins/ft_echo.c ./builtins/ft_cd.c ./builtins/ft_pwd.c ./builtins/ft_env.c \
	./builtins/tools_list_env.c ./builtins/ft_exit.c ./builtins/tools_list_env2.c \
	./builtins/ft_export.c ./builtins/ft_export_tools.c ./builtins/ft_unset.c \
	./execution/stdin_out.c ./execution/run_cmd.c ./execution/tools_run_cmd.c ./execution/env_toarray.c ./execution/ft_herdoc.c \
	./execution/ft_pipe.c ./execution/ft_pipe_tools.c ./execution/ft_pipe_tools2.c ./execution/ft_pipe_tools3.c ./execution/signals.c 


OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

%.o : %.c
	$(CC) $(CFLAGS) -c $? -o $@

all : $(NAME)

$(LIBFT):
	make -C libft

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -L ./rdln -lreadline -lcurses $(OBJ) $(LIBFT) -o $(NAME)

clean:
	rm -rf $(OBJ)
	make clean -C libft

fclean:
	rm -rf $(NAME) $(OBJ)
	make fclean -C libft

clear:
	clear

re: fclean all clean  clear

