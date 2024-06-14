# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/12 20:57:52 by aneekhra          #+#    #+#              #
#    Updated: 2024/06/14 12:28:43 by bmarek           ###   ########.fr        #
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
		execute.c open_files.c \
		env_init.c parsing.c tokenize.c cmd.c cmd_init.c \
		utils_signals.c  utils_parsing.c utils_path.c \
		utils_env.c env_lst.c \
		src/utils/shell_data_cleaner.c \
		src/parsing/dollar_var_expander.c \
		src/parsing/quote_handler.c \
		src/parsing/utils/input_validation.c \
		src/parsing/utils/validation_utils.c \
		src/parsing/utils/utils.c \
		src/parsing/utils/errors_utils.c \
		src/parsing/utils/string_separator.c \
		src/parsing/utils/string_utils.c \
		src/execution/initialize_builtins.c \
		src/execution/utils/export_utils.c \
		src/execution/utils/handle_errors.c \
		src/execution/utils/utils_execute.c \
		src/execution/shell_commands/cd.c \
		src/execution/shell_commands/env.c \
		src/execution/shell_commands/pwd.c \
		src/execution/shell_commands/echo.c \
		src/execution/shell_commands/exit.c \
		src/execution/shell_commands/unset.c \
		src/execution/shell_commands/export.c \

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