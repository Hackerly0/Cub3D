CC = cc
CFLAGS = -Wall -Werror -Wextra -g -Iinclude -fsanitize=address

SRCS = main.c raycasting.c move.c minimap.c textures.c draw.c
SRCS := $(addprefix src/, $(SRCS))
OBJS = $(SRCS:.c=.o)

NAME = cub3D

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./MLX42
MLX = $(MLX_DIR)/build/libmlx42.a

MLXFLAGS = -Iinclude -ldl -lglfw -pthread -lm

all: LIBFT $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) -L$(LIBFT_DIR) -lft $(MLXFLAGS) -o $(NAME) 

%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

LIBFT:
	make -C $(LIBFT_DIR)

$(MLX):
	cmake -S $(MLX_DIR) -B $(MLX_DIR)/build
	cmake --build $(MLX_DIR)/build -j4

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: re all clean fclean LIBFT



# CC = cc
# CFLAGS = -Wall -Werror -Wextra -Iinclude -IMLX42/include

# SRCS = main.c
# SRCS := $(addprefix src/, $(SRCS))
# OBJS = $(SRCS:.c=.o)

# NAME = cub3D

# LIBFT_DIR = ./libft
# LIBFT = $(LIBFT_DIR)/libft.a

# MLX_DIR = ./MLX42
# MLX = $(MLX_DIR)/build/libmlx42.a

# MLXFLAGS = -ldl -lglfw -pthread -lm

# all: $(LIBFT) $(MLX) $(NAME)

# $(NAME): $(OBJS) $(LIBFT) $(MLX)
# 	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(NAME)

# %.o: src/%.c ./cub.h
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(LIBFT):
# 	make -C $(LIBFT_DIR)

# $(MLX):
# 	cmake -S $(MLX_DIR) -B $(MLX_DIR)/build
# 	cmake --build $(MLX_DIR)/build -j4

# clean:
# 	rm -f $(OBJS)
# 	make clean -C $(LIBFT_DIR)

# fclean: clean
# 	rm -f $(NAME)
# 	make fclean -C $(LIBFT_DIR)

# re: fclean all

# .PHONY: re all clean fclean
