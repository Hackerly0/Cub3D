# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: $(USER)                                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/23 20:40:00 by you               #+#    #+#              #
#    Updated: 2025/09/23 20:40:00 by you              ###   ########.fr        #
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
          $(SRC_DIR)/pad_map.c \
          $(SRC_DIR)/parse.c \
          $(SRC_DIR)/floodfill.c \
          $(SRC_DIR)/header_validation.c \
          $(SRC_DIR)/map_validation.c \
          $(SRC_DIR)/player_validation.c \
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
