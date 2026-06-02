# Nom de l'exécutable
NAME        = minimap

# Compilateur et flags
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -O3 -g3

# Chemins vers la MiniLibX (Ajusté selon ton arborescence ../../libs/...)
MLX_DIR     = ../../libs/minilibx-linux
MLX_INC     = -I$(MLX_DIR)
MLX_LNK     = -L$(MLX_DIR) -lmlx

# Inclusion des bibliothèques système (X11 et Math)
SYS_LNK     = -L/usr/lib -lXext -lX11 -lm

# Sources et Objets
SRCS        = minimap.c \
				minimap_utiles.c \
				minimap_render.c \
				minimap_hook.c \
				minimap_dda.c
OBJS        = $(SRCS:.c=.o)

# Règles principales
all: $(NAME)

# Compilation de la MiniLibX si nécessaire
$(MLX_DIR)/libmlx.a:
	@echo "🛠️  Vérification / Compilation de la MiniLibX..."
	@make -C $(MLX_DIR)

# Compilation de ton exécutable (Correction de l'ordre ici)
$(NAME): $(MLX_DIR)/libmlx.a $(OBJS)
	@echo "🚀 Compilation de $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LNK) $(SYS_LNK) -o $(NAME)

# Règle pour transformer les .c en .o
%.o: %.c
	$(CC) $(CFLAGS) $(MLX_INC) -I/usr/include -c $< -o $@

# Nettoyage des objets
clean:
	@echo "🧹 Nettoyage des fichiers objets..."
	rm -f $(OBJS)

# Nettoyage complet
fclean: clean
	@echo "🗑️  Nettoyage complet..."
	rm -f $(NAME)

# Recommencer à zéro
re: fclean all

.PHONY: all clean fclean re