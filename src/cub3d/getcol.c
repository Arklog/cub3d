/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducloux <pducloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:41:46 by pducloux          #+#    #+#             */
/*   Updated: 2024/03/15 14:48:15 by pducloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

u_int32_t	getcol(t_texture_index idx, t_cub3d *cub)
{
	return (cub->textures[idx].u_data.color.value);
}
