/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laliao <laliao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:30:22 by laliao            #+#    #+#             */
/*   Updated: 2024/03/09 12:28:37 by laliao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* function to calculate the distance between the player and one point */

double	distance(t_player p1, t_point a)
{
	if (a.x == 0 && a.y == 0)	//if blindspot
		return (DBL_MAX);
	return (sqrt(pow(p1.x - a.x, 2) + pow(p1.y - a.y, 2)));
}

void	ft_set_wall_dir(t_player p1, t_point *wall, int type)
{
	if (type == 1)
	{
		if (p1.y > wall->y)
			wall->direction = SOUTH;
		else
			wall->direction = NORTH;
	}
	else
	{
		if (p1.x > wall->x)
			wall->direction = EAST;
		else
			wall->direction = WEST;
	}
}

/* function that calculate the alpha angle for all directions depending
on the ray */

double	ft_get_alpha(double ray_angle)
{
	double	alpha;

	alpha = ray_angle;
	if (ray_angle > 90 && ray_angle <= 180)
		alpha = 180 - ray_angle;
	else if (ray_angle > 180 && ray_angle <= 270)
		alpha = ray_angle - 180;
	else if (ray_angle > 270 && ray_angle <= 360)
		alpha = 360 - ray_angle;
	else if (ray_angle > 360)
		alpha = ray_angle - 360;
	return (alpha);
}

/* function that calculate beta, the angle between the ray and 
the center of the player's point of view */

double	ft_get_beta(t_player p1, double ray_angle)
{
	double	beta;

	beta = fabs(p1.pov - ray_angle);
	if (beta > 300)
		beta = fabs(beta - 360);
	return (beta);
}

/* Initiate all ray values for the next ray */

void	ft_set_ray(t_ray *ray, t_player p1, int init)
{
	if (init == 0)
	{
		ray->angle = p1.pov - 30;
		if (ray->angle < 0)
			ray->angle = 360 + ray->angle;
		ray->column = WIN_LENGHT - 1;
	}
	else
	{
		ray->angle = ray->angle + ((double)60 / (WIN_LENGHT - 1));
		if (ray->angle >= 360)
			ray->angle = ray->angle - 360;
		ray->column--;
	}
	ray->alpha = ft_get_alpha(ray->angle);
	ray->beta = ft_get_beta(p1, ray->angle);
}
