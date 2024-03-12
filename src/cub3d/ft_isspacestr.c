/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspacestr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre </var/spool/mail/pierre>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:30:38 by pierre            #+#    #+#             */
/*   Updated: 2024/03/12 15:30:39 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isspacestr(const char *str)
{
	while (*str && ft_isspace(*str))
		++str;
	return (!(*str));
}

int	ft_isspacedigitstr(const char *str)
{
	while (*str && (ft_isspace(*str) || ft_isdigit(*str)))
		++str;
	return (!(*str));
}
