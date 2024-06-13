# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: beata <beata@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/12 20:57:52 by aneekhra          #+#    #+#              #
#    Updated: 2024/06/13 11:25:42 by beata            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[0;32m
RED = \033[0;31m
CYAN = \033[0;36m
MAGENTA = \033[0;35m
ENDCOLOR = \033[0m

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iincl
LFLAGS = -lreadline -Ireadline -L$(LFT_F) -lft -I$(LFT_F)
# HEADERS = incl/minishell.h incl/execute.h incl/parsing.h
LFT_F = libft
FT_DES = ft_destructor

SRC =	minishell.c \
		execute.c builtins1.c builtins2.c echo.c open_files.c \
		env_init.c parsing.c dollar_parse.c tokenize.c cmd.c cmd_init.c \
		utils_signals.c  utils_parsing.c utils_symbol.c utils_path.c utils_execute.c \
		utils_env.c err_parsing.c env_lst.c split_save_divider.c clean.c print.c \
		parsing/quote_handler.c \
		parsing/utils/input_validation.c \
		parsing/utils/validation_utils.c \
		parsing/utils/utils.c \
		parsing/utils/errors_utils.c \
		parsing/utils/string_separator.c \
		parsing/utils/string_utils.c \
		execution/utils/handle_errors.c \
		execution/shell_commands/cd.c \
		execution/shell_commands/pwd.c \
		execution/shell_commands/exit.c \
		execution/shell_commands/env.c \
		execution/shell_commands/unset.c \
		# execution/shell_commands/export.c \


SRC_F = src/
OBJ_F = obj/
VPATH = $(SRC_F) $(SRC_F)execution/ $(SRC_F)utils/ $(SRC_F)parsing/ 
OBJ = $(addprefix $(OBJ_F), $(SRC:%.c=%.o))

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C $(FT_DES) --silent
	@$(MAKE) -C $(LFT_F) --silent

	@printf "\n"
	@echo "${MAGENTA}				🚀 Compiling $(NAME)... 🚀${ENDCOLOR}"
	$(CC) -o $@ $(OBJ) $(LFLAGS) $(CFLAGS) ./ft_destructor/ft_alloc.a
	@echo "${GREEN}\n			✅ $(NAME) Compilation completed successfully! ✅${ENDCOLOR}"
	@echo "${CYAN}				🚀 Run with ./minishell 🚀\n${ENDCOLOR}"
	
$(OBJ_F)%.o: %.c  Makefile
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $<


v: all
	@valgrind --leak-check=full ./minishell
clean:
	@echo "${RED}🧹 Cleaning objects... 🧹${ENDCOLOR}"
	@rm -rf $(OBJ_F)

fclean: clean
	@echo "${RED}🧹 Cleaning $(NAME)... 🧹${ENDCOLOR}"
	@rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re bonus