GREEN = \033[0;32m
YELLOW = \033[0;33m
RE = \033[0m

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -lreadline -Ireadline -L$(LFT_F) -lft -I$(LFT_F)
HEADERS = incl/minishell.h incl/execute.h incl/parsing.h
LFT_F = libft
FT_DES = ft_destructor

SRC =	minishell.c \
		execute.c builtins1.c builtins2.c echo.c open_files.c \
		env_init.c parsing.c dollar_parse.c tokenize.c open_quotes.c cmd.c cmd_init.c \
		utils_signals.c  utils_parsing.c utils_symbol.c utils_path.c utils_execute.c \
		utils_env.c err.c err_parsing.c env_lst.c arr.c split_save_divider.c clean.c print.c \
		parsing/utils/input_validation.c \
		parsing/utils/validation_utils.c \
		parsing/utils/utils.c \
		parsing/utils/errors_utils.c \
		parsing/utils/string_separator.c \
		parsing/utils/string_utils.c \

SRC_F = src/
OBJ_F = obj/
VPATH = $(SRC_F) $(SRC_F)exec/ $(SRC_F)utils/ $(SRC_F)parsing/ 
OBJ = $(addprefix $(OBJ_F), $(SRC:%.c=%.o))

all: $(NAME)

$(NAME): $(OBJ)
	@printf "\n"
	$(MAKE) -C $(FT_DES)
	$(MAKE) -C $(LFT_F)
	$(CC) -o $@ $(OBJ) $(LFLAGS) $(CFLAGS) ./ft_destructor/ft_alloc.a
	@echo "$(GREEN)\n—————————————✣ MINISHELL COMPILED ✣—————————————\n$(RE)"

$(OBJ_F)%.o: %.c $(HEADERS) Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $<
	@printf "$(GREEN). $(RE)"

v: all
	valgrind --leak-check=full ./minishell
clean:
	rm -rf $(OBJ_F)

fclean: clean
	rm -f $(NAME)
	if [ -d "$(LFT_F)" ]; then \
		$(MAKE) fclean -C $(LFT_F); \
	fi
	if [ -d "$(FT_DES)" ]; then \
		$(MAKE) fclean -C $(FT_DES); \
	fi

re: fclean all
	$(MAKE) -j 12 all

.PHONY:	all clean fclean re bonus