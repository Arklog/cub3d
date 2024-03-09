/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laliao <laliao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 03:37:54 by laliao            #+#    #+#             */
/*   Updated: 2024/03/09 12:31:54 by laliao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

/* function that find the first intersection with a horizontal/vertical wall
of a ray casted from Player position */

t_point	ft_horizontal_inter(t_game *game, double alpha, double ray_angle)
{
	t_point	a;
	t_point	diff;

	diff.y = TILE;
	if (ray_angle <= 180)
	{
		a.y = (game->p1.y / TILE) * TILE;
		diff.y = -TILE;
	}
	else
		a.y = floor((game->p1.y / TILE) * TILE + TILE);
	if ((ray_angle >= 90 && ray_angle <= 180) || ray_angle >= 270)
		a.x = game->p1.x + (a.y - game->p1.y) / tan(alpha * (double)(M_PI / 180));
	else
		a.x = game->p1.x + (game->p1.y - a.y) / tan(alpha * (double)(M_PI / 180)); //conversion from degree to radians
	if (!(a.x / TILE > 0 && a.x / TILE < game->map_lenght))		//check if the point is within the map because-
		return (game->blindspot);								//if the angle is close to 0 or 180, there won't-
	diff.x = TILE / tan(alpha * (double)(M_PI / 180));			//be a horizontal wall intersection.
	if (ray_angle >= 90 && ray_angle <= 270)
		diff.x = -diff.x;
	a = ft_find_horizontal(game, a, diff, ray_angle);
	return (a);
}

t_point	ft_vertical_inter(t_game *game, double alpha, double ray_angle)
{
	t_point	b;
	t_point	diff;

	diff.x = TILE;
	if (ray_angle <= 90 || ray_angle >= 270)
		b.x = floor((game->p1.x / TILE) * TILE + TILE);
	else
	{
		b.x = (game->p1.x / TILE) * TILE;
		diff.x = -TILE;
	}
	if ((ray_angle >= 90 && ray_angle <= 180) || ray_angle >= 270)
		b.y = game->p1.y + (b.x - game->p1.x) * tan(alpha * (double)(M_PI / 180));
	else
		b.y = game->p1.y + (game->p1.x - b.x) * tan(alpha * (double)(M_PI / 180));
	if (!(b.y / TILE > 0 && b.y / TILE < game->map_height))
		return (game->blindspot);
	diff.y = TILE * tan(alpha  * (double)(M_PI / 180));
	if (ray_angle <= 180)
		diff.y = -diff.y;
	b = ft_find_vertical(game, b, diff, ray_angle);
	return (b);
}

/* function that determines the coordinates of the wall with a given ray */

t_point	ft_ray_to_wall(t_game *game, double alpha, double ray_angle)
{
	t_point	horizontal;
	t_point	vertical;

	printf("\n\nray : %2f\n", ray_angle);
	horizontal = ft_horizontal_inter(game, alpha, ray_angle);
	vertical = ft_vertical_inter(game,alpha,ray_angle);
	if (distance(game->p1, horizontal) < distance(game->p1, vertical))
	{
		ft_set_wall_dir(game->p1, &horizontal, 1);
		return (horizontal);
	}
	ft_set_wall_dir(game->p1, &vertical, 0);
	return (vertical);
}

/* each call of the function will create a new view of the whole screen dimension
from player position */

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
