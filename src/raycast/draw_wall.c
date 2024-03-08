/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laliao <laliao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:04:41 by laliao            #+#    #+#             */
/*   Updated: 2024/03/08 14:59:22 by laliao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* if endian == 1, the Most Significant Byte(MSB) is leftmost */

void	ft_put_pixel(t_img img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img.bits_per_pixel - 8;
	pixel = img.addr + (y * img.size_line + (x * (img.bits_per_pixel / 8)));
	while (i >= 0)
	{
		
		if (img.endian == 1)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img.bits_per_pixel - 8 - i)) & 0xFF;
		i = i - 8;
	}
}

/*column is x, top_wall is y (where we start to draw the top of the wall)*/

void	ft_draw_wall(t_img img, int column, int top_wall, int pro_height)
{
	int	i;

	i = 0;
	if (top_wall < 0)
		top_wall = 0;
	while (i < pro_height && (top_wall + i) <= (WIN_HEIGHT - 1))
	{
		ft_put_pixel(img, column, top_wall + i, 70 << 16 | 70 << 8);
		i++;
	}
}
int		ft_verti_wall_connected(t_game *game, t_point center, t_point wall)
{
	int i;

	i = 0;
	while (((wall.y / TILE + i) != center.y / TILE) && (((wall.y / TILE + i) >= 0) 
		&& ((wall.y / TILE + i) <= game->map_height - 1)))
	{
		if (center.y / TILE < wall.y / TILE)
			i--;
		else
			i++;
		if (game->map_data[wall.y / TILE + i][wall.x / TILE] == '0')
			return (0);
		else if ((wall.y / TILE + i) == center.y / TILE)
			return (1);
	}
	return (0);
}

int		ft_hori_wall_connected(t_game *game, t_point center, t_point wall)
{
	int i;

	i = 0;
	while (((wall.x / TILE + i) != center.x / TILE) && (((wall.x / TILE + i) >= 0) 
		&& ((wall.x / TILE + i) <= game->map_lenght - 1)))
	{
		if (center.x / TILE < wall.x / TILE)
			i--;
		else
			i++;
		if (game->map_data[wall.y / TILE][wall.x / TILE + i] == '0')
			return (0);
		else if ((wall.x / TILE + i) == center.x / TILE)
			return (1);
	}
	return (0);
}

int		ft_wall_aligned(t_game *game, t_point center, t_point wall)
{
	if (wall.x / TILE == center.x / TILE && wall.y / TILE == center.y / TILE)
		return (1);
	else if ((wall.y / TILE == center.y / TILE) && (center.direction == 'S' || center.direction == 'N'))
	{
		if (ft_hori_wall_connected(game, center, wall))
			return (1);
	}
	else if ((wall.x / TILE == center.x / TILE) && (center.direction == 'W' || center.direction == 'E'))
	{
		if (ft_verti_wall_connected(game, center, wall))
			return (1);
	}
	return (0);
}

// function that calculate all the dimensions of the wall and the distance
// from the player, and then draw it on the window. 

void	ft_display(t_game *game, t_point wall, t_ray ray)
{
	double	dist;
	int		pro_height;
	int		top_wall;
	int 	i = 0;

	dist = distance(game->p1, wall, ray.alpha, ray.angle);
	//if ((ft_wall_aligned(game, center, wall) && center.direction == wall.direction) 
	//	&& distance(game->p1, center, ray.alpha, ray.angle) <= dist)
	//	dist = dist * cos(ray.beta * (double)(M_PI / 180));
	if (ray.angle != game->p1.pov)
		dist = dist * cos(ray.beta * (double)(M_PI / 180));
	pro_height = floor((TILE / dist) * ((WIN_LENGHT / 2) / tan(30 * (double)(M_PI / 180))));
	top_wall = (WIN_HEIGHT / 2) -  (pro_height / 2);
	ft_draw_wall(game->img, ray.column, top_wall, pro_height);
	//draw center
	while (i < WIN_HEIGHT / 2)
	{
		ft_put_pixel(game->img, WIN_LENGHT / 2, WIN_HEIGHT / 4 + i, 255 << 16);
		i++;
	}
}
