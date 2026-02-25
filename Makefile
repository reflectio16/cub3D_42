# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/24 14:03:46 by meelma            #+#    #+#              #
#    Updated: 2026/02/25 15:05:35 by fmoulin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# === Nom de l'exécutable ===
NAME = cub3d

# === Fichiers sources ===
SRCS = main.c init.c events.c render.c my_mlx_pxl.c

# === Répertoires ===
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# === Objets ===
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# === Compilation ===
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O0
IFLAGS = -I$(INC_DIR) -Ilibft -Imlx
RM = rm -f

# === Libft ===
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# === MiniLibX Auto-téléchargement ===
LINK_MLX = https://cdn.intra.42.fr/document/document/46602/minilibx-linux.tgz
D_MLX = minilibx-linux
TAR_MLX = $(D_MLX).tgz
MLX_DIR = $(D_MLX)
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm -lbsd

# === Règle par défaut ===
all: $(LIBFT) $(MLX_LIB) $(NAME)

# === Compilation de Libft ===
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# === Téléchargement & Compilation de MiniLibX ===
$(MLX_LIB):
	@test -d $(MLX_DIR) || $(MAKE) $(TAR_MLX)
	@$(MAKE) -C $(MLX_DIR)

$(TAR_MLX):
	@echo "Téléchargement de MiniLibX..."
	@curl --output $@ $(LINK_MLX)
	@tar -xf $@
	@rm -f $@

# === Compilation de ton projet ===
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ $^ $(LIBFT) $(MLX_FLAGS)

# === Compilation des objets ===
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# === Nettoyage ===
clean:
	$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -rf $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re