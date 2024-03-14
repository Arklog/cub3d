/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducloux <pducloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:06:00 by pducloux          #+#    #+#             */
/*   Updated: 2024/03/14 17:31:48 by pducloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <fcntl.h>
# include <unistd.h>
# include "types.h"
# include "ft_string.h"
# include "ft_ctype.h"
# include "mlx.h"
# include "ft_stdlib.h"

# define BUFFER_SIZE 4096

# define MAPFILE_CHARSET "01NSEW"

/**
 * Load the file and store store it in the parser
 *
 * @param filename
 * @param parser
 * @return
 */
t_errors	load_map_file(const char *filename, t_parser *parser);

/**
 * @brief Check if the texture at line is a color
 * 
 * @param line 
 * @return int 
 */
int			texture_is_color(const char *line);

/**
 * @brief Load the color at line into the texture tex
 * 
 * @param line 
 * @param tex 
 * 
 * @return E_NO_ERROR on success, E_COLOR_INVALID if the color is invalid 
 */
t_errors	load_color(const char *line, t_texture *tex);

/**
 * @brief Check if the texture at line is a sprite
 * 
 * @param line 
 * @return int 
 */
int			texture_is_animated(const char *line);

t_errors	load_animated(const char *line, t_texture *tex, t_cub3d *cub);

/**
 * @brief Check if the texture at line is a texture (filepath)
 * 
 * @param line 
 * @return int 
 */
int			texture_is_texture(const char *line);

/**
 * @brief Load the texture at line into the texture tex
 * 
 * @param line 
 * @param tex 
 * @param cub 
 * 
 * @return E_NO_ERROR on success, E_TEXTURE_INVALID_PATH if the path is 
 * invalid or E_MLX_IMAGE if the image could not be loaded
 */
t_errors	load_texture(const char *line, t_texture *tex, t_cub3d *cub);

/**
 * @brief Check if the map is valid
 * 
 * @param map 
 * @return t_errors 
 */
t_errors	check_map(t_map *map);

t_errors	setup_map(t_map *map);

t_errors	create_map_check_buffer(t_map *map, char ***placeholder);

void		free_split(char **buff);

#endif //CUB3D_MAP_H
