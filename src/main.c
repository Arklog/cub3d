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
#include "ft_string.h"

int main(int argc, char **argv) {
	t_cub3d	cub3d;

	ft_memset(&cub3d, 0, sizeof(t_cub3d));
	if (argc != 2)
		exit_cub3d(&cub3d, E_INVALID_ARGUMENTS);
	else
		cub3d.map.file.filename = argv[1];
	if (load(&cub3d))
		run(&cub3d);
	exit_cub3d(&cub3d, E_NO_ERROR);
	return (0);
}
