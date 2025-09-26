# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: $(USER)                                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/23 20:40:00 by you               #+#    #+#              #
#    Updated: 2025/09/26 20:40:00 by you              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iinclude -IGNL
NAME    = cub3d

# Directories
SRC_DIR = src
GNL_DIR = GNL

# Source files
SRCS    = $(SRC_DIR)/main.c \
          $(SRC_DIR)/parse_cub.c \
          $(SRC_DIR)/Parsing/map_builder.c \
          $(SRC_DIR)/Parsing/pad_map.c \
          $(SRC_DIR)/Parsing/parse_elements.c \
          $(SRC_DIR)/Utility/memory_utils.c \
          $(SRC_DIR)/Utility/utils.c \
          $(SRC_DIR)/Validation/flood_validation.c \
          $(SRC_DIR)/Validation/header_validation.c \
          $(SRC_DIR)/Validation/map_validation.c \
          $(SRC_DIR)/Validation/player_validation.c \
          $(GNL_DIR)/get_next_line.c \
          $(GNL_DIR)/get_next_line_utils.c

# Object files
OBJS    = $(SRCS:.c=.o)

# Default target
all: $(NAME)

# Build the executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS)

# Clean everything
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
