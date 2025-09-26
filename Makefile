# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/06 15:42:05 by tutku             #+#    #+#              #
#    Updated: 2025/09/26 14:52:27 by tcakir-y         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -I$(INC_DIR) -pthread -g

# Directories
INC_DIR = includes
SRC_DIR = src
OBJ_DIR = obj

# Source file
SRC =	main.c\
		check_error.c\
		free.c\
		init.c\
		monitor.c\
		routine.c\
		utils_print.c\
		utils_routine.c\
		utils.c\
		test.c

# Convert source file name into object file path inside obj/
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Executable name
NAME = philo

# Default rule: builds philo
all: $(NAME)

# Rule to compile .c files into .o files in obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/philo.h
					@mkdir -p $(OBJ_DIR)
					@echo "\033[0;33mCompiling $<.."
					@$(CC) $(CFLAGS) -c $< -o $@

# Rule to link executable
$(NAME):$(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "\033[0;32mAll files compiled!"

# Clean rule: removes object files
clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[0;31mAll object files removed."

# Full clean rule: removes executables
fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;31mAll executable files removed."

# Recompile everything
re: fclean all
	@echo "Object + exec files have been cleaned and rebuilt."
# Mark targets that are not actual files
.PHONY: all clean fclean re
