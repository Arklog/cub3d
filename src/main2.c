/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laliao <laliao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 03:17:26 by laliao            #+#    #+#             */
/*   Updated: 2024/03/08 14:55:23 by laliao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	game_data;

	(void) ac;
	ft_bzero(&game_data, sizeof(game_data));
	game_data.mlx = mlx_init();
	if (!game_data.mlx)
		return (1);
	game_data.map_data = ft_get_map(av, &game_data);	//for quick test
	if (set_window(&game_data))
		return (1);
	ft_playerview(&game_data);
	//display screen

	mlx_hook(game_data.window, 2, 1L<<0, ft_key_press, &game_data);
	mlx_hook(game_data.window, 3, 1L<<1, ft_key_release, &game_data);
	mlx_hook(game_data.window, 17, 1L << 17, ft_exit_redcross, &game_data);
	mlx_loop_hook(game_data.mlx, ft_key_event, &game_data);
	mlx_loop(game_data.mlx);
	return (0);

}
