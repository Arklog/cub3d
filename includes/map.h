//
// Created by pierre on 2/5/24.
//

#ifndef CUB3D_MAP_H
#define CUB3D_MAP_H

#include <fcntl.h>
#include <unistd.h>
#include "types.h"
#include "ft_string.h"

# define BUFFER_SIZE 4096

t_errors	load_map(t_map *map);

#endif //CUB3D_MAP_H
