/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 13:49:45 by meelma            #+#    #+#             */
/*   Updated: 2026/03/04 15:12:00 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

typedef struct s_data t_data;

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

/* === Parser Functions === */ 
int        parse_texture(char *line, t_data *data);
int        parse_color(char *line, t_data *data);


#endif