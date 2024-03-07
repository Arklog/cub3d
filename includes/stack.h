//
// Created by pierre on 3/7/24.
//

#ifndef CUB3D_STACK_H
#define CUB3D_STACK_H

#include <stdlib.h>

#include "types.h"
#include "defines.h"

typedef struct t_posstack
{
	t_pos				pos;
	struct t_posstack	*next;
}	t_posstack;

t_errors push(t_posstack **stack, t_pos pos);

t_errors pop(t_posstack **stack, t_pos *pos);

t_errors peek(t_posstack *stack, t_pos *pos);

t_errors clear(t_posstack **stack);

#endif //CUB3D_STACK_H
