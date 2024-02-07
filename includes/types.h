//
// Created by pierre on 2/5/24.
//

#ifndef CUB3D_TYPES_H
#define CUB3D_TYPES_H

#include <sys/types.h>

typedef enum e_errors {
	E_NO_ERROR,
	E_INVALID_ARGUMENTS,
	E_MAP_ERROR,
	E_MAP_INVALID_EXTENSION,
	E_MAP_INVALID_DIMENTION,
	E_MAP_INVALID_PATH,
	E_MAP_INVALID_CHAR,
	E_TEXTURE_ERROR,
	E_TEXTURE_INVALID_PATH,
	E_ALLOCATION_FAILURE,
	E_ERROR_COUNT,
} t_errors;

typedef struct s_map {
	struct {
		char 	*filename;
		void 	*raw_data;
		size_t	dlen;
	} file;
	unsigned int	width;
	unsigned int	height;
} t_map;

typedef struct s_texture {
	char	*path;
	void	*data;
} t_texture;

typedef struct s_rendering_data {
} t_rendering_data;

typedef struct s_cub3d {
	t_map		map;
	t_texture	texture_data[4];
} t_cub3d;

#endif //CUB3D_TYPES_H
