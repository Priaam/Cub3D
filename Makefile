NAME = cub3d

SRCS_DIR = srcs/
OBJS_DIR = objs/
INCLUDES_DIR = include/

LIBFT_PATH = libs/Libft
LIBFT = $(LIBFT_PATH)/libft.a

MLX_PATH = libs/minilibx-linux
MLX = $(MLX_PATH)/libmlx.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g3

INCLUDES = -I$(INCLUDES_DIR) \
		   -I$(LIBFT_PATH)/include \
		   -I$(MLX_PATH)

LIB_FLAGS = -L$(LIBFT_PATH) -lft \
			-L$(MLX_PATH) -lmlx \
			-lXext -lX11 -lm

SRCS = main.c \
	   init/init.c \
	   init/init_structs.c \
	   parsing/check_extension.c \
	   parsing/parser.c \
	   parsing/map_data.c \
	   parsing/map_data_utils.c \
	   parsing/map_grid.c \
	   parsing/map_grid_utils.c \
	   parsing/check_data.c \
	   parsing/flood_fill.c \
	   parsing/flood_fill_utils.c \
	   minimap/minimap.c \
	   minimap/minimap_utiles.c \
	   minimap/minimap_render.c \
	   minimap/minimap_hook.c \
	   render/raycast.c \
	   render/render.c \
	   render/textured_wall.c \
	   textures/textures.c \
	   player/player.c

OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB_FLAGS) -o $(NAME)

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

.PHONY: all clean fclean re