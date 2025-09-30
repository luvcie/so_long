NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Source files
SRCS = main.c \
       rendermap.c \
       parse_map.c \
       load_sprites.c \
       player_movement.c \
       get_next_line.c \
       cleanup.c \
       utils.c

# Object files
OBJS = $(SRCS:.c=.o)

# MLX path
MLX_PATH = ./minilibx-linux
MLX = $(MLX_PATH)/libmlx.a
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

# Libft
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a
LIBFT_INC = -I$(LIBFT_PATH)

# Include paths
INC = -I$(MLX_PATH) $(LIBFT_INC) -I.

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(MLX_PATH):
	@if [ ! -f $(MLX_PATH)/Makefile ]; then \
		rm -rf $(MLX_PATH); \
		git clone https://github.com/42Paris/minilibx-linux $(MLX_PATH); \
		./patch_minilibx.sh; \
	fi

$(MLX): $(MLX_PATH)
	make -C $(MLX_PATH)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_PATH) -lft $(MLX_FLAGS) -o $(NAME)

%.o: %.c so_long.h
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJS)
	@if [ -d $(MLX_PATH) ] && [ -f $(MLX_PATH)/Makefile.gen ]; then \
		make -C $(MLX_PATH) clean 2>/dev/null || true; \
	fi
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(MLX_PATH)
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
