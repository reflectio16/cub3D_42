# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meelma <meelma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/24 14:03:46 by meelma            #+#    #+#              #
#    Updated: 2026/03/16 13:32:39 by meelma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# === Executable Name ===
NAME = cub3D

# === Source Files ===
SRC_SRCS    = main.c
GNL_SRCS    = get_next_line.c get_next_line_utils.c
PARSE_SRCS  = parse_utils.c parse_texture.c parse_color.c \
              parse_map.c validate_map.c flood_fill.c init.c \
              is_map_closed.c clean.c parse_color_02.c
RENDER_SRCS = render.c events.c move.c rotation.c my_mlx_pxl.c \
              dda_debug.c c_w_f_render.c display_data.c load_texture.c \
              wall_floor_utils.c ray_utils.c player_pixel_utils.c game_init.c

# === Object Files ===
OBJS = $(SRC_OBJS) $(PARSE_OBJS) $(GNL_OBJS) $(RENDER_OBJS)

# === Directories ===
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# === Object Paths ===
SRC_OBJS = $(SRC_SRCS:%.c=$(OBJ_DIR)/src/%.o)
PARSE_OBJS = $(PARSE_SRCS:%.c=$(OBJ_DIR)/parsing/%.o)
GNL_OBJS = $(GNL_SRCS:%.c=$(OBJ_DIR)/gnl/%.o)
RENDER_OBJS = $(RENDER_SRCS:%.c=$(OBJ_DIR)/render/%.o)

# === Compiler Settings ===
CC = cc
CFLAGS = -Wall -Wextra -Werror
IFLAGS = -I$(INC_DIR) -ILibft -Ignl -I$(MLX_DIR)
RM = rm -f

# === Libft ===
LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

# === MiniLibX ===
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
LINK_MLX = https://cdn.intra.42.fr/document/document/34997/minilibx-linux.tgz
TAR_MLX = $(MLX_DIR).tgz

# === Default Rule ===
all: $(LIBFT) $(MLX_LIB) $(NAME)

# === Compile Libft ===
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# === Compile MiniLibX ===
$(MLX_LIB):
	@if [ ! -d $(MLX_DIR) ]; then \
		echo "Downloading MiniLibX..."; \
		curl --output $(TAR_MLX) $(LINK_MLX); \
		tar -xf $(TAR_MLX); \
		rm -f $(TAR_MLX); \
	fi
	@$(MAKE) -C $(MLX_DIR)

# === Link Project ===
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(MLX_FLAGS)

# === Compile Source Objects ===
$(OBJ_DIR)/src/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)/src
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# === Compile Parsing Objects ===
$(OBJ_DIR)/parsing/%.o: src/parsing/%.c
	@mkdir -p $(OBJ_DIR)/parsing
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# === Compile GNL Objects ===
$(OBJ_DIR)/gnl/%.o: gnl/%.c
	@mkdir -p $(OBJ_DIR)/gnl
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# === Compile Render Objects ===
$(OBJ_DIR)/render/%.o: src/rendering/%.c
	@mkdir -p $(OBJ_DIR)/render
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# === Clean ===
clean:
	$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re