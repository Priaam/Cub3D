NAME        = cub3D
SRCS_DIR    = srcs/
INCLUDES_DIR= include/

LIBFT_PATH  = libs/Libft
LIBFT       = $(LIBFT_PATH)/libft.a
MLX_PATH    = libs/minilibx-linux
MLX         = $(MLX_PATH)/libmlx.a

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -MMD -MP -O3 -std=gnu11
INCLUDES    = -I$(INCLUDES_DIR) \
              -I$(LIBFT_PATH)/include \
              -I$(MLX_PATH)
LIB_FLAGS   = -L$(LIBFT_PATH) -lft \
              -L$(MLX_PATH) -lmlx \
              -lXext -lX11 -lm

SRCS_CORE   = main.c \
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
              bonus/doors/doors.c \
              weapon/weapon.c

SRCS_BONUS  = bonus/minimap/minimap_bonus.c \
              bonus/events/events.c

ifdef WITH_BONUS
	OBJS_DIR = objs_bonus/
	CFLAGS += -D BONUS=1
	SRCS = $(SRCS_CORE) $(SRCS_BONUS)
else
	OBJS_DIR = objs/
	SRCS = $(SRCS_CORE)
endif

OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB_FLAGS) -o $(NAME)

bonus:
	$(MAKE) WITH_BONUS=1 all

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH) bonus

$(MLX):
	$(MAKE) -C $(MLX_PATH)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf objs/ objs_bonus/
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(MLX_PATH) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all bonus clean fclean re