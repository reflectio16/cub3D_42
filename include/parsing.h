/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:00:00 by meelma            #+#    #+#             */
/*   Updated: 2026/03/14 15:02:07 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/* parse_utils.c */
t_line_type	get_line_type(char *line);
int			print_error(char *msg);
int			get_line_width(t_data *data, int current_line);

/* clean.c */
void		free_split(char **arr);
void		free_data(t_data *data);
int			clean_exit(int fd, char *line, t_list **map_list);

/* parse_texture.c */
int			parse_texture(char *line, t_data *data);

/* parse_color.c */
int			parse_color(char *line, t_data *data);

/* parse_map.c */
int			add_map_line(char *line, t_list **map_list);
char		**list_to_array(t_list *list, int *height);
int			get_map_width(char **map);
int			find_player(t_data *data);

/* validate_map.c */
int			validate_map(t_data *data);

/* flood_fill.c */
int			flood_fill(char **map, int x, int y, int height);

/* is_map_closed.c */
int			check_map_closed(t_data *data);

/* init.c */
int			parse_file(char *filename, t_data *data, t_list **map_list);
int			setup_map(t_data *data, t_list *map_list);

#endif