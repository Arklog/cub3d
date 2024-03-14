/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducloux <pducloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:32:38 by pducloux          #+#    #+#             */
/*   Updated: 2024/03/14 17:32:50 by pducloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include <stdlib.h>

# include "types.h"
# include "defines.h"

typedef struct t_posstack
{
	t_pos				pos;
	struct t_posstack	*next;
}	t_posstack;

t_errors	push(t_posstack **stack, t_pos pos);

t_errors	pop(t_posstack **stack, t_pos *pos);

t_errors	peek(t_posstack *stack, t_pos *pos);

t_errors	clear(t_posstack **stack);

#endif //CUB3D_STACK_H
