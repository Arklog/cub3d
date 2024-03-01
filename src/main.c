/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre </var/spool/mail/pierre>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:08:18 by pierre            #+#    #+#             */
/*   Updated: 2024/02/05 18:08:18 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"
#include "map.h"
#include "mlx.h"
#include "ft_string.h"

static void	load_and_check_map(t_cub3d *cub3d)
{
	t_errors	err;

	err = load_map(&cub3d->map);
	if (err)
		exit_cub3d(cub3d, err);
	err = check_map(&cub3d->map);
	if (err)
		exit_cub3d(cub3d, err);
}

int main(int argc, char **argv) {
	t_cub3d	cub3d;

	ft_memset(&cub3d, 0, sizeof(t_cub3d));
	if (argc != 2)
		exit_cub3d(&cub3d, E_INVALID_ARGUMENTS);
	else
		cub3d.map.file.filename = argv[1];
	cub3d.mlx.mlx = mlx_init();
	if (!cub3d.mlx.mlx)
		exit_cub3d(&cub3d, E_MLX_INIT);
	cub3d.mlx.window = mlx_new_window(cub3d.mlx.mlx, 640, 480, "cub3d");
	if (!cub3d.mlx.window)
		exit_cub3d(&cub3d, E_MLX_WINDOW);
	load_and_check_map(&cub3d);
	if (!mlx_loop_hook(cub3d.mlx.mlx, (int (*)(void *))run, &cub3d))
		exit_cub3d(&cub3d, E_MLX_LOOP_HOOK);
	else if (!mlx_loop(cub3d.mlx.mlx))
		exit_cub3d(&cub3d, E_MLX_LOOP);
	exit_cub3d(&cub3d, E_NO_ERROR);
	return (0);
}
