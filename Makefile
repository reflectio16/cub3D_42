# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meelma <meelma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/24 14:03:46 by meelma            #+#    #+#              #
#    Updated: 2026/03/09 14:16:42 by meelma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# === Nom de l'exécutable ===
NAME = cub3d

# === Fichiers sources ===

SRC_SRCS	= main.c
GNL_SRCS	= get_next_line.c get_next_line_utils.c
PARSE_SRCS  = parse_utils.c parse_texture.c parse_color.c \
              parse_map.c validate_map.c flood_fill.c init.c

OBJS = $(SRC_OBJS) $(PARSE_OBJS) $(GNL_OBJS)

# === Répertoires ===
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes

# === Objets ===
SRC_OBJS = $(SRC_SRCS:%.c=$(OBJ_DIR)/src/%.o)
PARSE_OBJS = $(PARSE_SRCS:%.c=$(OBJ_DIR)/parsing/%.o)
GNL_OBJS = $(GNL_SRCS:%.c=$(OBJ_DIR)/gnl/%.o)

# === Compilation ===
CC = cc
CFLAGS = -Wall -Wextra -Werror 
IFLAGS = -I$(INC_DIR) -Ilibft -Imlx -Ignl
RM = rm -f

# === Libft ===
LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

# === MiniLibX Auto-téléchargement ===
LINK_MLX = https://cdn.intra.42.fr/document/document/34997/minilibx-linux.tgz
D_MLX = minilibx-linux
TAR_MLX = $(D_MLX).tgz
MLX_DIR = $(D_MLX)
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm -lbsd

# === Règle par défaut ===
all: $(LIBFT) $(NAME)

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
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ $^ $(LIBFT)

# === Compilation des objets ===
$(OBJ_DIR)/src/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)/src
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)/parsing/%.o: src/parsing/%.c
	@mkdir -p $(OBJ_DIR)/parsing
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)/gnl/%.o: gnl/%.c
	@mkdir -p $(OBJ_DIR)/gnl
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# === Nettoyage ===
clean:
	$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re