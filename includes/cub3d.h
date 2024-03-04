/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre </var/spool/mail/pierre>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:09:05 by pierre            #+#    #+#             */
/*   Updated: 2024/02/05 18:09:05 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_CUB3D_H
# define CUB3D_CUB3D_H

# include "types.h"
# include "libft.h"
# include "ft_ctype.h"
# include "mlx.h"

/**
 * Load cub3d
 *
 * @param filename
 * @param cub3d
 * @return
 */
t_errors	load_cub3d(const char *filename, t_cub3d *cub3d);

int load_textures(t_cub3d *cub3d);

int run(t_cub3d *cub3d);

void exit_cub3d(t_cub3d *cub3d, t_errors code);

int ft_isspacestr(const char *str);

int ft_isspacedigitstr(const char *str);

#endif //CUB3D_CUB3D_H
