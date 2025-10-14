CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iinclude -IGNL -fsanitize=address
NAME    = cub3D

# Directories
PARSE_DIR = src/Parser
RAYCAST_DIR = src/Raycasting/src
GNL_DIR = GNL
LIBFT_DIR = ./libft
MLX_DIR = ./MLX42

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/build/libmlx42.a
MLXFLAGS = -Iinclude -ldl -lglfw -pthread -lm

# Source files
SRCS    = src/main.c \
		src/config_to_cub.c \
		src/grab_questions.c \
		$(RAYCAST_DIR)/raycast.c \
		$(RAYCAST_DIR)/raycasting.c \
		$(RAYCAST_DIR)/move.c \
		$(RAYCAST_DIR)/minimap.c \
		$(RAYCAST_DIR)/textures.c \
		$(RAYCAST_DIR)/draw.c \
		$(RAYCAST_DIR)/door.c \
		$(RAYCAST_DIR)/init.c \
		$(RAYCAST_DIR)/ft_free_raycasting.c \
		$(RAYCAST_DIR)/animated_door.c \
		$(RAYCAST_DIR)/print.c \
		$(PARSE_DIR)/parse_cub.c \
		$(PARSE_DIR)/parse_cub_helper.c \
		$(PARSE_DIR)/parse_cub_helper2.c \
		$(PARSE_DIR)/Parsing/map_builder.c \
		$(PARSE_DIR)/Parsing/pad_map.c \
		$(PARSE_DIR)/Parsing/parse_elements.c \
		$(PARSE_DIR)/Utility/memory_utils.c \
		$(PARSE_DIR)/Utility/utils.c \
		$(PARSE_DIR)/Validation/flood_validation.c \
		$(PARSE_DIR)/Validation/header_validation.c \
		$(PARSE_DIR)/Validation/map_validation.c \
		$(PARSE_DIR)/Validation/player_validation.c \
		$(PARSE_DIR)/Validation/door_validation.c \
		$(GNL_DIR)/get_next_line.c \
		$(GNL_DIR)/get_next_line_utils.c

# Object files
OBJS    = $(SRCS:.c=.o)

# Default target
all: LIBFT MLX $(NAME)

# Build the executable
$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) -L$(LIBFT_DIR) -lft $(MLXFLAGS) -o $(NAME)

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build libft
LIBFT:
	make -C $(LIBFT_DIR)

# Build MLX42
MLX: $(MLX)

$(MLX):
	cmake -S $(MLX_DIR) -B $(MLX_DIR)/build
	cmake --build $(MLX_DIR)/build -j4

# Clean object files
clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)

# Clean everything
fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re LIBFT MLX