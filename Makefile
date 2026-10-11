NAME = cub3D

SRCS_DIR = srcs/
OBJS_DIR = objs/
INCLUDES_DIR = include/

LIBFT_PATH = libs/Libft
LIBFT = $(LIBFT_PATH)/libft.a

MLX_PATH = libs/minilibx-linux
MLX = $(MLX_PATH)/libmlx.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -O3

INCLUDES = -I$(INCLUDES_DIR) \
		   -I$(LIBFT_PATH)/include \
		   -I$(MLX_PATH)

LIB_FLAGS = -L$(LIBFT_PATH) -lft \
			-L$(MLX_PATH) -lmlx \
			-lXext -lX11 -lm

SRCS_CORE = main.c \
            init/init.c \
            init/init_structs.c \
            parsing/check_extension.c \
            parsing/parser.c \
            parsing/map_data.c \
            parsing/map_data_utils.c \
            parsing/map_grid.c \
            parsing/map_grid_utils.c \
			parsing/map_grid_utils2.c \
            parsing/parse_colors.c \
            parsing/flood_fill.c \
            parsing/flood_fill_utils.c \
            events/events.c \
            utils/graphics_utils.c \
			utils/clean_exit.c \
            render/raycast.c \
            render/render.c \
            render/textured_wall.c \
            textures/textures.c \
            player/player.c \
			bonus/doors/doors.c

SRCS_BONUS = bonus/minimap/minimap_bonus.c 

OBJS_CORE = $(addprefix $(OBJS_DIR),$(SRCS_CORE:.c=.o))
OBJS_BONUS = $(addprefix $(OBJS_DIR),$(SRCS_BONUS:.c=.o))

DEPS = $(OBJS_CORE:.o=.d) $(OBJS_BONUS:.o=.d)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS_CORE)
	$(CC) $(CFLAGS) $(OBJS_CORE) $(LIB_FLAGS) -o $(NAME)

bonus: CFLAGS += -D BONUS=1
bonus: $(LIBFT) $(MLX) $(OBJS_CORE) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_CORE) $(OBJS_BONUS) $(LIB_FLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH) bonus

$(MLX):
	$(MAKE) -C $(MLX_PATH)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(MLX_PATH) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all bonus clean fclean re