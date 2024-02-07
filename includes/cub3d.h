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

int	load(t_cub3d *cub3d);

void run(t_cub3d *cub3d);

void exit_cub3d(t_cub3d *cub3d, t_errors code);

#endif //CUB3D_CUB3D_H
