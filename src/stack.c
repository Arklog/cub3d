/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre </var/spool/mail/pierre>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:30:11 by pierre            #+#    #+#             */
/*   Updated: 2024/03/12 15:30:16 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

t_errors	push(t_posstack **stack, t_pos pos)
{
	t_posstack	*new;

	new = malloc(sizeof(t_posstack));
	if (!new)
		return (E_ALLOCATION_FAILURE);
	new->pos = pos;
	new->next = *stack;
	*stack = new;
	return (E_NO_ERROR);
}

t_errors	pop(t_posstack **stack, t_pos *pos)
{
	t_posstack	*tmp;

	tmp = (*stack)->next;
	*pos = (*stack)->pos;
	free(*stack);
	*stack = tmp;
	return (E_NO_ERROR);
}

t_errors	peek(t_posstack *stack, t_pos *pos)
{
	*pos = stack->pos;
	return (E_NO_ERROR);
}

t_errors	clear(t_posstack **stack)
{
	t_posstack	*tmp;

	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
	return (E_NO_ERROR);
}
