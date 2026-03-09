/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 13:49:45 by meelma            #+#    #+#             */
/*   Updated: 2026/03/09 16:00:47 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

typedef struct s_data t_data;

# include "../Libft/libft.h"

typedef enum e_line_type
{
    LINE_EMPTY = 0,
    LINE_TEXTURE = 1,
    LINE_COLOR = 2,
    LINE_MAP = 3,
    LINE_INVALID = -1
}   t_line_type;

typedef struct s_texture
{
    char *tex_north; // NO
    char *tex_south; // SO
    char *tex_west;  // WE
    char *tex_east;  // EA
    
}   t_texture;

typedef struct s_color
{
    int floor_color;   // F
    int ceiling_color;  // C
    
}   t_color;

/* ===  Ultilities === */ 
void        free_split(char **arr);
t_line_type get_line_type(char *line);
int         print_error(char *msg);
void        free_data(t_data *data);
int         clean_exit(int fd, char *line, int ret);

/* === Parser Functions === */ 
int         parse_texture(char *line, t_data *data);
int         parse_color(char *line, t_data *data);
int         add_map_line(char *line, t_list **map_list);
char        **list_to_array(t_list *list, int *height);
int         get_map_width(char **map);
int         find_player(t_data *data);
int         validate_map(t_data *data);
int         check_map_closed(t_data *data);

/* === Init. c === */
int         check_args(int ac, char *filename);
int         parse_file(char *filename, t_data *data, t_list **map_list);
int         setup_map(t_data *data, t_list *map_list);


#endif