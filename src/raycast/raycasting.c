/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducloux <pducloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 03:37:54 by laliao            #+#    #+#             */
/*   Updated: 2024/03/08 16:17:43 by pducloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

/* function that search til it finds a wall, with diff having 
the distance in x and y for the next intersection with a line
of the grid (a possible wall) */

t_point	ft_find_wall(t_game *game, t_point a, double diff_x, double diff_y)
{
	t_point	current;

	current = a;
//	if (game->map_data[current.y / TILE][current.x / TILE] == 'E') // E if the tile is an empty spot in the map
//		return (game->blindspot);
	while ((current.x >= 0 && current.x / TILE < game->map_lenght) && 
		(current.y >= 0 && current.y / TILE < game->map_height))
	{
		if (game->map_data[current.y / TILE][current.x / TILE] == '1')
			return (current);
		current.x = current.x + diff_x;
		current.y = current.y + diff_y;
	}
	return (game->blindspot);
}

/* function that find the first intersection with a horizontal wall
of a ray casted from Player position */

t_point	ft_horizontal_inter(t_game *game, double alpha, double ray_angle)
{
	t_point	a;
	double	diff_x;
	double	diff_y;

	if (ray_angle <= 180)
	{
		a.y = floor((game->p1.y / TILE) * TILE - 1);
		diff_y = -TILE;
	}
	else
	{
		a.y = floor((game->p1.y / TILE) * TILE + TILE);
		diff_y = TILE;
	}
	if ((ray_angle >= 90 && ray_angle <= 180) || ray_angle >= 270)
		a.x = game->p1.x + (a.y - game->p1.y) / tan(alpha * (double)(M_PI / 180));
	else
		a.x = game->p1.x + (game->p1.y - a.y) / tan(alpha * (double)(M_PI / 180)); //conversion from degree to radians
	if (!(a.x / TILE > 0 && a.x / TILE < game->map_lenght))		//check if the point is within the map because-
		return (game->blindspot);								//if the angle is close to 0 or 180, there won't-
	diff_x = TILE / tan(alpha * (double)(M_PI / 180));			//be a horizontal wall intersection.
	if (ray_angle >= 90 && ray_angle <= 270)
		diff_x = -diff_x;
	if (game->map_data[a.y / TILE][a.x / TILE] != '1')	//check if point A is a wall or not on map_data
		a = ft_find_wall(game, a, diff_x, diff_y);
	return (a);
}

/* function that find the first intersection with a vertical wall
of a ray casted from Player position */

t_point	ft_vertical_inter(t_game *game, double alpha, double ray_angle)
{
	t_point	b;
	double	diff_x;
	double	diff_y;

	if (ray_angle <= 90 || ray_angle >= 270)
	{
		b.x = floor((game->p1.x / TILE) * TILE + TILE);
		diff_x = TILE;
	}
	else
	{
		b.x = floor((game->p1.x / TILE) * TILE - 1);
		diff_x = -TILE;
	}
	if ((ray_angle >= 90 && ray_angle <= 180) || ray_angle >= 270)
		b.y = game->p1.y + (b.x - game->p1.x) * tan(alpha * (double)(M_PI / 180));
	else
		b.y = game->p1.y + (game->p1.x - b.x) * tan(alpha * (double)(M_PI / 180));
	if (!(b.y / TILE > 0 && b.y / TILE < game->map_height))
		return (game->blindspot);
	diff_y = TILE * tan(alpha  * (double)(M_PI / 180));
	if (ray_angle <= 180)
		diff_y = -diff_y;
	if (game->map_data[b.y / TILE][b.x / TILE] != '1')
		b = ft_find_wall(game, b, diff_x, diff_y);
	return (b);
}

void	ft_set_wall_dir(t_player p1, t_point *wall, int type)
{
	if (type == 1)
	{
		if (p1.tile_y > wall->y / TILE)
			wall->direction = 'S';
		else
			wall->direction = 'N';
	}
	else
	{
		if (p1.tile_x > wall->x / TILE)
			wall->direction = 'E';
		else
			wall->direction = 'W';
	}
}

/* function that determines the coordinates of the wall with a given ray */

t_point	ft_ray_to_wall(t_game *game, double alpha, double ray_angle)
{
	t_point	horizontal;
	t_point	vertical;

	printf("\n\nray : %2f\n", ray_angle);
	horizontal = ft_horizontal_inter(game, alpha, ray_angle);
	vertical = ft_vertical_inter(game,alpha,ray_angle);
	if (distance(game->p1, horizontal, alpha, ray_angle) < distance(game->p1, vertical, alpha, ray_angle))
	{
		ft_set_wall_dir(game->p1, &horizontal, 1);
		return (horizontal);
	}
	ft_set_wall_dir(game->p1, &vertical, 0);
	return (vertical);
}

int		ft_playerview(t_game *game)
{
	t_ray	ray;
	t_point	wall;
	int		i;

	i = 0;
	ft_memset(game->img.addr, 0,
		WIN_HEIGHT * WIN_LENGHT * (game->img.bits_per_pixel / 8));
	ft_set_ray(&ray, game->p1, 0);
	while (i < WIN_LENGHT)
	{
		wall = ft_ray_to_wall(game, ray.alpha, ray.angle);
		ft_display(game, wall, ray);
		ft_set_ray(&ray, game->p1, 1);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->img.mlx_img, 0, 0);
	return (0);
}
