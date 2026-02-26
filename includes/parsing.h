/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 13:49:45 by meelma            #+#    #+#             */
/*   Updated: 2026/02/26 15:32:31 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

typedef enum e_line_type
{
    LINE_EMPTY = 0,
    LINE_TEXTURE = 1,
    LINE_COLOR = 2,
    LINE_MAP = 3,
    LINE_INVALID = -1
}   t_line_type;


t_line_type get_line_type(char *line);


#endif