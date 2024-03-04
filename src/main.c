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

int main(int argc, char **argv) {
	t_cub3d	cub3d;
	t_errors err;

	ft_memset(&cub3d, 0, sizeof(t_cub3d));
	if (argc != 2)
		exit_cub3d(&cub3d, E_INVALID_ARGUMENTS);
	err = load_cub3d(argv[1], &cub3d);
	if (err)
		exit_cub3d(&cub3d, err);
	exit_cub3d(&cub3d, E_NO_ERROR);
	return (0);
}
