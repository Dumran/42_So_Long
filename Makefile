NAME=so_long
BONUS_NAME=so_long_bonus

SRCS = main.c utils.c map.c err.c dispose.c element.c image.c control.c
SRCS_BONUS = main_bonus.c utils_bonus.c map_bonus.c err_bonus.c dispose_bonus.c \
	element_bonus.c image_bonus.c control_bonus.c game_bonus.c enemy_bonus.c

MLX_DIR=lib/libmlx
MLX=$(MLX_DIR)/libmlx.a
LIBFT_DIR=lib/libft
LIBFT=$(LIBFT_DIR)/libft.a

CC=gcc
CFLAGS=-Wall -Wextra -Werror -I$(LIBFT_DIR) -I$(MLX_DIR)

$(NAME): $(LIBFT) $(MLX) $(SRCS)
	@$(CC) $(CFLAGS) $(SRCS) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

all: $(NAME) bonus

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT) $(MLX) $(SRCS_BONUS)
	@$(CC) $(CFLAGS) $(SRCS_BONUS) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -o $(BONUS_NAME)

$(LIBFT): $(LIBFT_DIR)/get_next_line/get_next_line.c $(LIBFT_DIR)/get_next_line/get_next_line_utils.c
	make -s -C $(LIBFT_DIR)

$(MLX):
	make -s -C $(MLX_DIR)

clean:
	make -s -C $(LIBFT_DIR) clean
	make -s -C $(MLX_DIR) clean

fclean: clean
	make -s -C $(LIBFT_DIR) fclean
	$(RM) $(NAME) $(BONUS_NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
