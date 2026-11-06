NAME		= so_long

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -std=gnu17

SRC_DIR		= sources
SRC			= $(SRC_DIR)/main.c \
			  $(SRC_DIR)/map_check.c \
			  $(SRC_DIR)/render.c \
			  $(SRC_DIR)/move.c \
			  $(SRC_DIR)/exit.c
OBJ			= $(SRC:.c=.o)

LIBFT		= libft/libft.a
MLX_PATH	= minilibx-linux
MLX			= $(MLX_PATH)/libmlx.a

INCLUDES	= -I includes -I $(MLX_PATH)
LIBS		= $(LIBFT) -L $(MLX_PATH) -lmlx -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

%.o: %.c includes/so_long.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft

$(MLX):
	$(MAKE) -C $(MLX_PATH)

clean:
	rm -f $(OBJ)
	$(MAKE) -C libft clean
	$(MAKE) -C $(MLX_PATH) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
