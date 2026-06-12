# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/24 12:42:07 by pserre-s          #+#    #+#              #
#    Updated: 2026/06/12 15:46:34 by pserre-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME         = cub3d

# --- CHEMINS ---
SRCS_DIR     = srcs/
OBJS_DIR     = objs/
INCLUDES_DIR = include/

LIBFT_PATH   = libs/Libft
LIBFT        = $(LIBFT_PATH)/libft.a

MLX_PATH     = libs/minilibx-linux
MLX          = $(MLX_PATH)/libmlx.a

# --- SOURCES ET OBJETS ---
SRCS         =	main.c \
				init_structs/init_structs.c \
				parsing/check_extension.c \
				parsing/parser.c \
				parsing/map_data.c \
				parsing/map_grid.c \
				parsing/check_data.c \
				minimap/minimap.c \
				minimap/minimap_utiles.c \
				minimap/minimap_render.c \
				minimap/minimap_hook.c \
				minimap/minimap_dda.c \
				3D_render/3d_display.c


SRCS_FILES   = $(addprefix $(SRCS_DIR), $(SRCS))
OBJS_FILES   = $(SRCS_FILES:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)
DEPS         = $(OBJS_FILES:.o=.d)

# --- COMPILATEUR ET FLAGS ---
CC           = cc
CFLAGS       = -Wall -Wextra -Werror -MMD -MP -g3
INCLUDES     = -I$(INCLUDES_DIR) -I$(LIBFT_PATH)/include -I$(MLX_PATH)

# Flags pour lier les bibliothèques
LIB_FLAGS    = -L$(LIBFT_PATH) -lft -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

# --- RÈGLES ---

all: $(NAME)

# Compilation finale
$(NAME): $(LIBFT) $(MLX) $(OBJS_FILES)
	@echo "🛠️ Création de l'exécutable $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS_FILES) $(LIB_FLAGS) -o $(NAME)
	@echo "✅ $(NAME) est prêt !"

# Compilation de la Libft
$(LIBFT):
	@echo "📚 Compilation de la Libft..."
	@make -C $(LIBFT_PATH) bonus

# Compilation de la MiniLibX
$(MLX):
	@echo "🖼️ Compilation de la MiniLibX..."
	@make -C $(MLX_PATH)

# Compilation des objets
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	@echo "  -> Compiling $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

-include $(DEPS)

clean:
	@echo "🧹 Nettoyage des objets..."
	@rm -rf $(OBJS_DIR)
	@make -C $(LIBFT_PATH) clean
	@make -C $(MLX_PATH) clean

fclean: clean
	@echo "🗑️ Nettoyage complet..."
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean
	# Note: La MLX n'a pas toujours de règle fclean, clean suffit souvent
	@echo "✨ Tout est propre."

re: fclean all

.PHONY: all clean fclean re