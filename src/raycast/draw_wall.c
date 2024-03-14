/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laliao <laliao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:04:41 by laliao            #+#    #+#             */
/*   Updated: 2024/03/11 17:33:24 by laliao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* if endian == 1, the Most Significant Byte(MSB) is leftmost */

void	ft_put_pixel(t_img img, int x, int y, u_int32_t color, t_cub3d *cub3d)
{
	char	*pixel;
	int		i;

	i = img.bits_per_pixel - 8;
	pixel = img.addr + (y * img.size_line + (x * (img.bits_per_pixel / 8)));
	while (i >= 0)
	{
		if (img.endian == 1)
			*pixel++ = (char)((color >> i) & 0xFF);
		else
			*pixel++ = (char)((color >> (img.bits_per_pixel - 8 - i)) & 0xFF);
		i = i - 8;
	}
//	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.window, img.mlx_img, 0, 0);
}

/*x : column, y : top_wall(where we start to draw the top of the wall)*/

void	ft_draw_wall(t_img img, int column, int top_wall, int pro_height, t_cub3d *cub, t_point wall)
{
	int	i;
	int	tmp;
	t_color	color;

	i = 0;
	tmp = top_wall;
	if (top_wall < 0)
		top_wall = 0;
	while (i < top_wall)
		ft_put_pixel(img, column, i++, cub->textures[TEXTURE_CEILING].u_data.color.value, cub);
	i = 0;
	while (i < pro_height && (top_wall + i) <= (WIN_HEIGHT - 1))
	{
		if (tmp < 0)
			color = get_pixel_colorf(cub, wall, fmin((double)(i + abs(tmp)) / (double)pro_height, 1));
		else
			color = get_pixel_colorf(cub, wall, fmin((double)(i) / (double)pro_height, 1));
		ft_put_pixel(img, column, top_wall + i, color.value, cub);
		i++;
	}
	while (top_wall + i <= WIN_HEIGHT - 1)
		ft_put_pixel(img, column, top_wall + i++, cub->textures[TEXTURE_FLOOR].u_data.color.value, cub);
}

// function that calculate all the dimensions of the wall and the distance
// from the player, and then draw it on the window. 

void	ft_display(t_game *game, t_point wall, t_ray ray)
{
	double	dist;
	int		pro_height;
	int		top_wall;

	dist = distance(game->p1, wall);
	if (ray.angle != game->p1.pov)
		dist = dist * cos(ray.beta * (double)(M_PI / 180));
	pro_height = floor(((WIN_LENGHT / 2) / tan(30 * (double)(M_PI / 180))) * 
		(TILE / dist));
	top_wall = (WIN_HEIGHT / 2) - (pro_height / 2);
	ft_draw_wall(game->img, ray.column, top_wall, pro_height, game->cub3d, wall);
}
