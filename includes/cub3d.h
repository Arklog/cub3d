/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducloux <pducloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:09:05 by pierre            #+#    #+#             */
/*   Updated: 2024/03/05 15:50:58 by pducloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "types.h"
# include "libft.h"
# include "ft_ctype.h"
# include "mlx.h"

/**
 * Load cub3d
 *
 * @param filename
 * @param cub3d
 * @return
 */
t_errors	load_cub3d(const char *filename, t_cub3d *cub3d);

/**
 * Load the textures
 * 
 * @param cub3d 
 * @return t_errors 
 */
t_errors	load_textures(t_cub3d *cub3d);

/**
 * Parse the remaining of the file into a map,
 * does not perform map checking
 * 
 * @param cub3d 
 * @return t_errors 
 */
t_errors	parse_map(t_cub3d *cub3d);

int			run(t_cub3d *cub3d);

/**
 * @brief Exit cub3d with given error code, if code != E_NO_ERROR 
 * an error message will be displayed
 * 
 * @param cub3d		cub3d datas
 * @param code		the error code
 */
void		exit_cub3d(t_cub3d *cub3d, t_errors code);

int			ft_isspacestr(const char *str);

int			ft_isspacedigitstr(const char *str);

/**
 * @brief Get the pixel color object
 * 
 * @param cub 	Cub3d datas
 * @param idx	Texture index
 * @param x 	Relative position of the texture x
 * @param y 	Relative position of the texture y
 * @return t_color 
 */
t_color		get_pixel_color(t_cub3d *cub, t_texture_index idx, double x, double y);

#endif //CUB3D_CUB3D_H
