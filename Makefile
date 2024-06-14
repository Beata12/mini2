# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/14 12:41:20 by bmarek            #+#    #+#              #
#    Updated: 2024/06/14 19:03:04 by aneekhra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[0;32m
RED = \033[0;31m
CYAN = \033[0;36m
PINK = \033[0;35m
MAGENTA = \033[0;35m
ENDCOLOR = \033[0m

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iincl
LFLAGS = -lreadline -Ireadline -L$(LFT_F) -lft -I$(LFT_F) ./ft_destructor/ft_alloc.a

RM = rm -rf
FT_DES = ft_destructor
LFT_F = libft
LIBFT = $(LFT_F)/libft.a

SRC_F = src/
OBJ_F = obj/
VPATH = $(SRC_F) $(SRC_F)execution/ $(SRC_F)utils/ $(SRC_F)parsing/ 
OBJ = $(addprefix $(OBJ_F), $(SRC:%.c=%.o))

SRC =	minishell.c \
		execute.c \
		tokenize.c \
		src/utils/signal_handlers.c \
		src/utils/errors_utils.c \
		src/utils/shell_data_cleaner.c \
		src/utils/utils_env_init.c \
		src/utils/env_operations.c \
		src/utils/shell_env_initializer.c \
		src/utils/environment_handler.c \
		src/parsing/parsing.c \
		src/parsing/dollar_var_expander.c \
		src/parsing/quote_handler.c \
		src/parsing/shell_command_parser.c \
		src/parsing/shell_command_processor.c \
		src/parsing/utils/input_validation.c \
		src/parsing/utils/validation_utils.c \
		src/parsing/utils/utils.c \
		src/parsing/utils/tokenization_utils.c \
		src/parsing/utils/string_separator.c \
		src/parsing/utils/string_utils.c \
		src/execution/manage_file_access.c \
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


all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo "${MAGENTA}				🚀 Compiling $(NAME)... 🚀${ENDCOLOR}"
	$(MAKE) -C $(FT_DES) --silent
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)
	clear
	@echo "${GREEN}			✅ $(NAME) Compilation completed successfully! ✅${ENDCOLOR}"
	@echo "${RED}				🚀 Run with ./minishell 🚀\n${ENDCOLOR}"

$(LIBFT):
	$(MAKE) -C $(LFT_F) --silent

$(OBJ_F)%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@  


v: all
	./$(NAME)
clean:
	$(RM) $(OBJ_F)
	$(RM) $(FT_DES)/*.
	$(RM) $(LFT_F)/*.o
	clear
	@echo "${RED}🧹 Cleaning objects... 🧹${ENDCOLOR}"

fclean: clean
	$(RM) $(NAME)
	$(RM) $(FT_DES)/ft_alloc.a
	$(RM) $(LFT_F)/libft.a
	clear
	@echo "${RED}🧹 Deep Cleaning $(NAME)... 🧹${ENDCOLOR}"
	
re: fclean all

.PHONY:	all clean fclean re bonus