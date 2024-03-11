/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laliao <laliao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:09:05 by pierre            #+#    #+#             */
/*   Updated: 2024/03/11 17:25:57 by laliao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "types.h"
# include "libft.h"
# include "ft_ctype.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <float.h>

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

int			ft_key_event(t_game *game);
int			ft_key_press(int keycode, t_game *game);
int			ft_key_release(int keycode, t_game *game);
int			ft_playerview(t_game *game);
void		ft_display(t_game *game, t_point wall, t_ray ray);
double		ft_get_alpha(double ray_angle);
double		ft_get_beta(t_player p1, double ray_angle);
void		ft_set_ray(t_ray *ray, t_player p1, int init);
double		distance(t_player p1, t_point a);
void		ft_set_wall_dir(t_player p1, t_point *wall, int type);
t_point		ft_find_horizontal(t_game *game, t_point a, t_point diff, double ray_angle);
t_point		ft_find_vertical(t_game *game, t_point a, t_point diff, double ray_angle);
void		ft_move_camera(t_game *game);

#endif //CUB3D_CUB3D_H
